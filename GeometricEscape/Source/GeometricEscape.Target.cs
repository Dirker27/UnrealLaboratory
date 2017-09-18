// Copyright ToasterCat Productions, LLC.

using UnrealBuildTool;
using System.Collections.Generic;

public class GeometricEscapeTarget : TargetRules
{
	public GeometricEscapeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "GeometricEscape" } );
	}
}
