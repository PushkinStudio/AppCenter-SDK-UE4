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

	/** Force native crash */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Crashes")
	virtual void TestNativeCrash();

	/** Did the app crash in the previous session */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Crashes")
	virtual bool HasCrashedInLastSession();

};
