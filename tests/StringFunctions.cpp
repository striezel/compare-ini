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
#include "../src/StringFunctions.hpp"

TEST_CASE("string functions")
{
  SECTION("trim")
  {
    SECTION("empty string")
    {
      std::string s;
      trim(s);
      REQUIRE( s.empty() );
    }

    SECTION("whitespace strings")
    {
      std::string s;

      s = " ";
      REQUIRE( !s.empty() );
      trim(s);
      REQUIRE( s.empty() );

      s = "       ";
      REQUIRE( !s.empty() );
      trim(s);
      REQUIRE( s.empty() );

      s = " \t   \t\t\t ";
      REQUIRE( !s.empty() );
      trim(s);
      REQUIRE( s.empty() );
    }

    SECTION("strings that will not be trimmed")
    {
      std::string s{"foo bar"};

      trim(s);
      REQUIRE( s == "foo bar" );

      s = "blob";
      trim(s);
      REQUIRE( s == "blob" );
    }

    SECTION("strings with removable characters at the beginning")
    {
      std::string s;

      s = " foo";
      trim(s);
      REQUIRE( s == "foo" );

      s = "\tbar";
      trim(s);
      REQUIRE( s == "bar" );

      s = "   \t\t \t baz";
      trim(s);
      REQUIRE( s == "baz" );
    }

    SECTION("strings with removable characters at the end")
    {
      std::string s;

      s = "foo ";
      trim(s);
      REQUIRE( s == "foo" );

      s = "bar\t";
      trim(s);
      REQUIRE( s == "bar" );

      s = "baz   \t\t \t ";
      trim(s);
      REQUIRE( s == "baz" );
    }

    SECTION("strings with removable characters at start and end")
    {
      std::string s;

      s = "\tfoo ";
      trim(s);
      REQUIRE( s == "foo" );

      s = " bar\t";
      trim(s);
      REQUIRE( s == "bar" );

      s = "\t    \t baz   \t\t \t ";
      trim(s);
      REQUIRE( s == "baz" );
    }
  }

  SECTION("removeEnclosingBrackets")
  {
    SECTION("short strings")
    {
      std::string s;

      REQUIRE_FALSE( removeEnclosingBrackets(s) );
      REQUIRE( s.empty() );

      s = "[";
      REQUIRE_FALSE( removeEnclosingBrackets(s) );
      REQUIRE( s == "[" );

      s = "]";
      REQUIRE_FALSE( removeEnclosingBrackets(s) );
      REQUIRE( s == "]" );
    }

    SECTION("strings without matching brackets")
    {
      std::string s;

      s = "foo";
      REQUIRE_FALSE( removeEnclosingBrackets(s) );
      REQUIRE( s == "foo" );

      s = "[foo";
      REQUIRE_FALSE( removeEnclosingBrackets(s) );
      REQUIRE( s == "[foo" );

      s = "foo]";
      REQUIRE_FALSE( removeEnclosingBrackets(s) );
      REQUIRE( s == "foo]" );
    }

    SECTION("strings with matching brackets")
    {
      std::string s;

      s = "[foo]";
      REQUIRE( removeEnclosingBrackets(s) );
      REQUIRE( s == "foo" );

      s = "[Bar]";
      REQUIRE( removeEnclosingBrackets(s) );
      REQUIRE( s == "Bar" );

      s = "[foo bar baz]";
      REQUIRE( removeEnclosingBrackets(s) );
      REQUIRE( s == "foo bar baz" );
    }
  }
}
