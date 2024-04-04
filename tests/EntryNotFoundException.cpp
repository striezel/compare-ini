/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for compare-ini.
    Copyright (C) 2024  Dirk Stolle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -------------------------------------------------------------------------------
*/

#include "locate_catch.hpp"
#include "../src/EntryNotFoundException.hpp"

TEST_CASE("EntryNotFoundException")
{
  SECTION("all in one: foo")
  {
    EntryNotFoundException ex{"foo"};
    REQUIRE_FALSE( ex.what() == nullptr );
    REQUIRE( ex.what() == std::string("The requested entry \"foo\" was not found!") );
  }

  SECTION("all in one: bar")
  {
    EntryNotFoundException ex{"bar"};
    REQUIRE_FALSE( ex.what() == nullptr );
    REQUIRE( ex.what() == std::string("The requested entry \"bar\" was not found!") );
  }
}
