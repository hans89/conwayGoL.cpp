-- A solution contains projects, and defines the available configurations
solution "golcpp"
   configurations {"Debug", "Release"}

   configuration "Debug"
      defines "DEBUG" 
      flags "Symbols"
   
   configuration "Release"
      defines "NDEBUG"
      flags "Optimize"   

   -- A project defines one build target
   project "golcpp"
      kind "ConsoleApp"
      language "C++"
      files { "**.h", "**.cpp", "**.c", "**.hpp" }
      targetdir "bin"

      configuration "windows"
         -- buildoptions { "/MD" }
         links { "user32", "gdi32", "shell32"}
      
      configuration "linux"
         links { "pthread", "X11"}
         includedirs { "/usr/X11R6/include" }
         libdirs { "/usr/X11R6/lib" }
    
      configuration "macosx"
      -- OS X frameworks need the extension to be handled properly
         links { "m", "pthread", "X11"}
         includedirs { "/usr/X11R6/include" }
         libdirs { "/usr/X11R6/lib" }