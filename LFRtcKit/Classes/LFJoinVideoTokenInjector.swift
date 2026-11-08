//
//  LFJoinVideoTokenInjector.swift
//  MediHub
//
//  Stopgap: the LFRtcKit SDK (LiveFullerDC.framework) is a precompiled binary that
//  fires `.../open/v1/api/join/video` with only `Client-Type` and `Authorization`
//  headers. The backend now also expects `Account-Token`. We cannot edit the SDK
//  (binary-only, no source), so we intercept that one request at the URL-loading
//  layer and inject the header here.
//
//  Remove this file (and its pod/dependency) once the vendor ships an SDK build
//  that sends Account-Token on join/video itself.
//
//  Reusable across projects: it has NO dependency on any app global. The host app
//  supplies the token through `tokenProvider`, which is read fresh on every request
//  — so a token that changes at runtime (re-login, member switch) is picked up
//  automatically.
//
//      LFJoinVideoTokenInjector.tokenProvider = { LIVEFULLER_ACCOUNT_TOKEN }
//      LFJoinVideoTokenInjector.activate()
//

import Foundation

public final class LFJoinVideoTokenInjector: URLProtocol {

    /// Supplies the current Account-Token. Called fresh on every matching request,
    /// so returning a live app value (not a captured snapshot) keeps it in sync
    /// when the token switches at runtime. Return nil/empty to skip injection.
    public static var tokenProvider: () -> String? = { nil }

    // Only touch this exact endpoint. Keep it as a suffix so it matches any
    // gateway/domain (fhn3, ssl, uat, ...).
    private static let targetPathSuffix = "/open/v1/api/join/video"
    private static let injectedHeaderField = "Account-Token"

    // Marks a request we've already handled, to avoid infinite recursion when we
    // re-issue it through our own session.
    private static let handledKey = "LFJoinVideoTokenInjectorHandled"

    private var proxyTask: URLSessionDataTask?
    private lazy var session: URLSession = {
        // Ephemeral + default protocol stack => our class is NOT registered on it,
        // so the re-issued request is not intercepted again.
        URLSession(configuration: .ephemeral, delegate: self, delegateQueue: nil)
    }()

    // MARK: - Activation

    /// Call once, early (e.g. in application(_:didFinishLaunchingWithOptions:)),
    /// after setting `tokenProvider`.
    public static func activate() {
        URLProtocol.registerClass(LFJoinVideoTokenInjector.self)
        // The SDK may build its own URLSession from a custom configuration, which
        // `registerClass` does NOT cover. Inject our protocol into every
        // configuration created via the standard factories so we catch those too.
        URLSessionConfiguration.lf_installJoinVideoInjector()
    }

    // MARK: - URLProtocol

    override public class func canInit(with request: URLRequest) -> Bool {
        guard URLProtocol.property(forKey: handledKey, in: request) == nil else {
            return false // already handled by us
        }
        guard let path = request.url?.path, path.hasSuffix(targetPathSuffix) else {
            return false
        }
        // Nothing to add if we have no token, or it's already present.
        guard let token = tokenProvider(), !token.isEmpty,
              request.value(forHTTPHeaderField: injectedHeaderField) == nil else {
            return false
        }
        return true
    }

    override public class func canonicalRequest(for request: URLRequest) -> URLRequest {
        return request
    }

    override public func startLoading() {
        guard let mutable = (request as NSURLRequest).mutableCopy() as? NSMutableURLRequest else {
            client?.urlProtocol(self, didFailWithError: URLError(.badURL))
            return
        }
        // Read the token again here (not captured in canInit) so it's the value
        // live at send time.
        if let token = Self.tokenProvider(), !token.isEmpty {
            mutable.setValue(token, forHTTPHeaderField: Self.injectedHeaderField)
        }
        URLProtocol.setProperty(true, forKey: Self.handledKey, in: mutable)

        proxyTask = session.dataTask(with: mutable as URLRequest)
        proxyTask?.resume()
    }

    override public func stopLoading() {
        proxyTask?.cancel()
        proxyTask = nil
        session.invalidateAndCancel()
    }
}

// MARK: - URLSession forwarding

extension LFJoinVideoTokenInjector: URLSessionDataDelegate {

    func urlSession(_ session: URLSession, dataTask: URLSessionDataTask,
                    didReceive response: URLResponse,
                    completionHandler: @escaping (URLSession.ResponseDisposition) -> Void) {
        client?.urlProtocol(self, didReceive: response, cacheStoragePolicy: .notAllowed)
        completionHandler(.allow)
    }

    func urlSession(_ session: URLSession, dataTask: URLSessionDataTask, didReceive data: Data) {
        client?.urlProtocol(self, didLoad: data)
    }

    func urlSession(_ session: URLSession, task: URLSessionTask,
                    didCompleteWithError error: Error?) {
        if let error = error {
            client?.urlProtocol(self, didFailWithError: error)
        } else {
            client?.urlProtocolDidFinishLoading(self)
        }
        session.finishTasksAndInvalidate()
    }

    // Preserve redirects.
    func urlSession(_ session: URLSession, task: URLSessionTask,
                    willPerformHTTPRedirection response: HTTPURLResponse,
                    newRequest request: URLRequest,
                    completionHandler: @escaping (URLRequest?) -> Void) {
        client?.urlProtocol(self, wasRedirectedTo: request, redirectResponse: response)
        completionHandler(request)
    }
}

// MARK: - Inject into SDK-created sessions

private extension URLSessionConfiguration {

    static func lf_installJoinVideoInjector() {
        // Swizzle `default` and `ephemeral` so configurations the SDK builds from
        // them carry our protocol class at the front of the stack.
        swizzle(#selector(getter: URLSessionConfiguration.default),
                with: #selector(lf_default))
        swizzle(#selector(getter: URLSessionConfiguration.ephemeral),
                with: #selector(lf_ephemeral))
    }

    @objc class func lf_default() -> URLSessionConfiguration {
        let config = lf_default() // calls the original (swapped) implementation
        config.lf_prependInjector()
        return config
    }

    @objc class func lf_ephemeral() -> URLSessionConfiguration {
        let config = lf_ephemeral()
        config.lf_prependInjector()
        return config
    }

    func lf_prependInjector() {
        var classes = protocolClasses ?? []
        if !classes.contains(where: { $0 == LFJoinVideoTokenInjector.self }) {
            classes.insert(LFJoinVideoTokenInjector.self, at: 0)
            protocolClasses = classes
        }
    }

    private static func swizzle(_ original: Selector, with swizzled: Selector) {
        let cls: AnyClass = object_getClass(URLSessionConfiguration.self)! // metaclass (class methods)
        guard let o = class_getClassMethod(cls, original),
              let s = class_getClassMethod(cls, swizzled) else { return }
        method_exchangeImplementations(o, s)
    }
}
