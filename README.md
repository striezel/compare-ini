# compare-ini, version 0.03

compare-ini is a program that can compare contents of ini files side by side.
It's command line only, so no "nice" GUI but just text output.


## What kind of ini files can compare-ini compare?

The program makes a few assumptions about the ini files:

* Sections are marked by square brackets (i.e. [Section]).
* Keys and values are delimited by equality sign (=).
* Keys and values are case-sensitive.
* Keys names within a section are unique, so there should not be two keys
  with same name but different values within one section. If there are, the
  later key is assumed to replace the value of the previous one.
* By default, comment lines start with ";" in the first column of the line.
  The contents of comment lines are ignored during comparison.
  However, you can change that character via the --comment command line
  option to another merry, printable, non-whitespace character.
* There is no single line that contains both data and a comment. That is,
  in lines like

      key = value ; comment here

  the programme will consider the value to be "value ; comment here" and
  NOT just "value".
* The order of sections and values within the sections is of no importance
  to the program. That means that the following two files would be
  considered to be equal:

      fileOne.ini      |     fileTwo.ini
                       |
      [SecOne]         |     [SecTwo]
      val = 1          |     x = unknown
      foo = bar        |     c = ++
      [SecTwo]         |     [SecOne]
      c = ++           |     foo = bar
      x = unknown      |     val = 1 

  If you try to compare ini files that do not meet these assumptions, then the
  result of the comparision might not be as expected. (Of course, you are
  always free to give it a try anyway.)

## Is there any kind of documentation for the program?

No, there is not (yet). That is, if you do not see this readme as such.

## Basic invocation

compare-ini expects two arguments: the (full or relative) paths to the ini
files you want to compare. An example would be:

    ./compare-ini /path/to/foo.ini bar.ini

This would compare the files /path/to/foo.ini and bar.ini with each other.

## Building the program from source

It is very easy to build the program, provided you have CMake on your build
machine. Just use:

    cmake /path/to/compare-ini-source
    make

... and CMake should take care of all the details.

For information how to build the program on Windows, see the
[MSYS2 build instructions](./documentation/msys2-build.md).

## Licensing

compare-ini is distributed under the the GNU General Public License,
version 3. See the accompanying LICENSE file for the full license text.
