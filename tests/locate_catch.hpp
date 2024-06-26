/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for compare-ini.
    Copyright (C) 2024  Dirk Stolle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -------------------------------------------------------------------------------
*/

// This header tries to find the matching header for Catch (C++ Automated Test
// Cases in Headers).
#if defined(__has_include)
  #if __has_include(<catch2/catch.hpp>)
    // Catch version 2.x
    #include <catch2/catch.hpp>
  #elif __has_include(<catch2/catch_test_macros.hpp>)
    // Catch version 3.x
    #include <catch2/catch_approx.hpp>
    #include <catch2/catch_test_macros.hpp>
    #include <catch2/catch_version_macros.hpp>
  #else
    // Catch version 1.x
    #include <catch.hpp>
  #endif
#else
  // If there is no __has_include, just go with catch v1.
  #include <catch.hpp>
#endif
