//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "AdobeMobilePrivatePCH.h"

#if PLATFORM_IOS
#import "../../lib/iOS/ADBMobile.h"
#elif PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif

void UAdobeMobileFunctions::AdobeMobileTrackState(FString state, FString data)
{
    UE_LOG(LogAdobeMobile, Log, TEXT("Tracking State..."));
    
#if PLATFORM_IOS
    [ADBMobile trackState:@"" data:@{ }];
#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_AdobeMobile_TrackState", "()Ljava/lang/String;",
                                                           false);
        
        FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);
    }
#endif
}

void UAdobeMobileFunctions::AdobeMobileTrackAction(FString state, FString data)
{
    UE_LOG(LogAdobeMobile, Log, TEXT("Tracking Action..."));
    
#if PLATFORM_IOS
    [ADBMobile trackAction:@"" data:@{ }];
#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_AdobeMobile_TrackAction", "()Ljava/lang/String;",
                                                           false);
        
        FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);
    }
#endif
}


