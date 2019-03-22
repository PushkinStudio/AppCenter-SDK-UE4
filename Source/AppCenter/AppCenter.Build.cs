// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class AppCenter : ModuleRules
{
    public AppCenter(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
			}
            );


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


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicDependencyModuleNames.AddRange(new string[] { "Launch" });

            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "AppCenter_UPL_Android.xml"));

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

            PublicDefinitions.Add("WITH_APPCENTER=1");
        }
        else
        {
            PublicDefinitions.Add("WITH_APPCENTER=0");
        }
    }
}
