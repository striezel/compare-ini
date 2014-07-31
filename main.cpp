/*
 -------------------------------------------------------------------------------
    This file is part of the compare-ini tool.
    Copyright (C) 2014  Thoronador

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

#include <iostream>
#include "Ini.hpp"

//return codes
const int rcInvalidParameter = 1;
const int rcFileError        = 2;

void showGPLNotice()
{
  std::cout << "compare-ini\n"
            << "  Copyright (C) 2014  Thoronador\n"
            << "\n"
            << "  This program is free software: you can redistribute it and/or modify\n"
            << "  it under the terms of the GNU General Public License as published by\n"
            << "  the Free Software Foundation, either version 3 of the License, or\n"
            << "  (at your option) any later version.\n"
            << "\n"
            << "  This program is distributed in the hope that it will be useful,\n"
            << "  but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
            << "  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
            << "  GNU General Public License for more details.\n"
            << "\n"
            << "  You should have received a copy of the GNU General Public License\n"
            << "  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
            << "\n";
}

void showHelp()
{
  std::cout << "compare-ini\n"
            << "\n"
            << "options:\n"
            << "  --help           - displays this help message and quits\n"
            << "  -?               - same as --help\n"
            << "  --version        - displays the version of the programme and quits\n"
            << "\n"
            << "NOTE: This programme is still under development and far from complete.\n";
}

void showVersion()
{
  std::cout << "compare-ini, version 0.01, 2014-07-31\n";
}

int main(int argc, char **argv)
{
  std::string first = "";
  std::string second = "";

  if (argc>1 and argv!=NULL)
  {
    int i=1;
    while (i<argc)
    {
      if (argv[i]!=NULL)
      {
        const std::string param = std::string(argv[i]);
        //help parameter
        if (param=="--help" or param=="-?")
        {
          showHelp();
          return 0;
        }//if help wanted
        //version information requested?
        else if ((param=="--version") or (param=="-v"))
        {
          showVersion();
          return 0;
        }
        else if (first.empty())
        {
          first = param;
        }
        else if (second.empty())
        {
          second = param;
        }
        else
        {
          //unknown or wrong parameter
          std::cout << "Invalid parameter given: \""<<param<<"\".\n"
                    << "Use --help to get a list of valid parameters.\n";
          return rcInvalidParameter;
        }
      }//parameter exists
      else
      {
        std::cout << "Parameter at index "<<i<<" is NULL.\n";
        return rcInvalidParameter;
      }
      ++i;//on to next parameter
    }//while
  }//if argc

  if (first.empty() || second.empty())
  {
    std::cout << "Not enough parameters given: you have to specify two ini files to compare!\n";
    return rcInvalidParameter;
  }

  showGPLNotice();

  //read first ini
  Ini ini_first;
  unsigned int lc = 0;
  std::string error_msg = "";
  bool success = ini_first.read(first, lc, error_msg);
  if (!success)
  {
    std::cout << "Failed to read ini from " << first << ".\nLine: "<<lc <<"; message: " << error_msg << "\n";
    return rcFileError;
  }

  //read second ini
  Ini ini_second;
  lc = 0;
  error_msg = "";
  success = ini_second.read(second, lc, error_msg);
  if (!success)
  {
    std::cout << "Failed to read ini from " << second << ".\nLine: "<<lc <<"; message: " << error_msg << "\n";
    return rcFileError;
  }

  if (ini_first.hasSameContent(ini_second))
    std::cout << "Both .ini files have the same content.\n";
  else if (ini_first.hasSameSectionNames(ini_second))
    std::cout << "Both .ini files have the same section names.\n";
  else
    std::cout << "Both .ini files seem to be rather different.\n";

  return 0;
}
