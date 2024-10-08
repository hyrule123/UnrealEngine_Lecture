// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lecture : ModuleRules
{
    public string SourceCodeDir
    {
        get
        {
            return System.IO.Path.GetFullPath(
                ModuleDirectory //Build.cs 파일이 있는 주소를 추가한다.
                //System.IO.Path.Combine(ModuleDirectory,"..")
            );
        }
    }

    public Lecture(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	    
        //ModuleExample을 의존성 모듈에 추가한다.(이제 ModuleExample 없이는 빌드 불가)
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Json", "JsonUtilities", "ModuleExample" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange( new string[] { SourceCodeDir } );

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }


}
