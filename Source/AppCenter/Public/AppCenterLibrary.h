// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "AppCenterLibrary.generated.h"

UCLASS()
class APPCENTER_API UAppCenterLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/** */
	UFUNCTION(BlueprintCallable, Category = AppCenter, BlueprintPure)
	static UAppCenterProxy* GetAppCenterProxy();
};
