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
  SECTION("addValue / hasValue / getValue")
  {
    SECTION("empty section")
    {
      IniSection section;
      REQUIRE_FALSE( section.hasValue("foo") );
      REQUIRE_THROWS( section.getValue("foo") );
    }

    SECTION("add some values")
    {
      IniSection section;
      REQUIRE_FALSE( section.hasValue("foo") );
      section.addValue("foo", "bar value");
      REQUIRE( section.hasValue("foo") );
      REQUIRE_NOTHROW( section.getValue("foo") );
      REQUIRE( section.getValue("foo") == "bar value" );

      REQUIRE_FALSE( section.hasValue("bar") );
      REQUIRE_THROWS( section.getValue("bar") );
      section.addValue("bar", "123");
      REQUIRE( section.hasValue("bar") );
      REQUIRE( section.getValue("bar") == "123" );
    }
  }

  SECTION("getValueNames")
  {
    IniSection section;
    REQUIRE( section.getValueNames().empty() );

    section.addValue("foo", "bar");
    auto names = section.getValueNames();
    REQUIRE( names.size() == 1 );
    REQUIRE( names.at(0) == "foo" );

    section.addValue("bar", "test");
    section.addValue("quux", "test2");

    names = section.getValueNames();
    REQUIRE( names.size() == 3 );
    REQUIRE( names.at(0) == "bar" );
    REQUIRE( names.at(1) == "foo" );
    REQUIRE( names.at(2) == "quux" );
  }

  SECTION("clear")
  {
    IniSection section;

    section.addValue("foo", "bar");
    section.addValue("bar", "test");
    section.addValue("quux", "test2");

    REQUIRE( section.getValueNames().size() == 3 );
    REQUIRE( section.hasValue("foo") );
    REQUIRE( section.hasValue("bar") );
    REQUIRE( section.hasValue("quux") );

    section.clear();

    REQUIRE_FALSE( section.hasValue("foo") );
    REQUIRE_FALSE( section.hasValue("bar") );
    REQUIRE_FALSE( section.hasValue("quux") );
    REQUIRE( section.getValueNames().empty() );
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
        a.addValue("foo", "1");
        a.addValue("blob", "blah");
        b.addValue("foo", "1");
        b.addValue("blob", "blah");

        REQUIRE( a.hasSameKeys(b) );
        REQUIRE( b.hasSameKeys(a) );
      }

      SECTION("same keys, different values")
      {
        a.addValue("foo", "1");
        b.addValue("foo", "2");

        REQUIRE( a.hasSameKeys(b) );
        REQUIRE( b.hasSameKeys(a) );
      }
    }

    SECTION("different keys")
    {
      a.addValue("foo", "1");
      REQUIRE_FALSE( a.hasSameKeys(b) );
      REQUIRE_FALSE( b.hasSameKeys(a) );

      b.addValue("blob", "blah");
      REQUIRE_FALSE( a.hasSameKeys(b) );
      REQUIRE_FALSE( b.hasSameKeys(a) );
    }
  }

  SECTION("hasSameValues")
  {
    IniSection a;
    IniSection b;

    SECTION("empty")
    {
      REQUIRE( a.hasSameValues(b) );
      REQUIRE( b.hasSameValues(a) );
    }

    SECTION("same keys, same values")
    {
      a.addValue("foo", "1");
      a.addValue("blob", "blah");
      b.addValue("foo", "1");
      b.addValue("blob", "blah");

      REQUIRE( a.hasSameValues(b) );
      REQUIRE( b.hasSameValues(a) );
    }

    SECTION("same keys, different values")
    {
      a.addValue("foo", "1");
      b.addValue("foo", "2");

      REQUIRE_FALSE( a.hasSameValues(b) );
      REQUIRE_FALSE( b.hasSameValues(a) );
    }

    SECTION("different keys and values")
    {
      a.addValue("foo", "1");
      REQUIRE_FALSE( a.hasSameValues(b) );
      REQUIRE_FALSE( b.hasSameValues(a) );

      b.addValue("blob", "blah");
      REQUIRE_FALSE( a.hasSameValues(b) );
      REQUIRE_FALSE( b.hasSameValues(a) );
    }
  }
}
