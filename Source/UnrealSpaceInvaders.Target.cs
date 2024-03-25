using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealSpaceInvadersTarget : TargetRules
{
	public UnrealSpaceInvadersTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "UnrealSpaceInvaders" } );
	}
}
