using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealSpaceInvadersEditorTarget : TargetRules
{
	public UnrealSpaceInvadersEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "UnrealSpaceInvaders" } );
	}
}
