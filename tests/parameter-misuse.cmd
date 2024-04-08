:: Script to test executable when parameters are used in the wrong way.
::
::  Copyright (C) 2024  Dirk Stolle
::
::  This program is free software: you can redistribute it and/or modify
::  it under the terms of the GNU Lesser General Public License as published by
::  the Free Software Foundation, either version 3 of the License, or
::  (at your option) any later version.
::
::  This program is distributed in the hope that it will be useful,
::  but WITHOUT ANY WARRANTY; without even the implied warranty of
::  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
::  GNU Lesser General Public License for more details.
::
::  You should have received a copy of the GNU Lesser General Public License
::  along with this program.  If not, see <http://www.gnu.org/licenses/>.

@echo off

:: 1st parameter = executable path
if "%1" EQU "" (
  echo First parameter must be executable file!
  exit /B 1
)

SET EXECUTABLE=%1

:: parameter --comment / -c given twice
"%EXECUTABLE%" --comment X --comment Y foo.ini bar.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --comment was given twice.
  exit /B 1
)

:: parameter --comment conflicts with --comment-second
"%EXECUTABLE%" --comment-second X --comment Y foo.ini bar.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when conflicting comment data was given.
  exit /B 1
)

:: no comment character after parameter --comment
"%EXECUTABLE%" foo.ini bar.ini --comment
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --comment had no extra character.
  exit /B 1
)

:: comment "character" after parameter --comment is more than one character
"%EXECUTABLE%" --comment XYZ foo.ini bar.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --comment had more than one character.
  exit /B 1
)

:: invalid comment character after parameter --comment
"%EXECUTABLE%" --comment '[' foo.ini bar.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --comment had an invalid character.
  exit /B 1
)

:: parameter -c (short form) given twice
"%EXECUTABLE%" -cX -cY foo.ini bar.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when -c was given twice.
  exit /B 1
)

:: parameter -c (short form) conflicts with --comment-second
"%EXECUTABLE%" --comment-second X -cY foo.ini bar.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when conflicting comment data in short form was given.
  exit /B 1
)

:: parameter --comment--first / -c1 given twice
"%EXECUTABLE%" --comment-first X --comment-first Y foo.ini bar.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --comment-first was given twice.
  exit /B 1
)

:: no comment character after parameter --comment-first
"%EXECUTABLE%" foo.ini bar.ini --comment-first
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --comment-first had no extra character.
  exit /B 1
)

:: comment "character" after parameter --comment-first is more than one character
"%EXECUTABLE%" --comment-first XY foo.ini bar.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --comment-first had more than one character.
  exit /B 1
)

:: parameter --comment-second / -c2 given twice
"%EXECUTABLE%" --comment-second X --comment-second Y foo.ini bar.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --comment-second was given twice.
  exit /B 1
)

:: no comment character after parameter --comment-second
"%EXECUTABLE%" foo.ini bar.ini --comment-second
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --comment-second had no extra character.
  exit /B 1
)

:: comment "character" after parameter --comment-second is more than one character
"%EXECUTABLE%" --comment-second YY foo.ini bar.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when --comment-second had more than one character.
  exit /B 1
)

:: only one .ini file is specified
"%EXECUTABLE%" foo.ini
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when only one .ini file was given.
  exit /B 1
)

:: unknown parameter
"%EXECUTABLE%" foo.ini bar.ini --this-is-not-supported
if %ERRORLEVEL% NEQ 1 (
  echo Executable did not exit with code 1 when an unknown parameter was given.
  exit /B 1
)

exit 0
