
using UnrealBuildTool;

public class UE5_CPP_Project : ModuleRules
{
	public UE5_CPP_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		PublicIncludePaths.Add(ModuleDirectory);

	}
}
