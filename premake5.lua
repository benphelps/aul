local detected_arch = io.popen('uname -m','r'):read('*l')

workspace "Build"
    configurations { "Debug", "Release" }
    platforms { "intel", "arm" }
    defaultplatform(detected_arch == "x86_64" and "intel" or "arm")
    filter { "platforms:intel" }
        architecture "x86_64"
        buildoptions { "-mmacosx-version-min=10.13", "-target x86_64-apple-macos10.13" }
        linkoptions "-target x86_64-apple-macos10.13"
    filter { "platforms:arm" }
        architecture "ARM"
        buildoptions { "-mmacosx-version-min=11", "-target arm64-apple-macos11" }
        linkoptions "-target arm64-apple-macos11"
    filter {}
    objdir "build/obj"

project "Interpreter"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++2a"
    targetdir "build/%{cfg.architecture}/%{cfg.buildcfg}"
    includedirs {
        "include/"
    }
    files {
        "src/main.cpp",
        "src/**.cpp"
    }
    filter "configurations:Debug"
        optimize "Off"
    filter "configurations:Release"
        postbuildcommands {
            "strip -x %{cfg.linktarget.relpath}",
            "codesign -fs - %{cfg.linktarget.relpath}"
        }
        optimize "Speed"
        visibility "Hidden"
    filter {}

project "Tests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++2a"
    targetdir "build/%{cfg.architecture}/%{cfg.buildcfg}"
    includedirs {
        "include/"
    }
    files {
        "include/catch2/catch_amalgamated.cpp",
        "src/**.cpp",
        "test/**.cpp"
    }
    excludes {
        "src/main.cpp",
    }
    filter "configurations:Debug"
        optimize "Off"
    filter "configurations:Release"
        postbuildcommands {
            "strip -x %{cfg.linktarget.relpath}",
            "codesign -fs - %{cfg.linktarget.relpath}"
        }
        optimize "Speed"
        visibility "Hidden"
    filter {}
