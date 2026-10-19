//
//  LFRemoteInvitation.h
//  MyVideoSDK
//
//  Created by kerwin on 2020/1/13.
//  Copyright © 2020 kerwin. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSInteger, LFRemoteInvitationState) {
    
  /**
0: <b>RETURNED TO THE CALLEE.</b> The initial state of a call invitation (idle).
   */
  LFRemoteInvitationStateIdle = 0,
    
  /**
1: <b>RETURNED TO THE CALLEE.</b> A call invitation from a remote caller is received.
   */
  LFRemoteInvitationStateInvitationReceived = 1,
    
  /**
2: FOR INTERNAL USE ONLY.
   */
  LFRemoteInvitationStateAcceptSentToLocal = 2,
    
  /**
3: <b>RETURNED TO THE CALLEE.</b> You have declined the call invitation.
   */
  LFRemoteInvitationStateRefused = 3,
    
  /**
4: <b>RETURNED TO THE CALLEE.</b> You have accepted the call invitation.
   */
  LFRemoteInvitationStateAccepted = 4,
    
  /**
5: <b>RETURNED TO THE CALLEE.</b> The call invitation is canceled by the remote caller.
   */
  LFRemoteInvitationStateCanceled = 5,
    
  /**
6: <b>RETURNED TO THE CALLEE.</b> The life cycle of the incoming call invitation ends in failure.
   */
  LFRemoteInvitationStateFailure = 6,
};

/**
<b>RETURNED TO THE CALLER.</b> Error codes of an outgoing call invitation.
 */

/**
<b>RETURNED TO THE CALLEE.</b> Error codes of an incoming call invitation.
 */

/** The callee's call invitation object. */
@interface LFRemoteInvitation: NSObject
/** User ID of the caller. */
@property (nonatomic, copy, nonnull) NSString *callerId;

/** The call invitation content set by the caller. */
@property (nonatomic, copy, nullable) NSString *content;

/** The callee's reponse to the call invitation. */
@property (nonatomic, copy, nullable) NSString *response;

/**The channel ID. */
@property (nonatomic, copy, nullable) NSString *channelId;

/** The state of the incoming call invitation. See LFRemoteInvitationState. */
@property (nonatomic, assign) LFRemoteInvitationState state;
@end


NS_ASSUME_NONNULL_END
