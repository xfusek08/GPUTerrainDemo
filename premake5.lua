workspace "GPUTerrainDemo"
	architecture "x64"
	startproject "GPUTerrainDemo"

	configurations
	{
		"Debug",
		"Release"
	}

project "GPUTerrainDemo"
	location "GPUTerrainDemo"
	kind "ConsoleApp"
  language "C++"
  staticruntime "off"

  objdir ("bin-objs")

  configuration "Debug"
    targetdir "bin/debug"

  configuration "Release"
    targetdir "bin/release"s

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
    "src/"
	}

	links
	{
    -- resolve Qt
    -- GPUEngine
    -- GPUTerrain
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines -- windows makra definitions
		{
		}

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "On"
