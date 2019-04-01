// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "AppCenterProxy.generated.h"

/**
 * The log levels correspond to the ones defined in both 
 * https://developer.android.com/reference/android/util/Log and
 * https://github.com/Microsoft/AppCenter-SDK-Apple/blob/develop/AppCenter/AppCenter/MSConstants.h
 */
UENUM(BlueprintType)
enum class EAppCenterLogLevel : uint8
{
	/** Only critical errors will be logged */
	ASSERT = 7,

	/** Debug information will be logged */
	DEBUG = 3,

	/** Errors will be logged */
	ERROR = 6,

	/** Information will be logged */
	INFO = 4,

	/** Logging will be very chatty */
	VERBOSE = 2,

	/** Errors and warnings will be logged */
	WARN = 5,

	/** Logging is disabled (IOS only!) */
	NONE = 99
};

UCLASS()
class APPCENTER_API UAppCenterProxy : public UObject
{
	GENERATED_UCLASS_BODY()

	/////////////////////////////////////////////////////////////////////////
	// AppCenter Other APIs
public:
	/** You can control the amount of log messages that show up from App Center in the console. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetLogLevel(EAppCenterLogLevel LogLevel);

	/** The App Center SDK creates a UUID for each device once the app is installed. This identifier remains the same for a device when the app is updated and a new one is generated only when the app is re-installed. */
	UFUNCTION(BlueprintPure, Category = "AppCenter|Other APIs")
	virtual FString GetInstallId();

	/** The App Center SDK supports setting a user ID that is used to augment crash reports. After setting a user ID, you can use App Center's search feature to search for specific crash reports associated with the ID. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetUserId();

	/** When disabled, the SDK will not forward any information to App Center. The state is persisted in the device's storage across application launches. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetEnabled();

	/** You can check if App Center is enabled or not. */
	UFUNCTION(BlueprintPure, Category = "AppCenter|Other APIs")
	virtual bool IsEnabled();

	/** You can get the version of App Center SDK that you are currently using.  */
	UFUNCTION(BlueprintPure, Category = "AppCenter|Other APIs")
	virtual FString GetSdkVersion();

	/** 
	 * App Center allows you to define custom properties as key value pairs in your app. You may use custom properties for various purposes. 
	 * For instance, you can use custom properties to segment your users, and then send push notifications to a specific audience. 
	 */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetCustomProperties(/** @TODO */);

	/** You may remove any custom property. This will only remove the value of the property for a device. It will not remove the property name from App Center portal. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void ClearCustomProperties(/** @TODO */);

	/////////////////////////////////////////////////////////////////////////
	// Analytics

	/////////////////////////////////////////////////////////////////////////
	// Crashes
public:
	/** Force crash */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Crashes")
	virtual void TestCrash();

	/** Force native crash */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Crashes")
	virtual void TestNativeCrash();

	/** Did the app crash in the previous session */
	UFUNCTION(BlueprintPure, Category = "AppCenter|Crashes")
	virtual bool HasCrashedInLastSession();
};
