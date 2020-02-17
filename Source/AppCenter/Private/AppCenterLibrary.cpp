// Copyright 2015-2020 Mail.Ru Group. All Rights Reserved.

#include "AppCenterLibrary.h"

#include "AppCenter.h"

UAppCenterLibrary::UAppCenterLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UAppCenterProxy* UAppCenterLibrary::GetAppCenterProxy()
{
	return FAppCenterModule::Get().GetProxy();
}
