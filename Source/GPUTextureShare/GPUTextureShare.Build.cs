// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GPUTextureShare : ModuleRules
{
	public GPUTextureShare(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"RHI",
				"RenderCore",
			}
			);

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"D3D11RHI",
					"D3D12RHI",
				}
				);

			PublicSystemLibraries.AddRange(
				new string[]
				{
					"d3d11.lib",
					"d3d12.lib",
					"dxgi.lib",
				}
				);
		}
		else
		{
			PublicDefinitions.Add("GPUTEXTURESHARE_WINDOWS_ONLY=0");
		}

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicDefinitions.Add("GPUTEXTURESHARE_WINDOWS_ONLY=1");
		}

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
