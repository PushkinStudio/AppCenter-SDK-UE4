// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "AppCenterProxy.h"

#include "AppCenter.h"
#include "AppCenterDefines.h"

UAppCenterProxy::UAppCenterProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UAppCenterProxy* UAppCenterProxy::Get()
{
	return FAppCenterModule::Get().GetProxy();
}

/////////////////////////////////////////////////////////////////////////
// AppCenter Other APIs

void UAppCenterProxy::SetLogLevel(EAppCenterLogLevel InLogLevel)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet: %d"), *PS_FUNC_LINE, static_cast<int32>(InLogLevel));
}

FString UAppCenterProxy::GetInstallId()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
	return FString();
}

void UAppCenterProxy::SetUserId()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
}

void UAppCenterProxy::SetEnabled(bool bEnabled)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet: %s"), *PS_FUNC_LINE, bEnabled ? TEXT("True") : TEXT("False"));
}

bool UAppCenterProxy::IsEnabled()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
	return true;
}

FString UAppCenterProxy::GetSdkVersion()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
	return FString();
}

void UAppCenterProxy::SetCustomProperties(const FString& CustomPropertiesJson)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
}

void UAppCenterProxy::SetCustomPropertyAsString(const FString& Key, const FString& Value)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
}

void UAppCenterProxy::SetCustomPropertyAsInt(const FString& Key, int32 Value)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
}

void UAppCenterProxy::SetCustomPropertyAsFloat(const FString& Key, float Value)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
}

void UAppCenterProxy::SetCustomPropertyAsBool(const FString& Key, bool Value)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
}

void UAppCenterProxy::ClearCustomProperties(const TArray<FString>& Keys)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
}

void UAppCenterProxy::ClearCustomProperty(const FString& Key)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
}

/////////////////////////////////////////////////////////////////////////
// Analytics

void UAppCenterProxy::TrackEvent(const FString& EventName, const TMap<FString, FString>& Properties, EAppCenterEventPersistence EventPersistence)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used: %s (%d)"), *PS_FUNC_LINE, *EventName, static_cast<int32>(EventPersistence));
}

void UAppCenterProxy::PauseAnalytics()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
}

void UAppCenterProxy::ResumeAnalytics()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
}

void UAppCenterProxy::SetAnalyticsEnabled(bool bEnabled)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet: %s"), *PS_FUNC_LINE, bEnabled ? TEXT("True") : TEXT("False"));
}

bool UAppCenterProxy::IsAnalyticsEnabled()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
	return false;
}

/////////////////////////////////////////////////////////////////////////
// Crashes

void UAppCenterProxy::GenerateTestCrash()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
}

void UAppCenterProxy::GenerateNativeCrash()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
}

bool UAppCenterProxy::HasCrashedInLastSession()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
	return false;
}

FAppCenterErrorReport UAppCenterProxy::GetLastSessionCrashReport()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
	return FAppCenterErrorReport();
}

void UAppCenterProxy::SetCrashesEnabled(bool bEnabled)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet: %s"), *PS_FUNC_LINE, bEnabled ? TEXT("True") : TEXT("False"));
}

bool UAppCenterProxy::IsCrashesEnabled()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
	return false;
}
