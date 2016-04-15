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

void UAdobeMobileFunctions::AdobeMobileTrackState(FString state, TArray<FString> dataKeys, TArray<FString> dataValues)
{
    UE_LOG(LogAdobeMobile, Log, TEXT("Tracking State..."));

    const int32 kNumKeys   = dataKeys.Num();
    const int32 kNumValues = dataValues.Num();
    
    if (kNumKeys == 0 || kNumValues == 0)
    {
        UE_LOG(LogAdobeMobile, Log, TEXT("keys and/or value arguments are empty"));
        return;
    }
    
    if (kNumKeys != kNumValues)
    {
         UE_LOG(LogAdobeMobile, Log, TEXT("number of keys are not equal to number of values"));
        return;
    }
    
    // Verify that keys are of allowed data types by Adobe Mobile plugin
    
#if PLATFORM_IOS
    [ADBMobile trackState:@"" data:@{ }];
    NSMutableDictionary *d = [NSMutableDictionary dictionaryWithCapacity:kNumKeys];
    
    for (uint32 i = 0; i < kNumKeys; i++)
    {
        FString &k = dataKeys[i];
        FString &v = dataValues[i];
        
        d[k.GetNSString()] = v.GetNSString();
    }
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

void UAdobeMobileFunctions::AdobeMobileTrackAction(FString state, TArray<FString> dataKeys, TArray<FString> dataValues)
{
    UE_LOG(LogAdobeMobile, Log, TEXT("Tracking Action..."));
    
    const int32 kNumKeys   = dataKeys.Num();
    const int32 kNumValues = dataValues.Num();
    
    if (kNumKeys == 0 || kNumValues == 0)
    {
        UE_LOG(LogAdobeMobile, Log, TEXT("keys and/or value arguments are empty"));
        return;
    }
    
    if (kNumKeys != kNumValues)
    {
        UE_LOG(LogAdobeMobile, Log, TEXT("number of keys are not equal to number of values"));
        return;
    }
    
#if PLATFORM_IOS
    [ADBMobile trackAction:@"" data:@{ }];
    NSMutableDictionary *d = [NSMutableDictionary dictionaryWithCapacity:kNumKeys];
    
    for (uint32 i = 0; i < kNumKeys; i++)
    {
        FString &k = dataKeys[i];
        FString &v = dataValues[i];
        
        d[k.GetNSString()] = v.GetNSString();
    }
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


