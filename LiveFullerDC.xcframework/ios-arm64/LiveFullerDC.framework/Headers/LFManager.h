//
//  LFManager.h
//  MyVideoSDK
//
//  Created by kerwin on 2020/1/8.
//  Copyright © 2020 kerwin. All rights reserved.
//



//Accelerate.framework
//AudioToolbox.framework
//AVFoundation.framework
//CoreMedia.framework
//CoreML.framework
//CoreTelephony.framework
//libc++.tbd
//libresolv.tbd
//SystemConfiguration.framework
//VideoToolbox.framework

//info.plist
//Privacy - Microphone Usage Description    使用麦克风的目的，例如：for a video call.
//Privacy - Camera Usage Description        使用摄像头的目的，例如：for a video call。

#import <Foundation/Foundation.h>
#import "LFRemoteInvitation.h"

NS_ASSUME_NONNULL_BEGIN
/**
<b>RETURNED TO THE CALLEE.</b> States of an incoming call invitation.
 */
/**
Error codes of the call invitation methods.
 */
typedef NS_ENUM(NSInteger, LFInvitationApiCallErrorCode) {
    
  /**
0: The method call succeeds.
   */
  LFInvitationApiCallErrorOk = 0,
    
  /**
1: The method call fails. Invalid argument.
   */
  LFInvitationApiCallErrorInvalidAugment = 1,
    
  /**
2: The method call fails. The call invitation has not started.
   */
  LFInvitationApiCallErrorNotStarted = 2,
    
  /**
3: The method call fails. The call invitation has ended.
   */
  LFInvitationApiCallErrorAlreadyEnd = 3,
    
  /**
4: The method call fails. The call invitation is already accepted.
   */
  LFInvitationApiCallErrorAlreadyAccept = 4,
    
  /**
5: The method call fails. The call invitation is already sent.
   */
  LFInvitationApiCallErrorAlreadySent = 5,
};

typedef NS_ENUM(NSInteger, LFRemoteInvitationErrorCode) {
    
  /**
0: <b>RETURNED TO THE CALLEE.</b> The incoming call invitation succeeds.
   */
  LFRemoteInvitationErrorOk = 0,
    
  /**
1: <b>RETURNED TO THE CALLEE.</b> The call invitation received by the callee fails: the callee is not online.
   */
  LFRemoteInvitationErrorLocalOffline = 1,
    
  /**
2: <b>RETURNED TO THE CALLEE.</b> The call invitation received by callee fails: the acceptance of the call invitation fails.
   */
  LFRemoteInvitationErrorAcceptFailure = 2,
    
  /**
3: <b>RETURNED TO THE CALLEE.</b> The call invitation received by the callee fails: the call invitation expires 60 seconds since it is sent, if the callee ACKs to the call invitation but neither the caller or callee takes any further action (cancel, accpet, or decline it).
   */
  LFRemoteInvitationErrorExpire = 3,
};

typedef NS_ENUM(NSInteger, LFLoginErrorCode) {
    
    /**
0: Login succeeds. No error occurs.
     */
    LFLoginErrorOk = 0,
    
    /**
1: Login fails for reasons unknown.
     */
    LFLoginErrorUnknown = 1,
    
    /**
2: Login is rejected, possibly because the SDK is not initialized or is rejected by the server.
     */
    LFLoginErrorRejected = 2,
    
    /**
3: Invalid login arguments.
     */
    LFLoginErrorInvalidArgument = 3,

    /**
7: Unauthorized login.
     */
    LFLoginErrorNotAuthorized = 7,
    
    /**
8: The user has already logged in or is logging in the LiveFullerDC system, or the user has not called the [logoutWithCompletion]([LFKit logoutWithCompletion:]) method to leave the `LFConnectionStateAborted` state.
     */
    LFLoginErrorAlreadyLogin = 8,
    
    /**
9: The login times out. The current timeout is set as six seconds.
     */
    LFLoginErrorTimeout = 9,
    
    /**
10: The call frequency of the [loginByToken]([LFKit loginByToken:user:completion:]) method exceeds the limit of two queries per second.
     */
    LFLoginErrorLoginTooOften = 10,
    
    /**
101: The SDK is not initialized.
     */
    LFLoginErrorLoginNotInitialized = 101,
    
    /**
     1001: The SDK is not initialized.
     */
    LFLoginAPIError = 1001,
    
    
};

/**
Error codes related to logout.
 */
typedef NS_ENUM(NSInteger, LFLogoutErrorCode) {
    
  /**
0: Logout succeeds. No error occurs.
   */
  LFLogoutErrorOk = 0,
    
  /**
1: Logout fails.
   */
  LFLogoutErrorRejected = 1,
    
  /**
101: The SDK is not initialized.
   */
  LFLogoutErrorNotInitialized = 101,
    
  /**
102: The user does not call the [loginByToken]([LFKit loginByToken:user:completion:]) method, or the method call of [loginByToken]([LFKit loginByToken:user:completion:]) does not succeed before the user logs out of the LiveFullerDC system.
   */
  LFLogoutErrorNotLoggedIn = 102,
};

typedef NS_ENUM(NSInteger, LFConnectionState) {
    
    LFConnectionStateDisconnected = 1,
    
    LFConnectionStateConnecting = 2,
    
    LFConnectionStateConnected = 3,
    
    LFConnectionStateReconnecting = 4,
    
    LFConnectionStateAborted = 5,
};
/**
Reasons for a connection state change.
 */
typedef NS_ENUM(NSInteger, LFConnectionChangeReason) {
    
    /**
1: The SDK is logging in the Agora RTM system.
     */
    LFConnectionChangeReasonLogin = 1,
    
    /**
2: The SDK has logged in the Agora RTM system.
     */
    LFConnectionChangeReasonLoginSuccess = 2,
    
    /**
3: The SDK fails to log in the Agora RTM system.
     */
    LFConnectionChangeReasonLoginFailure = 3,
    
    /**
4: The login has timed out for 10 seconds, and the SDK stops logging in.
     */
    LFConnectionChangeReasonLoginTimeout = 4,
    
    /**
5: The connection between the SDK and the Agora RTM system is interrupted for more than four seconds.
     */
    LFConnectionChangeReasonInterrupted = 5,
    
    /**
6: The user has called the [logoutWithCompletion]([LFKit logoutWithCompletion:]) method to log out of the Agora RTM system.
     */
    LFConnectionChangeReasonLogout = 6,
    
    /**
7: Login is banned by the Agora RTM server.
     */
    LFConnectionChangeReasonBannedByServer = 7,
    
    /**
8: Another instance has logged in the Agora RTM system with the same user ID.
     */
    LFConnectionChangeReasonRemoteLogin = 8,
};


typedef void (^LFRemoteInvitationAcceptBlock)(LFInvitationApiCallErrorCode errorCode);


@protocol LFManagerDelegate <NSObject>
@optional
/// 主叫成功,建立链接
-(void)localInvitationAccepted:(NSString *)channelId withResponse:(NSString * )response;
/// 被叫收到呼叫邀请
-(void)onRemoteInvitationReceived:(LFRemoteInvitation *)remoteInvitation;
/// 主叫已取消邀请
-(void)onRemoteInvitationCanceled:(LFRemoteInvitation *)remoteInvitation;
/// 被叫接受邀请成功
-(void)onRemoteInvitationAccepted:(LFRemoteInvitation *)remoteInvitation;
/// 被叫邀请失败
-(void)onRemoteInvitationFailure:(LFRemoteInvitation *)remoteInvitation errorCode:(LFRemoteInvitationErrorCode)errorCode;

@end
@protocol LFUserStateDelegate <NSObject>
@optional
/// 连接状态回调
-(void)connectionStateChanged:(LFConnectionState)state reason:(LFConnectionChangeReason)reason;
/// token过期
-(void)onTokenDidExpire;
@end
@interface LFManager : NSObject

@property(nonatomic,weak,nullable)id<LFManagerDelegate> delegate;

@property(nonatomic,weak,nullable)id<LFUserStateDelegate> userStatedelegate;
/// 初始化
+(LFManager *)initWithClientType:(NSString *)clientType authorization:(NSString *)authorization domain:(NSString *)domain;

/// 获取单例对象;
+(LFManager *)shareManager;
/// LiveFullerDC登录
/// @param userId userID
-(void)loginByUserId:(NSString *)userId Success:(void(^)(NSString *accountToken, NSString *userId, NSString *tencentAppId, NSString *userSig))success Failure:(void(^)(LFLoginErrorCode errorCode))fail;
/// 接收邀请
-(void)acceptRemoteInvitation:(LFRemoteInvitation *)remoteInvitation completion:(LFRemoteInvitationAcceptBlock)completion;
/// 登出
-(void)logOutWithCompletion:(void(^)(LFLogoutErrorCode errorCode))completion;
@end

NS_ASSUME_NONNULL_END
