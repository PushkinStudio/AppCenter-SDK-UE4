// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "AppCenterTypes.h"

#include "AppCenterProxy.generated.h"

UCLASS()
class APPCENTER_API UAppCenterProxy : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** Global AppCenterProxy accessor */
	UFUNCTION(BlueprintCallable, Category = "AppCenter", BlueprintPure)
	static UAppCenterProxy* Get();

	/////////////////////////////////////////////////////////////////////////
	// AppCenter Other APIs
public:
	/** You can control the amount of log messages that show up from App Center in the console. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetLogLevel(EAppCenterLogLevel InLogLevel);

	/** The App Center SDK creates a UUID for each device once the app is installed. This identifier remains the same for a device when the app is updated and a new one is generated only when the app is re-installed. */
	UFUNCTION(BlueprintPure, Category = "AppCenter|Other APIs")
	virtual FString GetInstallId();

	/** The App Center SDK supports setting a user ID that is used to augment crash reports. After setting a user ID, you can use App Center's search feature to search for specific crash reports associated with the ID. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetUserId();

	/** When disabled, the SDK will not forward any information to App Center. The state is persisted in the device's storage across application launches. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetEnabled(bool bEnabled = true);

	/** You can check if App Center is enabled or not. */
	UFUNCTION(BlueprintPure, Category = "AppCenter|Other APIs")
	virtual bool IsEnabled();

	/** You can get the version of App Center SDK that you are currently using.  */
	UFUNCTION(BlueprintPure, Category = "AppCenter|Other APIs")
	virtual FString GetSdkVersion();

	/**
	 * App Center allows you to define custom properties as key value pairs in your app. You may use custom properties for various purposes. 
	 * For instance, you can use custom properties to segment your users, and then send push notifications to a specific audience.
	 *
	 * @param CustomPropertiesJson Map of custom properties as string in json format
	 */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetCustomProperties(const FString& CustomPropertiesJson = "{}");

	/** App Center allows you to define custom properties as key value pairs in your app. You may use custom properties for various purposes. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetCustomPropertyAsString(const FString& Key, const FString& Value);

	/** App Center allows you to define custom properties as key value pairs in your app. You may use custom properties for various purposes. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetCustomPropertyAsInt(const FString& Key, int32 Value);

	/** App Center allows you to define custom properties as key value pairs in your app. You may use custom properties for various purposes. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetCustomPropertyAsFloat(const FString& Key, float Value);

	/** App Center allows you to define custom properties as key value pairs in your app. You may use custom properties for various purposes. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void SetCustomPropertyAsBool(const FString& Key, bool Value);

	/** You may remove any custom property. This will only remove the value of the property for a device. It will not remove the property name from App Center portal. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void ClearCustomProperties(const TArray<FString>& Keys);

	/** You may remove any custom property. This will only remove the value of the property for a device. It will not remove the property name from App Center portal. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Other APIs")
	virtual void ClearCustomProperty(const FString& Key);

	/////////////////////////////////////////////////////////////////////////
	// Analytics
public:
	/**
	 * You can track your own custom events with up to twenty properties to understand the interaction between your users and the app. 
	 *
	 * @param Properties Properties for events are entirely optional
	 * @param EventPersistence You can track business critical events that have higher importance than other events.
	 */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Analytics", meta = (AutoCreateRefTerm = "Properties"))
	virtual void TrackEvent(const FString& EventName, const TMap<FString, FString>& Properties, EAppCenterEventPersistence EventPersistence = EAppCenterEventPersistence::PERSISTENCE_NORMAL);

	/**
	 * Pausing the event transmission can be useful in scenarios when the app needs to control the network bandwidth for more business critical needs.
	 * You can pause sending logs to the App Center backend. When paused, events can still be tracked and saved, but they are not sent right away.
	 */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Analytics")
	virtual void PauseAnalytics();

	/** Any events your app tracks while paused will only be sent once you call `ResumeAnalytics()` */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Analytics")
	virtual void ResumeAnalytics();

	/** You can enable and disable App Center Analytics at runtime. If you disable it, the SDK will not collect any more analytics information for the app. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Analytics")
	virtual void SetAnalyticsEnabled(bool bEnabled = true);

	/** You can check if App Center Analytics is enabled or not. */
	UFUNCTION(BlueprintPure, Category = "AppCenter|Analytics")
	virtual bool IsAnalyticsEnabled();

	/////////////////////////////////////////////////////////////////////////
	// Crashes
public:
	/** App Center Crashes provides you with an API to generate a test crash for easy testing of the SDK. This API can only be used in debug builds and won't do anything in release builds. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Crashes")
	virtual void GenerateTestCrash();

	/** Generate native C++ crash. This API can only be used in debug builds and won't do anything in release builds. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Crashes")
	virtual void GenerateNativeCrash();

	/** Did the app crash in the previous session */
	UFUNCTION(BlueprintPure, Category = "AppCenter|Crashes")
	virtual bool HasCrashedInLastSession();

	/** If your app crashed previously, you can get details about the last crash. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Crashes")
	virtual FAppCenterErrorReport GetLastSessionCrashReport();

	/** You can enable and disable App Center Crashes at runtime. If you disable it, the SDK will not do any crash reporting for the app. */
	UFUNCTION(BlueprintCallable, Category = "AppCenter|Crashes")
	virtual void SetCrashesEnabled(bool bEnabled = true);

	/** You can check if App Center Crashes is enabled or not. */
	UFUNCTION(BlueprintPure, Category = "AppCenter|Crashes")
	virtual bool IsCrashesEnabled();
};
