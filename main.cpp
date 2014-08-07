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
#include "Compare.hpp"

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
  std::cout << "compare-ini [options] /path/to/first.ini /path/to/second.ini\n"
            << "\n"
            << "options:\n"
            << "  --help    | -?   - displays this help message and quits\n"
            << "  --version | -v   - displays the version of the programme and quits\n"
            << "  --license | -l   - show license information.\n"
            << "  --comment C      - set comment character to C\n"
            << "  -c C | -cC       - short forms of --comment C\n";
}

void showVersion()
{
  std::cout << "compare-ini, version 0.03, 2014-08-08\n";
}

std::string pad(const std::string& str, const std::string::size_type len)
{
  const std::string::size_type sl = str.size();
  if (len>sl)
    return str + std::string(len-sl, ' ');
  return str;
}

int main(int argc, char **argv)
{
  std::string first = "";
  std::string second = "";
  char commentCharacter = '\0';

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
        //show license
        else if ((param=="--licence") or (param=="--license") or (param=="-l"))
        {
          showGPLNotice();
          return 0;
        }
        //set comment character
        else if ((param=="--comment") or (param=="-c"))
        {
          if (commentCharacter!='\0')
          {
            std::cout << "Comment character was already set to '" << commentCharacter << "'.\n";
            return rcInvalidParameter;
          }
          //enough arguments left?
          if ((i+1 < argc) and (argv[i+1]!=NULL))
          {
            const std::string cc = std::string(argv[i+1]);
            if (cc.size()!=1)
            {
              std::cout << "Error: comment character parameter must be exactly one character!\n";
              return rcInvalidParameter;
            }
            commentCharacter = cc[0];
            //skip next parameter, because it's already used as comment character
            ++i;
          }
          else
          {
            std::cout << "Error: You have to specify a comment character after \""
                      << param<<"\".\n";
            return rcInvalidParameter;
          }
        }
        //shorter way to set comment character
        else if ((param.size()==3) and (param.find("-c") == 0))
        {
          if (commentCharacter!='\0')
          {
            std::cout << "Comment character was already set to '" << commentCharacter << "'.\n";
            return rcInvalidParameter;
          }
          commentCharacter = param[2];
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

  //check comment character
  if (commentCharacter=='\0')
  {
    //was not set, set it to default
    commentCharacter = ';';
  }

  //read first ini
  Ini ini_first;
  if (!ini_first.setCommentCharacter(commentCharacter))
  {
    std::cout << "Error: invalid comment character specified!\n";
    return rcInvalidParameter;
  }
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
  if (!ini_second.setCommentCharacter(commentCharacter))
  {
    std::cout << "Error: invalid comment character specified!\n";
    return rcInvalidParameter;
  }
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
  {
    std::vector<std::string> out_left;
    std::vector<std::string> out_right;
    compare(ini_first, ini_second, out_left, out_right);
    out_left.insert(out_left.begin(), first);
    out_right.insert(out_right.begin(), second);

    std::string::size_type maxLeftLength = 0;
    std::vector<std::string>::const_iterator cLeftIter = out_left.begin();
    while (cLeftIter!=out_left.end())
    {
      const std::string::size_type l = cLeftIter->size();
      if (l > maxLeftLength)
        maxLeftLength = l;
      ++cLeftIter;
    } //while

    //output
    std::cout << std::endl;
    cLeftIter = out_left.begin();
    std::vector<std::string>::const_iterator cRightIter = out_right.begin();
    while (cLeftIter != out_left.end())
    {
      std::cout << pad(*cLeftIter, maxLeftLength) << " | " << *cRightIter << std::endl;
      ++cLeftIter;
      ++cRightIter;
    }//while
  } //if different / comparison needed

  return 0;
}
