// Copyright 2015-2020 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "AppCenterLibrary.generated.h"

UCLASS()
class APPCENTER_API UAppCenterLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/** Global AppCenterProxy accessor */
	UFUNCTION(BlueprintPure, Category = AppCenter, meta = (DisplayName = "Get AppCenter Proxy"))
	static UAppCenterProxy* GetAppCenterProxy();
};
