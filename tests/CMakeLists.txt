cmake_minimum_required (VERSION 3.8)

include (CheckIncludeFileCXX)
check_include_file_cxx (catch2/catch_test_macros.hpp HAS_CATCH_V3_HEADER)
check_include_file_cxx (catch2/catch.hpp HAS_CATCH_V2_HEADER)

if (HAS_CATCH_V3_HEADER AND NOT HAS_CATCH_V2_HEADER)
  set(HAS_CATCH_V3 ON)
else ()
  set(HAS_CATCH_V3 OFF)
endif ()

# test binary for component tests
project(component_tests)

set(component_tests_sources
    ../src/EntryNotFoundException.cpp
    ../src/Ini.cpp
    ../src/IniSection.cpp
    ../src/StringFunctions.cpp
    EntryNotFoundException.cpp
    Ini.cpp
    IniSection.cpp
    StringFunctions.cpp
    main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions (-Wall -Wextra -Wpedantic -pedantic-errors -Wshadow -fexceptions)
    if (CODE_COVERAGE)
        add_definitions (-O0)
    else ()
        add_definitions (-O3)
    endif ()

    set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
endif ()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(component_tests ${component_tests_sources})

# MSYS2 / MinGW uses Catch 3.x.
if (HAS_CATCH_V3)
    find_package(Catch2 3 REQUIRED)
    target_link_libraries(component_tests Catch2::Catch2WithMain)
endif ()

# GNU GCC before 9.1.0 needs to link to libstdc++fs explicitly.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.1.0")
  target_link_libraries(component_tests stdc++fs)
endif ()

# Clang before 9.0 needs to link to libc++fs explicitly.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0")
    # If we are on Clang 7.x, then the filesystem library from GCC is better.
    target_link_libraries(component_tests stdc++fs)
  else ()
   # Use Clang's C++ filesystem library, it is recent enough.
   target_link_libraries(component_tests c++fs)
  endif ()
endif ()

# add test case
add_test(NAME test_components
         COMMAND $<TARGET_FILE:component_tests>)

if (NOT WIN32)
  set(EXT "sh")
else ()
  set(EXT "cmd")
endif()

# test for wrong arguments
add_test(NAME compare-ini_parameter_misuse
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/parameter-misuse.${EXT} $<TARGET_FILE:compare-ini>)
