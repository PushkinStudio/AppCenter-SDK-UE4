// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "AppCenterProxy.h"

#include "AppCenter_Android.generated.h"

UCLASS()
class UAppCenter_Android : public UAppCenterProxy
{
	GENERATED_UCLASS_BODY()

#if PLATFORM_ANDROID
#if WITH_APPCENTER_CRASHES
	virtual void GenerateTestCrash() override;
	virtual void GenerateNativeCrash() override;
	virtual bool HasCrashedInLastSession() override;
#endif // WITH_APPCENTER_CRASHES
#endif
};
