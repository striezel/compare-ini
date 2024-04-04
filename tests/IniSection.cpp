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
#include "../src/IniSection.hpp"

TEST_CASE("IniSection")
{
  SECTION("addEntry / hasEntry / getValue")
  {
    SECTION("empty section")
    {
      IniSection section;
      REQUIRE_FALSE( section.hasEntry("foo") );
      REQUIRE_THROWS( section.getValue("foo") );
    }

    SECTION("add some values")
    {
      IniSection section;
      REQUIRE_FALSE( section.hasEntry("foo") );
      section.addEntry("foo", "bar value");
      REQUIRE( section.hasEntry("foo") );
      REQUIRE_NOTHROW( section.getValue("foo") );
      REQUIRE( section.getValue("foo") == "bar value" );

      REQUIRE_FALSE( section.hasEntry("bar") );
      REQUIRE_THROWS( section.getValue("bar") );
      section.addEntry("bar", "123");
      REQUIRE( section.hasEntry("bar") );
      REQUIRE( section.getValue("bar") == "123" );
    }
  }

  SECTION("getEntryNames")
  {
    IniSection section;
    REQUIRE( section.getEntryNames().empty() );

    section.addEntry("foo", "bar");
    auto names = section.getEntryNames();
    REQUIRE( names.size() == 1 );
    REQUIRE( names.at(0) == "foo" );

    section.addEntry("bar", "test");
    section.addEntry("quux", "test2");

    names = section.getEntryNames();
    REQUIRE( names.size() == 3 );
    REQUIRE( names.at(0) == "bar" );
    REQUIRE( names.at(1) == "foo" );
    REQUIRE( names.at(2) == "quux" );
  }

  SECTION("clear")
  {
    IniSection section;

    section.addEntry("foo", "bar");
    section.addEntry("bar", "test");
    section.addEntry("quux", "test2");

    REQUIRE( section.getEntryNames().size() == 3 );
    REQUIRE( section.hasEntry("foo") );
    REQUIRE( section.hasEntry("bar") );
    REQUIRE( section.hasEntry("quux") );

    section.clear();

    REQUIRE_FALSE( section.hasEntry("foo") );
    REQUIRE_FALSE( section.hasEntry("bar") );
    REQUIRE_FALSE( section.hasEntry("quux") );
    REQUIRE( section.getEntryNames().empty() );
  }

  SECTION("hasSameKeys")
  {
    IniSection a;
    IniSection b;

    SECTION("empty")
    {
      REQUIRE( a.hasSameKeys(b) );
      REQUIRE( b.hasSameKeys(a) );
    }

    SECTION("same keys (non-empty)")
    {
      SECTION("same keys, same values")
      {
        a.addEntry("foo", "1");
        a.addEntry("blob", "blah");
        b.addEntry("foo", "1");
        b.addEntry("blob", "blah");

        REQUIRE( a.hasSameKeys(b) );
        REQUIRE( b.hasSameKeys(a) );
      }

      SECTION("same keys, different values")
      {
        a.addEntry("foo", "1");
        b.addEntry("foo", "2");

        REQUIRE( a.hasSameKeys(b) );
        REQUIRE( b.hasSameKeys(a) );
      }
    }

    SECTION("different keys")
    {
      a.addEntry("foo", "1");
      REQUIRE_FALSE( a.hasSameKeys(b) );
      REQUIRE_FALSE( b.hasSameKeys(a) );

      b.addEntry("blob", "blah");
      REQUIRE_FALSE( a.hasSameKeys(b) );
      REQUIRE_FALSE( b.hasSameKeys(a) );
    }
  }

  SECTION("equality / inequality operator")
  {
    IniSection a;
    IniSection b;

    SECTION("empty")
    {
      REQUIRE( a == b );
      REQUIRE( b == a );

      REQUIRE_FALSE( a != b );
      REQUIRE_FALSE( b != a );
    }

    SECTION("same keys, same values")
    {
      a.addEntry("foo", "1");
      a.addEntry("blob", "blah");
      b.addEntry("foo", "1");
      b.addEntry("blob", "blah");

      REQUIRE( a == b );
      REQUIRE( b == a );

      REQUIRE_FALSE( a != b );
      REQUIRE_FALSE( b != a );
    }

    SECTION("same keys, different values")
    {
      a.addEntry("foo", "1");
      b.addEntry("foo", "2");

      REQUIRE_FALSE( a == b );
      REQUIRE_FALSE( b == a );

      REQUIRE( a != b );
      REQUIRE( b != a );
    }

    SECTION("different keys and values")
    {
      a.addEntry("foo", "1");
      REQUIRE_FALSE( a == b );
      REQUIRE_FALSE( b == a );

      REQUIRE( a != b );
      REQUIRE( b != a );

      b.addEntry("blob", "blah");
      REQUIRE_FALSE( a == b );
      REQUIRE_FALSE( b == a );

      REQUIRE( a != b );
      REQUIRE( b != a );
    }
  }
}
