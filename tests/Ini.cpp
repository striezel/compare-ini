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
#include "../src/Ini.hpp"
#include <sstream>
#include <string_view>

TEST_CASE("Ini")
{
  SECTION("getCommentCharacter")
  {
    Ini ini;

    SECTION("initial value")
    {
      REQUIRE( ini.getCommentCharacter() == ';' );
    }

    SECTION("set-get")
    {
      REQUIRE( ini.setCommentCharacter('#') );
      REQUIRE( ini.getCommentCharacter() == '#' );

      REQUIRE( ini.setCommentCharacter(':') );
      REQUIRE( ini.getCommentCharacter() == ':' );
    }
  }

  SECTION("setCommentCharacter")
  {
    Ini ini;

    SECTION("some allowed characters")
    {
      REQUIRE( ini.setCommentCharacter('!') );
      REQUIRE( ini.setCommentCharacter('#') );
      REQUIRE( ini.setCommentCharacter('$') );
      REQUIRE( ini.setCommentCharacter('%') );
      REQUIRE( ini.setCommentCharacter('&') );
      REQUIRE( ini.setCommentCharacter('*') );
      REQUIRE( ini.setCommentCharacter('+') );
      REQUIRE( ini.setCommentCharacter(',') );
      REQUIRE( ini.setCommentCharacter('-') );
      REQUIRE( ini.setCommentCharacter('.') );
      REQUIRE( ini.setCommentCharacter('/') );
      REQUIRE( ini.setCommentCharacter(':') );
      REQUIRE( ini.setCommentCharacter(';') );
      REQUIRE( ini.setCommentCharacter('|') );
      REQUIRE( ini.setCommentCharacter('~') );
    }

    SECTION("some disallowed characters")
    {
      REQUIRE_FALSE( ini.setCommentCharacter('\0') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x01') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x02') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x03') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x04') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x05') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x06') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x07') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x08') );
      REQUIRE_FALSE( ini.setCommentCharacter('\t') );
      REQUIRE_FALSE( ini.setCommentCharacter('\n') );
      REQUIRE_FALSE( ini.setCommentCharacter('\v') );
      REQUIRE_FALSE( ini.setCommentCharacter('\f') );
      REQUIRE_FALSE( ini.setCommentCharacter('\r') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x0E') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x0F') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x10') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x11') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x12') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x13') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x14') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x15') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x16') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x17') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x18') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x19') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x1A') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x1B') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x1C') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x1D') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x1E') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x1F') );
      REQUIRE_FALSE( ini.setCommentCharacter(' ') );
      REQUIRE_FALSE( ini.setCommentCharacter('[') );
      REQUIRE_FALSE( ini.setCommentCharacter('\x7F') );
    }

    SECTION("setting comment character actually changes comment character")
    {
      REQUIRE( ini.setCommentCharacter('~') );
      REQUIRE( ini.getCommentCharacter() == '~' );

      REQUIRE( ini.setCommentCharacter(';') );
      REQUIRE( ini.getCommentCharacter() == ';' );
    }
  }

  SECTION("addSection / hasSection / getSection")
  {
    SECTION("empty ini")
    {
      Ini ini;
      REQUIRE_FALSE( ini.hasSection("foo") );
      REQUIRE_THROWS( ini.getSection("foo") );
    }

    SECTION("add some values")
    {
      Ini ini;
      REQUIRE_FALSE( ini.hasSection("foo") );
      {
        IniSection section;
        section.addEntry("bar", "value");
        ini.addSection("foo", section);
      }
      REQUIRE( ini.hasSection("foo") );
      REQUIRE_NOTHROW( ini.getSection("foo") );
      REQUIRE( ini.getSection("foo").getValue("bar") == "value" );

      REQUIRE_FALSE( ini.hasSection("bar") );
      REQUIRE_THROWS( ini.getSection("bar") );

      {
        IniSection section;
        section.addEntry("blob", "123");
        ini.addSection("bar", section);
      }

      REQUIRE( ini.hasSection("bar") );
      REQUIRE( ini.getSection("bar").getValue("blob") == "123" );
    }
  }

  SECTION("getSectionNames")
  {
    Ini ini;
    REQUIRE( ini.getSectionNames().empty() );

    ini.addSection("foo", IniSection());
    auto names = ini.getSectionNames();
    REQUIRE( names.size() == 1 );
    REQUIRE( names.at(0) == "foo" );

    ini.addSection("bar", IniSection());
    ini.addSection("quux", IniSection());

    names = ini.getSectionNames();
    REQUIRE( names.size() == 3 );
    REQUIRE( names.at(0) == "bar" );
    REQUIRE( names.at(1) == "foo" );
    REQUIRE( names.at(2) == "quux" );
  }

  SECTION("clear")
  {
    Ini ini;

    ini.addSection("foo", IniSection());
    ini.addSection("bar", IniSection());
    ini.addSection("quux", IniSection());

    REQUIRE( ini.getSectionNames().size() == 3 );
    REQUIRE( ini.hasSection("foo") );
    REQUIRE( ini.hasSection("bar") );
    REQUIRE( ini.hasSection("quux") );

    ini.clear();

    REQUIRE_FALSE( ini.hasSection("foo") );
    REQUIRE_FALSE( ini.hasSection("bar") );
    REQUIRE_FALSE( ini.hasSection("quux") );
    REQUIRE( ini.getSectionNames().empty() );
  }

  SECTION("hasSameSectionNames")
  {
    Ini a;
    Ini b;

    SECTION("empty")
    {
      REQUIRE( a.hasSameSectionNames(b) );
      REQUIRE( b.hasSameSectionNames(a) );
    }

    SECTION("same sections (non-empty)")
    {
      SECTION("same sections, same entries")
      {
        IniSection foo;
        foo.addEntry("key", "1");

        IniSection blob;
        blob.addEntry("blub", "blah");

        a.addSection("foo", foo);
        a.addSection("blob", blob);
        b.addSection("foo", foo);
        b.addSection("blob", blob);

        REQUIRE( a.hasSameSectionNames(b) );
        REQUIRE( b.hasSameSectionNames(a) );
      }

      SECTION("same sections, different entries")
      {
        IniSection foo1;
        foo1.addEntry("key", "1");

        IniSection foo2;
        foo2.addEntry("what", "42");

        a.addSection("foo", foo1);
        b.addSection("foo", foo2);

        REQUIRE( a.hasSameSectionNames(b) );
        REQUIRE( b.hasSameSectionNames(a) );
      }
    }

    SECTION("different sections")
    {
      IniSection foo;
      foo.addEntry("key", "1");

      a.addSection("foo", foo);
      REQUIRE_FALSE( a.hasSameSectionNames(b) );
      REQUIRE_FALSE( b.hasSameSectionNames(a) );

      IniSection blob;
      blob.addEntry("blub", "blah");

      b.addSection("blob", blob);
      REQUIRE_FALSE( a.hasSameSectionNames(b) );
      REQUIRE_FALSE( b.hasSameSectionNames(a) );
    }
  }

  SECTION("equality operator")
  {
    Ini a;
    Ini b;

    SECTION("empty")
    {
      REQUIRE( a == b );
      REQUIRE( b == a );
    }

    SECTION("same sections, same entries")
    {
      IniSection foo;
      foo.addEntry("key", "1");

      IniSection blob;
      blob.addEntry("blub", "blah");

      a.addSection("foo", foo);
      a.addSection("blob", blob);
      b.addSection("foo", foo);
      b.addSection("blob", blob);

      REQUIRE( a == b );
      REQUIRE( b == a );
    }

    SECTION("same sections, different entries")
    {
      IniSection foo_1st;
      foo_1st.addEntry("key", "1");

      IniSection foo_2nd;
      foo_2nd.addEntry("nay", "12");

      a.addSection("foo", foo_1st);
      b.addSection("foo", foo_2nd);

      REQUIRE_FALSE( a == b );
      REQUIRE_FALSE( b == a );
    }

    SECTION("same sections, same entries, but different values")
    {
      IniSection foo_1st;
      foo_1st.addEntry("key", "1");

      IniSection foo_2nd;
      foo_2nd.addEntry("key", "2");

      a.addSection("foo", foo_1st);
      b.addSection("foo", foo_2nd);

      REQUIRE_FALSE( a == b );
      REQUIRE_FALSE( b == a );
    }

    SECTION("different sections and entries")
    {
      IniSection foo;
      foo.addEntry("key", "value");

      IniSection blob;
      blob.addEntry("blub", "blah");

      a.addSection("foo", foo);
      REQUIRE_FALSE( a == b );
      REQUIRE_FALSE( b == a );

      b.addSection("blob", blob);
      REQUIRE_FALSE( a == b );
      REQUIRE_FALSE( b == a );
    }
  }

  SECTION("read (stream-based)")
  {
    using namespace std::string_view_literals;

    SECTION("small ini with two sections")
    {
      const std::string_view data = "[hey]\nhello = world\n\n[next]\nkey = value\nnext=no\n"sv;
      std::istringstream stream;
      stream.str(std::string(data));

      Ini ini;
      unsigned int lines = 0;
      std::string error;

      REQUIRE( ini.read(stream, lines, error) );
      REQUIRE( error == "eof bit" );
      REQUIRE( lines == 6 );

      REQUIRE( ini.hasSection("hey") );
      REQUIRE( ini.getSection("hey").hasEntry("hello") );
      REQUIRE( ini.getSection("hey").getValue("hello") == "world" );

      REQUIRE( ini.hasSection("next") );
      REQUIRE( ini.getSection("next").hasEntry("key") );
      REQUIRE( ini.getSection("next").getValue("key") == "value" );
      REQUIRE( ini.getSection("next").hasEntry("next") );
      REQUIRE( ini.getSection("next").getValue("next") == "no" );
    }

    SECTION("ini with comment")
    {
      const std::string_view data = "; This is a comment.\n[Settings]\ncomments = yes\n"sv;
      std::istringstream stream;
      stream.str(std::string(data));

      Ini ini;
      unsigned int lines = 0;
      std::string error;

      REQUIRE( ini.read(stream, lines, error) );
      REQUIRE( error == "eof bit" );
      REQUIRE( lines == 3 );

      REQUIRE( ini.hasSection("Settings") );
      REQUIRE( ini.getSection("Settings").hasEntry("comments") );
      REQUIRE( ini.getSection("Settings").getValue("comments") == "yes" );
    }

    SECTION("corrupt data: no closing bracket")
    {
      const std::string_view data = "[Settings\ncomments = yes\n"sv;
      std::istringstream stream;
      stream.str(std::string(data));

      Ini ini;
      unsigned int lines = 0;
      std::string error;

      REQUIRE_FALSE( ini.read(stream, lines, error) );
      REQUIRE( error == "No closing bracket in section line!" );
      REQUIRE( lines == 1 );

      REQUIRE_FALSE( ini.hasSection("Settings") );
    }

    SECTION("corrupt data: empty section name")
    {
      const std::string_view data = "[]\ncomments = yes\n"sv;
      std::istringstream stream;
      stream.str(std::string(data));

      Ini ini;
      unsigned int lines = 0;
      std::string error;

      REQUIRE_FALSE( ini.read(stream, lines, error) );
      REQUIRE( error == "Empty section name!" );
      REQUIRE( lines == 1 );

      REQUIRE( ini.getSectionNames().empty() );
    }

    SECTION("corrupt data: missing equality sign")
    {
      const std::string_view data = "[Settings]\ncomments yes\n"sv;
      std::istringstream stream;
      stream.str(std::string(data));

      Ini ini;
      unsigned int lines = 0;
      std::string error;

      REQUIRE_FALSE( ini.read(stream, lines, error) );
      REQUIRE( error == "No equality sign in key-value line!" );
      REQUIRE( lines == 2 );

      REQUIRE( ini.hasSection("Settings") );
      REQUIRE( ini.getSection("Settings").getEntryNames().empty() );
    }

    SECTION("corrupt data: empty key")
    {
      const std::string_view data = "[Settings]\n = yes\n"sv;
      std::istringstream stream;
      stream.str(std::string(data));

      Ini ini;
      unsigned int lines = 0;
      std::string error;

      REQUIRE_FALSE( ini.read(stream, lines, error) );
      REQUIRE( error == "Empty key name!" );
      REQUIRE( lines == 2 );

      REQUIRE( ini.hasSection("Settings") );
      REQUIRE( ini.getSection("Settings").getEntryNames().empty() );
    }
  }
}
