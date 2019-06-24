OutDirPattern  = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
PchNamePattern = "%{prj.name}Pch"
SdlArchDirPattern = "%{cfg.architecture == 'x86' and 'x86' or 'x64'}"
Dependencies = {
	["SDL2"] = {
		LibSearchDir =  "vendor/SDL2-2.0.9/lib/" .. SdlArchDirPattern,
		IncludeDirs  = { "vendor/SDL2-2.0.9/include" },
		LibFileNames = { "SDL2", "SDL2main" },
		DllFileNames = { "SDL2" }
	},
	["SDL2_image"] = {
		LibSearchDir = "vendor/SDL2_image-2.0.4/lib/" .. SdlArchDirPattern,
		IncludeDirs  = { "vendor/SDL2_image-2.0.4/include" },
		LibFileNames = { "SDL2_image" },
		DllFileNames = { "SDL2_image", "libpng16-16", "zlib1" }
	},
	["Eigen"] = {
		IncludeDirs = { "vendor/eigen" }
	}
}

function CopyDllAtPostBuild(DllDir, DllName)
	-- Asterisk issue
	-- https://github.com/premake/premake-core/issues/1015
	postbuildcommands {
		"{COPY} %{wks.location}" .. DllDir .. "/" .. DllName .. ".dll " 
		.. "%{cfg.targetdir}/" .. DllName .. ".dll*"
	}
end

function InjectDependencies(DepNames)
	for _, DepName in ipairs(DepNames) do 
		local Dep = Dependencies[DepName]
		if not Dep then
			print("Failed to resolve dependency '" .. DepName .. "' you should add it to Dependencies table.")
			os.exit()
		end
		if Dep.LibSearchDir then libdirs { Dep.LibSearchDir } end
		if Dep.IncludeDirs  then includedirs(Dep.IncludeDirs) end
		if Dep.LibFileNames then links(Dep.LibFileNames) end
		if Dep.DllFileNames then
			for _, DllName in ipairs(Dep.DllFileNames) do 
				CopyDllAtPostBuild(Dep.LibSearchDir, DllName) 
			end
		end
	end
end

workspace "AirHockey" 
	configurations { "Debug", "Release" }
	architecture "x64"
	startproject "AirHockey"

project "AirHockey"
	location   "%{prj.name}"
	language   "C++"
	cppdialect "C++17"

	pchheader     (PchNamePattern .. ".h")    
	pchsource     ("%{prj.location}/src/" .. PchNamePattern .. ".cpp")
	forceincludes { "%{prj.pchheader}" }

	targetdir ("bin/"  .. OutDirPattern .. "/%{prj.name}")
	objdir ("bin-int/" .. OutDirPattern .. "/%{prj.name}")

	includedirs { "%{prj.location}/include" }

	InjectDependencies { 
		"SDL2", "SDL2_image", "Eigen"
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
		kind	"ConsoleApp"

	filter "configurations:Release"
		runtime  "Release"
		defines  { "NDEBUG" }
		optimize "On"
		kind     "WindowedApp" 