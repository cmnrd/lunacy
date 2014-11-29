local GCC_AVR_CC_PATH = "/usr/bin/avr-gcc"
local GCC_AVR_CPP_PATH = "/usr/bin/avr-g++"
local GCC_AVR_AR_PATH = "/usr/bin/avr-ar"

premake.gcc.cc = GCC_AVR_CC_PATH
premake.gcc.cxx = GCC_AVR_CPP_PATH
premake.gcc.ar = GCC_AVR_AR_PATH

solution "lunacy"

--------------------------------------------------------------------------------
-- Command line options
--------------------------------------------------------------------------------

newoption { 
  trigger     = "mmcu", 
  description = "Chose the target platform (default = atmega8", 
  value="MMCU",
  allowed = {
    { "atmega8",  "ATmega8" },
    { "test",  "Test" }
  }
}

newoption { 
  trigger     = "fcpu", 
  description = "Specify the CPU frequency (default = 8000000)", 
  value="FCPU"
}

--------------------------------------------------------------------------------
-- Premake settings
--------------------------------------------------------------------------------

location "build"
language "C++"
kind "ConsoleApp"

--------------------------------------------------------------------------------
-- General build settings
--------------------------------------------------------------------------------

-- Includes
includedirs { "include" }
-- Enables some additional warnings.
buildoptions { "-Wall" }
-- Enables C++11 support.
buildoptions { "-std=c++11 " }
-- set AVR specific options
buildoptions {"-fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields"}

if _OPTIONS["mmcu"] then
  buildoptions { "-mmcu=" .. _OPTIONS["mmcu"] }
end

if _OPTIONS["fcpu"] then
  defines { "F_CPU=" .. _OPTIONS["fcpu"] }
end

--------------------------------------------------------------------------------
-- Configurations
--------------------------------------------------------------------------------
configurations { "release", "debug" }

configuration "release"
  objdir "build/bin/obj"
  targetdir "build/bin"

configuration "debug"
  objdir "build/dbg/obj"
  targetdir "build/dbg"

--------------------------------------------------------------------------------
-- Projects
--------------------------------------------------------------------------------
project "iomm"
  files { "test/avr/iomm.cpp" }
  targetname (project().name .. ".elf")
  postbuildcommands { "avr-objcopy -O ihex bin/" .. project().name .. ".elf bin/"  .. project().name .. ".hex"}
  postbuildcommands { "avr-size bin/" .. project().name .. ".elf"}
  
project "typelist"
  files { "test/mpl/typelist.cpp" }
  targetname (project().name .. ".elf")
  postbuildcommands { "avr-objcopy -O ihex bin/" .. project().name .. ".elf bin/"  .. project().name .. ".hex"}
  postbuildcommands { "avr-size bin/" .. project().name .. ".elf"}

-- Add new projects here

-- Template:
-- project "name"            <- edit
--   files { "source.cpp"v}  <- edit
--   targetname (project().name .. ".elf")
--   postbuildcommands { "avr-objcopy -O ihex bin/" .. project().name .. ".elf bin/"  .. project().name .. ".hex"}
--   postbuildcommands { "avr-size bin/" .. project().name .. ".elf"}
