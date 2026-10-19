//
//  LFVideoEngine.h
//  MyVideoSDK
//
//  Created by kerwin on 2020/1/10.
//  Copyright © 2020 kerwin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, LFJoinChannelErrorCode) {
    /**
0: Login succeeds. No error occurs.
     */
    LFJoinChannelErrorCodeOk = 0,
    /**
1: Login fails for reasons unknown.
     */
    LFJoinChannelErrorCodeUnknown = 1,
    /**
3: Invalid login arguments.
     */
    LFJoinChannelErrorCodeInvalidArgument = 2,
};
     

/** Reason for the user being offline. */
typedef NS_ENUM(NSUInteger, LFUserOfflineReason) {
    /** The user left the current channel. */
    LFUserOfflineReasonQuit = 0,
    /** The SDK timed out and the user dropped offline because no data packet is received within a certain period of time. If a user quits the call and the message is not passed to the SDK (due to an unreliable channel), the SDK assumes the user dropped offline. */
    LFUserOfflineReasonDropped = 1,
    
    LFUserOfflineReasonAbnormal = 2,
};
/** Network quality. */
typedef NS_ENUM(NSUInteger, LFNetworkQuality) {
    /** The network quality is unknown. */
    LFNetworkQualityUnknown = 0,
    /**  The network quality is excellent. */
    LFNetworkQualityExcellent = 1,
    /** The network quality is quite good, but the bitrate may be slightly lower than excellent. */
    LFNetworkQualityGood = 2,
    /** Users can feel the communication slightly impaired. */
    LFNetworkQualityPoor = 3,
    /** Users can communicate only not very smoothly. */
    LFNetworkQualityBad = 4,
     /** The network quality is so bad that users can hardly communicate. */
    LFNetworkQualityVBad = 5,
     /** The network is disconnected and users cannot communicate at all. */
    LFNetworkQualityDown = 6,
     /** Users cannot detect the network quality. (Not in use.) */
    LFNetworkQualityUnsupported = 7,
     /** Detecting the network quality. */
    LFNetworkQualityDetecting = 8,
};

@protocol LFVideoEngineDelegate <NSObject>
@optional

/// 已解码远端视频首帧
- (void)onSetRemoteVideoFrameWithUid:(NSUInteger)uid size:(CGSize)size;
///加入频道
- (void)didJoinChannel:(NSString *)channel withUid:(NSUInteger)uid;
///远端离开频道
- (void)didOfflineOfUid:(NSUInteger)uid reason:(LFUserOfflineReason)reason;
///网络质量
- (void)onNetworkQuality:(NSUInteger)uid txQuality:(LFNetworkQuality)txQuality rxQuality:(LFNetworkQuality)rxQuality;

@end
@interface LFVideoEngine : NSObject

@property(nonatomic,weak)id<LFVideoEngineDelegate>delegate;

+(LFVideoEngine *)shareEngine;


- (void)enableVideo;
/// 加入频道
- (void)joinChannelByChannelId:(NSString *)channelId completion:(void(^)(LFJoinChannelErrorCode errorCode))completion;
/// 设置本地视频
/// @param localVideoView 本地视频view
- (void)setupLocalVideo:(UIView *)localVideoView;
/// 设置远端视频
/// @param remoteVideoView 远端视频view
- (void)setupRemoteVideo:(UIView *)remoteVideoView uid:(NSUInteger)uid;


/// 预览
-(void)startPreview;

/// 静音
/// @param mute 静音 YES : 静音 NO: 不静音
-(void)muteLocalAudio:(BOOL)mute;
/// 转换摄像头
-(void)switchCamera;

/// 设置是否启动扬声器
/// @param enable <#enable description#>
-(void)setEnableSpeakerphone:(BOOL)enable;

/// 离开频道
- (void)leaveChannel;

/// 销毁
-(void)destoryEngine;
@end

NS_ASSUME_NONNULL_END
