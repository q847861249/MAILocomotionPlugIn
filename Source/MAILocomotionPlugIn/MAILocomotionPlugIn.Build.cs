// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MAILocomotionPlugIn : ModuleRules
{
	public MAILocomotionPlugIn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.Add("ControlRig/Private");
        PrivateIncludePaths.Add("ControlRigEditor/Private");
			
		
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
                "BlueprintGraph",
                "GameplayTags",
                "ControlRig",
                "ControlRigDeveloper",
                "AnimGraph",
                "PropertyEditor",
				"AnimGraphRuntime",
                "ToolMenus",
                "UnrealEd",





                
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
          
				// ... add any modules that your module loads dynamically here ...
			}
			);
    }
}
