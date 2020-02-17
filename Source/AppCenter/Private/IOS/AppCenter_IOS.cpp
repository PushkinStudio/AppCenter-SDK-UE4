// Copyright 2015-2020 Mail.Ru Group. All Rights Reserved.

#include "AppCenter_IOS.h"

#include "AppCenterDefines.h"
#include "AppCenterSettings.h"

#if PLATFORM_IOS
THIRD_PARTY_INCLUDES_START
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"
#pragma clang diagnostic ignored "-Wduplicate-protocol"

#if WITH_APPCENTER
#import <AppCenter/AppCenter.h>
#endif

#if WITH_APPCENTER_ANALYTICS
#import <AppCenterAnalytics/AppCenterAnalytics.h>
#endif

#if WITH_APPCENTER_CRASHES
#import <AppCenterCrashes/AppCenterCrashes.h>
#endif

#if WITH_APPCENTER_DISTIBUTE
#import <AppCenterDistribute/AppCenterDistribute.h>
#endif

#if WITH_APPCENTER_PUSH
#import <AppCenterPush/AppCenterPush.h>
#endif

#pragma clang diagnostic pop
THIRD_PARTY_INCLUDES_END
#endif // PLATFORM_IOS

#if PLATFORM_IOS
@implementation AppCenterObserver

static AppCenterObserver* AppCenterObserverInstance = nil;

- (id)init
{
	self = [super init];
	return self;
}

+ (void)load
{
	[super load];

	if (AppCenterObserverInstance == nil)
	{
		AppCenterObserverInstance = [[AppCenterObserver alloc] init];
		[AppCenterObserverInstance registerLifeCycleListener];
	}
}

- (void)registerLifeCycleListener
{
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(didFinishLaunching:)
												 name:UIApplicationDidFinishLaunchingNotification
											   object:nil];
}

- (void)didFinishLaunching:(NSNotification*)notification
{
#if WITH_APPCENTER
	NSDictionary* AppCenterDict = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"AppCenter"];
	if (AppCenterDict == nil)
	{
		NSLog(@"AppCenterSDK: Can't read plist properties.");
		return;
	}

	NSString* AppSecret = [AppCenterDict objectForKey:@"AppSecret"];
	if (AppSecret == nil)
	{
		NSLog(@"AppCenterSDK: AppSecret is not set.");
		return;
	}

	NSMutableArray* AppCenterModules = [[[NSMutableArray alloc] init] autorelease];

#if WITH_APPCENTER_ANALYTICS
	[AppCenterModules addObject:[MSAnalytics class]];
#endif

#if WITH_APPCENTER_CRASHES
	[AppCenterModules addObject:[MSCrashes class]];
#endif

#if WITH_APPCENTER_DISTIBUTE
	[AppCenterModules addObject:[MSDistribute class]];
#endif

#if WITH_APPCENTER_PUSH
	[AppCenterModules addObject:[MSPush class]];
#endif

	[MSAppCenter start:AppSecret
		  withServices:AppCenterModules];

#endif // WITH_APPCENTER
}

@end
#endif // PLATFORM_IOS && WITH_APPCENTER

UAppCenter_IOS::UAppCenter_IOS(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#if PLATFORM_IOS

/////////////////////////////////////////////////////////////////////////
// AppCenter Other APIs

#if WITH_APPCENTER
void UAppCenter_IOS::SetUserId(const FString& UserId)
{
	FString LocalUserId = UserId;

	dispatch_async(dispatch_get_main_queue(), ^{
	  [MSAppCenter setUserId:LocalUserId.GetNSString()];
	});
}
#endif // WITH_APPCENTER

/////////////////////////////////////////////////////////////////////////
// Analytics

#if WITH_APPCENTER_ANALYTICS
void UAppCenter_IOS::TrackEvent(const FString& EventName, const TMap<FString, FString>& Properties, EAppCenterEventPersistence EventPersistence)
{
	const FString LocalEventName = EventName;
	const TMap<FString, FString> LocalProperties = Properties;

	dispatch_async(dispatch_get_main_queue(), ^{
	  NSMutableDictionary* PropertiesDictionary = [[[NSMutableDictionary alloc] init] autorelease];
	  for (const auto& Elem : LocalProperties)
	  {
		  [PropertiesDictionary setValue:Elem.Value.GetNSString() forKey:Elem.Key.GetNSString()];
	  }

	  MSFlags PersistenceFlags = (EventPersistence == EAppCenterEventPersistence::PERSISTENCE_CRITICAL) ? MSFlagsCritical : MSFlagsNormal;
	  [MSAnalytics trackEvent:LocalEventName.GetNSString() withProperties:PropertiesDictionary flags:PersistenceFlags];
	});
}
#endif // WITH_APPCENTER_ANALYTICS

/////////////////////////////////////////////////////////////////////////
// Crashes

#if WITH_APPCENTER_CRASHES
void UAppCenter_IOS::GenerateTestCrash()
{
	dispatch_async(dispatch_get_main_queue(), ^{
	  [MSCrashes generateTestCrash];
	});
}

void UAppCenter_IOS::GenerateNativeCrash()
{
	abort();
}
#endif // WITH_APPCENTER_CRASHES

#endif // PLATFORM_IOS
