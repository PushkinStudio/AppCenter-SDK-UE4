// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

using System.IO;
using UnrealBuildTool;
using Tools.DotNETCommon;

public class AppCenter : ModuleRules
{
    public AppCenter(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                // ... add other public dependencies that you statically link with here ...
            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                // ... add private dependencies that you statically link with here ...	
            }
            );

        // Setup platform include paths
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateIncludePaths.Add("AppCenter/Private/Android");
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PrivateIncludePaths.Add("AppCenter/Private/IOS");
        }

        // Configure build defines
        bool bAppCenterEnabled = false;
        bool bEnableAnalytics = false;
        bool bEnableAuth = false;
        bool bEnableCrashes = false;
        bool bEnableData = false;
        bool bEnableDistribute = false;
        bool bEnablePush = false;
        string AppSecretAndroid = "";
        string AppSecretIOS = "";

        // Read from config
        ConfigHierarchy Ini = ConfigCache.ReadHierarchy(ConfigHierarchyType.Engine, Target.ProjectFile.Directory, Target.Platform);

        string SettingsSection = "/Script/AppCenter.AppCenterSettings";
        Ini.GetBool(SettingsSection, "bEnableAnalytics", out bEnableAnalytics);
        Ini.GetBool(SettingsSection, "bEnableAuth", out bEnableAuth);
        Ini.GetBool(SettingsSection, "bEnableCrashes", out bEnableCrashes);
        Ini.GetBool(SettingsSection, "bEnableData", out bEnableData);
        Ini.GetBool(SettingsSection, "bEnableDistribute", out bEnableDistribute);
        Ini.GetBool(SettingsSection, "bEnablePush", out bEnablePush);
        Ini.GetString(SettingsSection, "AppSecretAndroid", out AppSecretAndroid);
        Ini.GetString(SettingsSection, "AppSecretIOS", out AppSecretIOS);
        bool bAnyModuleEnabled = (bEnableAnalytics | bEnableAuth | bEnableCrashes | bEnableData | bEnableDistribute | bEnablePush);

        if(bAnyModuleEnabled)
        {
            if (Target.Platform == UnrealTargetPlatform.Android && AppSecretAndroid != "")
            {
                bAppCenterEnabled = true;

                PublicDependencyModuleNames.AddRange(new string[] { "Launch" });

                string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "AppCenter_UPL_Android.xml"));

                if (bEnableCrashes)
                {
                    /** 
                     * Application.mk
                     * 
                     * APP_STL := gnustl_static
                     * APP_ABI := armeabi-v7a, arm64-v8a
                     * APP_CXXFLAGS := -std=c++11 -D__STDC_LIMIT_MACROS
                     * APP_PLATFORM := android-19
                     */
                    string ThirdPartyPath = Path.Combine(ModuleDirectory, "..", "ThirdParty");
                    PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Breakpad", "src"));

                    PublicLibraryPaths.Add(Path.Combine(ThirdPartyPath, "Breakpad", "lib", "armeabi-v7a"));
                    PublicLibraryPaths.Add(Path.Combine(ThirdPartyPath, "Breakpad", "lib", "arm64-v8a"));
                    PublicAdditionalLibraries.Add("breakpad_client");
                }
            }
            else if (Target.Platform == UnrealTargetPlatform.IOS && AppSecretIOS != "")
            {
                bAppCenterEnabled = true;

                string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "AppCenter_UPL_IOS.xml"));

                // The AppCenter.framework is required to start the SDK. If it is not added to the project, 
                // the other modules won't work and your app won't compile.
                PublicAdditionalFrameworks.Add(
                    new UEBuildFramework(
                        "AppCenter",
                        "../../ThirdParty/AppCenter-SDK-Apple/iOS/AppCenter.embeddedframework.zip"
                    )
                );

                if (bEnableAnalytics)
                {
                    PublicAdditionalFrameworks.Add(
                        new UEBuildFramework(
                            "AppCenterAnalytics",
                            "../../ThirdParty/AppCenter-SDK-Apple/iOS/AppCenterAnalytics.embeddedframework.zip"
                        )
                    );
                }

                if (bEnableAuth) {
                    PublicAdditionalFrameworks.Add(
                        new Framework(
                            "AppCenterAuth",
                            "../../ThirdParty/AppCenter-SDK-Apple/iOS/AppCenterAuth.embeddedframework.zip"
                        )
                    );
                }

                if (bEnableCrashes)
                {
                    PublicAdditionalFrameworks.Add(
                        new UEBuildFramework(
                            "AppCenterCrashes",
                            "../../ThirdParty/AppCenter-SDK-Apple/iOS/AppCenterCrashes.embeddedframework.zip"
                        )
                    );
                }

                if (bEnableData) {
                    PublicAdditionalFrameworks.Add(
                        new Framework(
                            "AppCenterData",
                            "../../ThirdParty/AppCenter-SDK-Apple/iOS/AppCenterData.embeddedframework.zip"
                        )
                    );
                }

                if (bEnableDistribute)
                {
                    PublicAdditionalFrameworks.Add(
                        new UEBuildFramework(
                            "AppCenterDistribute",
                            "../../ThirdParty/AppCenter-SDK-Apple/iOS/AppCenterDistribute.embeddedframework.zip",
                            "AppCenterDistributeResources.bundle"
                        )
                    );
                }

                if (bEnablePush)
                {
                    PublicAdditionalFrameworks.Add(
                        new UEBuildFramework(
                            "AppCenterPush",
                            "../../ThirdParty/AppCenter-SDK-Apple/iOS/AppCenterPush.embeddedframework.zip"
                        )
                    );
                }
            }
        }

        // Setup defines based on reality
        if(bAppCenterEnabled) 
        {
            PublicDefinitions.Add("WITH_APPCENTER=" + (bAnyModuleEnabled ? "1" : "0"));
            PublicDefinitions.Add("WITH_APPCENTER_ANALYTICS=" + (bEnableAnalytics ? "1" : "0"));
            PublicDefinitions.Add("WITH_APPCENTER_AUTH=" + (bEnableAuth ? "1" : "0"));
            PublicDefinitions.Add("WITH_APPCENTER_CRASHES=" + (bEnableCrashes ? "1" : "0"));
            PublicDefinitions.Add("WITH_APPCENTER_DATA=" + (bEnableData ? "1" : "0"));
            PublicDefinitions.Add("WITH_APPCENTER_DISTIBUTE=" + (bEnableDistribute ? "1" : "0"));
            PublicDefinitions.Add("WITH_APPCENTER_PUSH=" + (bEnablePush ? "1" : "0"));
        }
        else 
        {
            PublicDefinitions.Add("WITH_APPCENTER=0");
            PublicDefinitions.Add("WITH_APPCENTER_ANALYTICS=0");
            PublicDefinitions.Add("WITH_APPCENTER_AUTH=0");
            PublicDefinitions.Add("WITH_APPCENTER_CRASHES=0");
            PublicDefinitions.Add("WITH_APPCENTER_DATA=0");
            PublicDefinitions.Add("WITH_APPCENTER_DISTIBUTE=0");
            PublicDefinitions.Add("WITH_APPCENTER_PUSH=0");
        }
    }
}
