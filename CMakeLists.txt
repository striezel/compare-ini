cmake_minimum_required (VERSION 3.8)

project(compare-ini)

set(compare_ini_sources
    Compare.cpp
    EntryNotFoundException.cpp
    Ini.cpp
    IniSection.cpp
    StringFunctions.cpp
    main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions (-Wall -Wextra -pedantic -O3 -fexceptions)

    set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(compare-ini ${compare_ini_sources})
