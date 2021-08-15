local detected_arch = io.popen('uname -m','r'):read('*l')

workspace "Build"
    language "C++"
    cppdialect "C++2a"
    configurations { "Debug", "Release" }
    platforms { "intel", "arm" }
    defaultplatform(detected_arch == "x86_64" and "intel" or "arm")
    filter "platforms:intel"
        architecture "x86_64"
        buildoptions { "-mmacosx-version-min=10.13", "-target x86_64-apple-macos10.13" }
        linkoptions "-target x86_64-apple-macos10.13"
    filter "platforms:arm"
        architecture "ARM"
        buildoptions { "-mmacosx-version-min=11", "-target arm64-apple-macos11" }
        linkoptions "-target arm64-apple-macos11"
    filter {}
    filter "configurations:Debug"
        optimize "Off"
    filter "configurations:Release"
        postbuildcommands {
            "strip -x %{cfg.linktarget.relpath}"
        }
        optimize "Speed"
    filter {}
    includedirs {
        "include/",
        "libs/"
    }
    objdir "build/obj"
    targetdir "build/%{cfg.architecture}/%{cfg.buildcfg}"

project "Interpreter"
    kind "ConsoleApp"
    files {
        "src/**.cpp",
        "src/main.cpp",
    }
    excludes {
        "src/repl.cpp",
    }

project "Repl"
    kind "ConsoleApp"
    files {
        "src/**.cpp",
        "src/repl.cpp",
    }
    excludes {
        "src/main.cpp",
    }

project "Tests"
    kind "ConsoleApp"
    files {
        "libs/catch2/catch_amalgamated.cpp",
        "src/**.cpp",
        "test/**.cpp"
    }
    excludes {
        "src/main.cpp",
        "src/repl.cpp"
    }
