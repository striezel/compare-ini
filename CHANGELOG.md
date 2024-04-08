# Version history of compare-ini

_(Note: Smaller fixes or improvements may be omitted.)_

## Version 0.6.0 (2024-04-08)

Error messages are now shown on standard error stream instead of the standard
output stream.

The program will now handle files with Windows-style line endings (carriage
return and line feed) properly.

## Version 0.5.0 (2022-11-28)

The minimum required CMake version for compiling the project is raised from 2.8
to 3.8.

The C++ standard used during compilation has been raised from de-facto still
using C++98 or whatever the compiler uses as default standard to C++17.
Recent compilers should support that by now.

## Version 0.04 (2014-08-09)

Allow to set comment character on a per-file basis, i. e. both files can have
different comment characters from now on.

## Version 0.03 (2014-08-08)

The comment character for the .ini files can now be changed, i. e. the program
does not assume it to be `;` when the user sets a different value.

## Version 0.02 (2014-08-01)

A side-by-side comparison containing the differences of both files is now shown.

## Version 0.01 (2014-07-31)

Initial version of the program. It only determines whether both .ini files are
equal.
