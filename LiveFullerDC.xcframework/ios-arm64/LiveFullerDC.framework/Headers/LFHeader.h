//
//  LFHeader.h
//  LiveFullerDC
//
//  Created by kerwin on 2020/1/31.
//  Copyright © 2020 kerwin. All rights reserved.
//


// Include any system framework and library headers here that should be included in all compilation units.
// You will also need to set the Prefix Header build setting of one or more of your targets to reference this file.

#define API_GATEWAY_fhn3                 @"fhn3"        //fhn3测试
#define API_GATEWAY_testenv              @"testenv"     //plato测试
#define API_GATEWAY_uat                  @"uat"         //uat测试
#define API_GATEWAY_pro                  @"ssl"         //生产
#define API_GATEWAY_pre                  @"pre"         //预发
#define API_GATEWAY_dev                  @"dev"         //开发


#define API_Host                 [NSString stringWithFormat:@"https://apiv2-gateway-%@.fullertonhealthtech.com",API_GATEWAY_fhn3]



#define API_Login(domain)                       [NSString stringWithFormat:@"%@/client-open-web/open/v1/api/login",domain]
#define API_JoinChannel(domain)                [NSString stringWithFormat:@"%@/client-open-web/open/v1/api/join/video",domain]

