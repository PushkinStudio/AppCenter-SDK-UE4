# AppCenter-SDK-UE4

Development repository for the App Center SDK for Unreal Engine 4 platforms

## JFYI

Plugin is in active development stage and being used on prod in a few project (e.g. [Armored Warfare: Assault](http://awa.my.com/)). It's well tested and double-checked, but as its primary target is limited to our own games only selected features are implemented.

* Analytics (basic integration and events traking)
* Crashes
* Distribute

Platforms: both iOS and Android.

**nb!** Force ANSI allocator for iOS build! Just add `GlobalDefinitions.Add("FORCE_ANSI_ALLOCATOR=1");` to `YourProject.Target.cs`
