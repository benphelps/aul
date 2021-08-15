workspace "Aul"
    language "C++"
    cppdialect "C++2a"
    configurations { "Debug", "Release" }
    includedirs {
        "include/",
        "libs/"
    }
    targetdir "build/%{cfg.buildcfg}"
    filter "configurations:Debug"
        optimize "Off"
    filter "configurations:Release"
        optimize "Speed"
    filter {}

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
