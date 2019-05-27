# AppCenter-SDK-UE4
Development repository for the App Center SDK for Unreal Engine 4 platforms

## JFYI

Plugin is in active development stage for now, so there are few things you should know.

Modules implemented:

* Analytics (basic integration and events traking)
* Crashes
* Distribute

Platforms: both iOS and Android.

**nb!** Force ANSI allocator for iOS build! Just add `GlobalDefinitions.Add("FORCE_ANSI_ALLOCATOR=1");` to `YourProject.Target.cs`
