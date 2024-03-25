using UnrealBuildTool;

public class UnrealSpaceInvaders : ModuleRules
{
	public UnrealSpaceInvaders(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
