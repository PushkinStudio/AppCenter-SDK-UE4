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
	virtual void GenerateTestCrash() override;
	virtual void GenerateNativeCrash() override;
#endif
};
// clang-format on