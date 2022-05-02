project "SkyCore"


   location "%{wks.location}/SkyCore"
   kind "consoleapp"

   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   cppdialect "C++20"


   -- Make Precompiled Headers
   pchheader "SkyCore.h"
   pchsource "Source/SkyCore.cpp"




   --Shaders
   files {  "%{wks.location}/SkyCore/Shaders/**"}


   -- Vendor Files
   files {  "%{wks.location}/Vendor/**.cpp", "%{wks.location}/Vendor/**.c",
            "%{wks.location}/Vendor/**.h",   "%{wks.location}/Vendor/**.hpp",
            "%{wks.location}/Vendor/**.inl"}
           
            

   files {  "%{wks.location}/SkyCore/Source/**.cpp",
            "%{wks.location}/SkyCore/Source/**.h"}

   -- Misc Files
   files {  "SkyCore.lua"}


   -- Include Directories
   includedirs {"%{wks.location}/Vendor/", "Source/",
                os.getenv("VK_SDK_PATH").. "/Include/" }


       -- Link Libraries
   libdirs {
            "%{wks.location}/Dependencies/GLFW",                         
            "%{wks.location}/Dependencies/lua",
            os.getenv("VK_SDK_PATH").. "/Lib/"
            }


   links {"glfw3", "luajit", "opengl32"}





   filter "configurations:Debug"
      defines { "DEBUG", "NLOG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
     filter "configurations:Performance"
      defines { "NDEBUG" }
      optimize "Full"