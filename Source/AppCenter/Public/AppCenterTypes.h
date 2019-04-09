// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "AppCenterTypes.generated.h"

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
	ERRORR = 6,
	/** Information will be logged */
	INFO = 4,
	/** Logging will be very chatty */
	VERBOSE = 2,
	/** Errors and warnings will be logged */
	WARN = 5,
	/** Logging is disabled (IOS only!) */
	NONE = 99
};

/**
 * You can track business critical events that have higher importance than other events.
 * 
 *  - Events with priority set as Critical will be retrieved from storage first and sent before Normal events.
 *  - When the local storage is full and new events needs to be stored, the oldest events that have the lowest priority are deleted first to make room for the new ones.
 *  - If the storage is full of logs with Critical priority, then tracking an event with Normal priority will fail as the SDK cannot make room in that case.
 *  - If you also use the Crashes service, please note that crash logs are set as Critical and share the same storage as events.
 */
UENUM(BlueprintType)
enum class EAppCenterEventPersistence : uint8
{
	/** Normal */
	PERSISTENCE_NORMAL = 1,
	/** Critical */
	PERSISTENCE_CRITICAL = 2
};

/**
 * Details about the last crash
 * https://github.com/Microsoft/AppCenter-SDK-Apple/blob/develop/SasquatchMac/SasquatchMacObjC/AppCenterDelegateObjC.m
 * https://github.com/Microsoft/AppCenter-SDK-Android/blob/develop/sdk/appcenter-crashes/src/main/java/com/microsoft/appcenter/crashes/model/ErrorReport.java
 */
USTRUCT(BlueprintType)
struct FAppCenterErrorReport
{
	GENERATED_BODY()

public:
	FAppCenterErrorReport() {}

	// @TODO Implement class details https://github.com/PushkinStudio/AppCenter-SDK-UE4/issues/4
};
