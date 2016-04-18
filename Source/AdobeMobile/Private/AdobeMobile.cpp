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

void FAdobeMobile::StartupModule()
{
	// register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "AdobeMobile",
										 LOCTEXT("RuntimeSettingsName", "AdobeMobile"),
										 LOCTEXT("RuntimeSettingsDescription", "Configure the AdobeMobile plugin"),
										 GetMutableDefault<UAdobeMobileSettings>()
										 );
	}
    
    const UAdobeMobileSettings *settings = GetDefault<UAdobeMobileSettings>();
    
#if PLATFORM_IOS
    NSString *sdkVersion = [NSString stringWithFormat:@"%@:%@:%@",
                            [ADBMobile version],
                            [[NSBundle mainBundle] infoDictionary][@"CFBundleVersion"],
                            [[NSBundle mainBundle] infoDictionary][@"CFBundleShortVersionString"]];
    
    NSDictionary *d = @{ @"appname"    : settings->AppName.GetNSString(),
                         @"sdkversion" : sdkVersion };
    
    [ADBMobile collectLifecycleDataWithAdditionalData:d];
#elif PLATFORM_ANDROID
    // Initilization of Android is done through plugin APL file.
    //
#endif
}


void FAdobeMobile::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
