// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

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
	}

	NSString* AppSecret = [AppCenterDict objectForKey:@"AppSecret"];
	if (AppSecret == nil)
	{
		NSLog(@"AppCenterSDK: AppSecret is not set.");
		return;
	}

	NSMutableArray* AppCenterModules = [[NSMutableArray alloc] init];

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

void UAppCenter_IOS::GenerateTestCrash()
{
	[MSCrashes generateTestCrash];
}

void UAppCenter_IOS::GenerateNativeCrash()
{
	abort();
}

#endif // PLATFORM_IOS