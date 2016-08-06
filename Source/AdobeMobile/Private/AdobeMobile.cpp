//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "AdobeMobilePrivatePCH.h"
#include "AdobeMobileSettings.h"
#include "ISettingsModule.h"

#if PLATFORM_IOS
#import "../../lib/iOS/ADBMobile.h"
#elif PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif

DEFINE_LOG_CATEGORY(LogAdobeMobile);

#define LOCTEXT_NAMESPACE "AdobeMobile"

class FAdobeMobile : public IAdobeMobile
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FAdobeMobile, AdobeMobile )

#if PLATFORM_IOS

@interface AdobeMobileDelegate : NSObject
{
}

@end

static AdobeMobileDelegate *ams;

@implementation AdobeMobileDelegate

+(void)load
{
    if (!ams)
    {
        ams = [[AdobeMobileDelegate alloc] init];
    }
}

-(id)init
{
    self = [super init];
    
    if (self)
    {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(applicationDidFinishLaunching:)
                                                     name:UIApplicationDidFinishLaunchingNotification
                                                   object:nil];
    }
    
    return self;
}

-(void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

-(void)applicationDidFinishLaunching:(NSNotification *)n
{
    NSDictionary *dLaunchOptionsUrl = n.userInfo[@"UIApplicationLaunchOptionsURLKey"];
    
    if (!dLaunchOptionsUrl)
    {
        NSString *sdkVersion = [NSString stringWithFormat:@"%@:%@:%@",
                                [ADBMobile version],
                                [[NSBundle mainBundle] infoDictionary][@"CFBundleVersion"],
                                [[NSBundle mainBundle] infoDictionary][@"CFBundleShortVersionString"]];
        
        NSDictionary *info    = [[NSBundle mainBundle] infoDictionary][@"AdobeMobile"];
        NSString     *appName = @"";
        
        if (info)
        {
            appName = info[@"AppName"];

            if (!appName)
            {
                UE_LOG(LogAdobeMobile, Log, TEXT("[AdobeMobile][AppName] was not found in info.plist tracking may not behave correctly"));
            }
        }
        else
        {
            UE_LOG(LogAdobeMobile, Log, TEXT("[AdobeMobile] was not found in info.plist tracking may not behave correctly"));
        }
        
        NSDictionary *d = @{ @"appname"    : appName,
                             @"sdkversion" : sdkVersion };

        [ADBMobile collectLifecycleDataWithAdditionalData:d];
    }
}

@end

#endif

void FAdobeMobile::StartupModule()
{
    // register settings
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "AdobeMobile",
										 LOCTEXT("RuntimeSettingsName", "AdobeMobile"),
										 LOCTEXT("RuntimeSettingsDescription", "Configure the AdobeMobile plugin"),
										 GetMutableDefault<UAdobeMobileSettings>());
	}
}


void FAdobeMobile::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
