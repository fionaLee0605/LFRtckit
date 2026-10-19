// swift-tools-version:5.5
import PackageDescription

// LiveFullerDC is a static binary framework that references the Agora RTC/RTM
// SDKs. This package vends only the LiveFullerDC binary; the consuming app must
// also add the Agora Swift packages and link them:
//   AgoraRtcEngine_iOS  (3.6.3)  products: RtcBasic (+ extensions as needed)
//   AgoraRtm_iOS        (1.4.10)
// plus, in the app target: OTHER_LDFLAGS = -ObjC, link libc++/libresolv/
// SystemConfiguration, and EXCLUDED_ARCHS[sdk=iphonesimulator*] = arm64
// (no arm64 simulator slice — same as the original CocoaPods binary).
let package = Package(
    name: "LiveFullerDC",
    platforms: [
        .iOS(.v15)
    ],
    products: [
        .library(name: "LiveFullerDC", targets: ["LiveFullerDC"])
    ],
    targets: [
        .binaryTarget(
            name: "LiveFullerDC",
            path: "LiveFullerDC.xcframework"
        )
    ]
)
