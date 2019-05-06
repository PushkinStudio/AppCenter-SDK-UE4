// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "AppCenter.h"

#include "AppCenterDefines.h"
#include "AppCenterProxy.h"
#include "AppCenterSettings.h"

#include "Developer/Settings/Public/ISettingsModule.h"
#include "UObject/Package.h"

#if PLATFORM_IOS
#include "AppCenter_IOS.h"
#elif PLATFORM_ANDROID
#include "AppCenter_Android.h"
#endif

#define LOCTEXT_NAMESPACE "FAppCenterModule"

void FAppCenterModule::StartupModule()
{
	AppCenterSettings = NewObject<UAppCenterSettings>(GetTransientPackage(), "AppCenterSettings", RF_Standalone);
	AppCenterSettings->AddToRoot();

	// Register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "AppCenter SDK",
			LOCTEXT("RuntimeSettingsName", "AppCenter SDK"),
			LOCTEXT("RuntimeSettingsDescription", "Configure AppCenter SDK"),
			AppCenterSettings);
	}

	// Proxy class depends on platform
	UClass* KitPlatformClass = UAppCenterProxy::StaticClass();
#if PLATFORM_IOS
	KitPlatformClass = UAppCenter_IOS::StaticClass();
#elif PLATFORM_ANDROID
	KitPlatformClass = UAppCenter_Android::StaticClass();
#endif

	// Create crashlytics kit proxy and initalize module by default
	AppCenterProxy = NewObject<UAppCenterProxy>(GetTransientPackage(), KitPlatformClass);
	AppCenterProxy->SetFlags(RF_Standalone);
	AppCenterProxy->AddToRoot();
}

void FAppCenterModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "AppCenter SDK");
	}

	if (!GExitPurge)
	{
		// If we're in exit purge, this object has already been destroyed
		AppCenterSettings->RemoveFromRoot();
		AppCenterProxy->RemoveFromRoot();
		AppCenterProxy->ClearFlags(RF_Standalone);
	}
	else
	{
		AppCenterSettings = nullptr;
		AppCenterProxy = nullptr;
	}
}

UAppCenterSettings* FAppCenterModule::GetSettings() const
{
	check(AppCenterSettings);
	return AppCenterSettings;
}

UAppCenterProxy* FAppCenterModule::GetProxy() const
{
	check(AppCenterProxy);
	return AppCenterProxy;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAppCenterModule, AppCenter)

DEFINE_LOG_CATEGORY(LogAppCenter);