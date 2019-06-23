OutDirPattern  = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
PchNamePattern = "%{prj.name}Pch"
SdlArchDirPattern = "%{cfg.architecture == 'x86' and 'x86' or 'x64'}"
Dependencies = {
	["SDL2"] = {
		IncludeDir = "vendor/SDL2-2.0.9/include",
		LibDir     = "vendor/SDL2-2.0.9/lib/" .. SdlArchDirPattern
	},
	["SDL2main"] = {},
	["SDL2_image"] = {
		IncludeDir = "vendor/SDL2_image-2.0.4/include",
		LibDir     = "vendor/SDL2_image-2.0.4/lib/" .. SdlArchDirPattern
	}
}

function InjectDependencies(DepNames)
	for _, DepName in ipairs(DepNames) do 
		local Dep = Dependencies[DepName]
		if not Dep then
			print("Failed to resolve dependency '" .. DepName .. "' you should add it to Dependencies table.")
			os.exit()
		end
		links { DepName }
		if Dep.IncludeDir then includedirs { Dep.IncludeDir } end
		if Dep.LibDir     then 
			libdirs { Dep.LibDir } 
			copylocal { DepName }
			-- Asterisk issue
			-- https://github.com/premake/premake-core/issues/1015
			postbuildcommands {
				"{COPY} %{wks.location}" .. Dep.LibDir .. "/" .. DepName .. ".dll " 
				.. "%{cfg.targetdir}/" .. DepName .. ".dll*"
			}
		end
	end
end

workspace "AirHockey" 
	configurations { "Debug", "Release" }
	architecture "x64"
	startproject "AirHockey"

project "AirHockey"
	location   "%{prj.name}"
	kind	   "WindowedApp"
	language   "C++"
	cppdialect "C++17"

	pchheader     (PchNamePattern .. ".h")    
	pchsource     ("%{prj.location}/src/" .. PchNamePattern .. ".cpp")
	forceincludes { "%{prj.pchheader}" }

	targetdir ("bin/"  .. OutDirPattern .. "/%{prj.name}")
	objdir ("bin-int/" .. OutDirPattern .. "/%{prj.name}")

	includedirs { "%{prj.location}/include" }

	InjectDependencies { 
		"SDL2", "SDL2main", "SDL2_image"
	}

	files { 
		"%{prj.location}/include/**.h", 
		"%{prj.location}/src/**.cpp" 
	}

	filter "system:windows"
		
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		defines { "NDEBUG" }
		optimize "On"