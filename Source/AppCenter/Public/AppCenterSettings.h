// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "AppCenterSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UAppCenterSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** */
	UPROPERTY(Config, EditAnywhere)
	bool bEnableAnalytics;

	/** */
	UPROPERTY(Config, EditAnywhere)
	bool bEnableCrashes;

	/** */
	UPROPERTY(Config, EditAnywhere)
	bool bEnableDistribute;

	/** */
	UPROPERTY(Config, EditAnywhere)
	bool bEnablePush;

	/** The App Secret can be found on the Getting Started page or Settings page on the App Center portal */
	UPROPERTY(Config, EditAnywhere)
	FString AppSecretAndroid;

	/** The App Secret can be found on the Getting Started page or Settings page on the App Center portal */
	UPROPERTY(Config, EditAnywhere)
	FString AppSecretIOS;

	/** If you want to see the logs that get sent to the backend, set debug to true and the SDK will print logs in the console */
	UPROPERTY(Config, EditAnywhere)
	bool bDebug;
};
