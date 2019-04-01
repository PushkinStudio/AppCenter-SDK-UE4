// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "AppCenterProxy.h"

#include "AppCenter_IOS.generated.h"

#if PLATFORM_IOS
@interface AppCenterObserver : NSObject
@end
#endif // PLATFORM_IOS

// clang-format off
UCLASS()
class UAppCenter_IOS : public UAppCenterProxy
{
	GENERATED_UCLASS_BODY()

#if PLATFORM_IOS
#if WITH_APPCENTER_CRASHES
	virtual void GenerateTestCrash() override;
	virtual void GenerateNativeCrash() override;
#endif // WITH_APPCENTER_CRASHES
#endif
};
// clang-format on