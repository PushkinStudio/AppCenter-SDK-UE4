// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "AppCenterProxy.generated.h"

UCLASS()
class APPCENTER_API UAppCenterProxy : public UObject
{
	GENERATED_UCLASS_BODY()

	/////////////////////////////////////////////////////////////////////////
	// Crashes

	/** Force crash */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Crashes")
	virtual void TestCrash();
};
