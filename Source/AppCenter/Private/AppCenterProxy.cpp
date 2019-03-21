// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "AppCenterProxy.h"

#include "AppCenterDefines.h"

UAppCenterProxy::UAppCenterProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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
