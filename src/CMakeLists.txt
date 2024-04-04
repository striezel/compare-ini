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
    add_definitions (-Wall -Wextra -pedantic -pedantic-errors -Wshadow -O3 -fexceptions)

    set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(compare-ini ${compare_ini_sources})


# #################### #
# tests for executable #
# #################### #

# add tests for --version and --help parameters
# default help parameter "--help"
add_test(NAME compare-ini_help
         COMMAND $<TARGET_FILE:compare-ini> --help)

# short help parameter with question mark "-?"
add_test(NAME compare-ini_help_question_mark
         COMMAND $<TARGET_FILE:compare-ini> -?)

# Windows-style help parameter "/?"
if (NOT DEFINED ENV{GITHUB_ACTIONS} OR NOT MINGW)
    add_test(NAME compare-ini_help_question_mark_windows
             COMMAND $<TARGET_FILE:compare-ini> /?)
endif ()
# parameter to show license information
add_test(NAME compare-ini_license
         COMMAND $<TARGET_FILE:compare-ini> --license)

# parameter to show version number
add_test(NAME compare-ini_version
         COMMAND $<TARGET_FILE:compare-ini> --version)
