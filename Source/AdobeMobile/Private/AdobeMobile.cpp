//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "AdobeMobilePrivatePCH.h"
#include "AdobeMobileSettings.h"
#include "ISettingsModule.h"

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
}


void FAdobeMobile::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
