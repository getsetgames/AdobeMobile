//
//  Created by Robert Segal on 2016-02-04.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

using System;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class AdobeMobile : ModuleRules
	{
		public AdobeMobile(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
					"../../../../Source/Runtime/Core/Public",
					"../../../../Source/Runtime/Launch/Public"
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"AdobeMobile/Private"
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine"
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
				
			PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"Settings"
			}
			);

			PublicIncludePathModuleNames.Add("Launch");

			String JSONConfigFile = Path.Combine(ModuleDirectory,"..","..","lib","ADBMobileConfig.json");
			String RSID           = File.ReadAllText(JSONConfigFile);

			// Dump in new placeholders to signfiy build configurations being used.  Final RSID replacement will 
			// be done in IPL/APL script
			//
			if (Target.Configuration == UnrealTargetConfiguration.Development)
			{
				RSID = RSID.Replace("$${tracking-rsid}$$", "$${tracking-rsid-development}$$");
			}
			else if (Target.Configuration == UnrealTargetConfiguration.Shipping)
			{
				RSID = RSID.Replace("$${tracking-rsid}$$", "$${tracking-rsid-shipping}$$");
			}

			String JSONIntermediateConfigFile = Path.Combine(ModuleDirectory,"..","..","lib","ADBMobileConfig.intermediate.json");

			File.WriteAllText(JSONIntermediateConfigFile, RSID);

			if (Target.Platform == UnrealTargetPlatform.IOS) {
				var LibDir = Path.Combine(ModuleDirectory,"..","..","lib","iOS");
				PrivateIncludePaths.Add(LibDir);

				PublicAdditionalLibraries.Add(Path.Combine(LibDir,"AdobeMobileLibrary.a"));
				PublicAdditionalLibraries.Add("sqlite3");

				PublicFrameworks.AddRange( 
					new string[] 
					{ 
						"SystemConfiguration"
					}
				);

				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add(new ReceiptProperty("IOSPlugin", Path.Combine(PluginPath, "AdobeMobile_IPL.xml")));
			}
			else if(Target.Platform == UnrealTargetPlatform.Android)
			{
				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "AdobeMobile_APL.xml")));
			}
		}
	}
}
