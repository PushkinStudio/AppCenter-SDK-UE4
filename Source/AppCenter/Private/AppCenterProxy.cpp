// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "AppCenterProxy.h"

#include "AppCenterDefines.h"

UAppCenterProxy::UAppCenterProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

/////////////////////////////////////////////////////////////////////////
// AppCenter Other APIs

void UAppCenterProxy::SetLogLevel(EAppCenterLogLevel LogLevel)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet: %d"), *PS_FUNC_LINE, static_cast<int32>(LogLevel));
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

void UAppCenterProxy::SetEnabled()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
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

void UAppCenterProxy::SetCustomProperties(/** @TODO */)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
}

void UAppCenterProxy::ClearCustomProperties(/** @TODO */)
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Not implemented yet"), *PS_FUNC_LINE);
}

/////////////////////////////////////////////////////////////////////////
// Crashes

void UAppCenterProxy::TestCrash()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
}

void UAppCenterProxy::TestNativeCrash()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
}

bool UAppCenterProxy::HasCrashedInLastSession()
{
	UE_LOG(LogAppCenter, Warning, TEXT("%s: Null proxy used"), *PS_FUNC_LINE);
	return false;
}
