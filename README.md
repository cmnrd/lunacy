lunacy
======

The goal for this project is to create an efficient C++11 library for the AVR ATmega series.

Build
======

- install premake (version >=4.4) 
  (newest source at https://bitbucket.org/premake/premake-stable)

- run premake4 gmake to create build directory and generate makefiles
  --mmcu=X specifies the target platform
  --fcpu=X specifies the CPU frequency

- cd build and make
