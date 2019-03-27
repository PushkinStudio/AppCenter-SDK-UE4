// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "AppCenter_IOS.h"

#include "AppCenterDefines.h"
#include "AppCenterSettings.h"

#if PLATFORM_IOS
THIRD_PARTY_INCLUDES_START
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"
#pragma clang diagnostic ignored "-Wduplicate-protocol"
#import <AppCenter/AppCenter.h>
#import <AppCenterAnalytics/AppCenterAnalytics.h>
#import <AppCenterCrashes/AppCenterCrashes.h>
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
	[AppCenterModules addObject:[MSAnalytics class]];
	[AppCenterModules addObject:[MSCrashes class]];

	[MSAppCenter start:AppSecret withServices:AppCenterModules];
}

@end
#endif // PLATFORM_IOS

UAppCenter_IOS::UAppCenter_IOS(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#if PLATFORM_IOS

void UAppCenter_IOS::TestCrash()
{
}

void UAppCenter_IOS::TestNativeCrash()
{
	abort();
}

#endif // PLATFORM_IOS