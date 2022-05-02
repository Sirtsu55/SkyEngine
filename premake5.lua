



workspace "SkyEngine"
   configurations { "Debug", "Release", "Performance" }
   platforms { "Win64" }
   startproject "SkyCore"

      -- Disable Precompiled Headers in Vendor
   filter { "files:Vendor/**" }
      flags { "NoPCH" }


include "SkyCore/SkyCore.lua"	