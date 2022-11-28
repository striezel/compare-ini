/*
 -------------------------------------------------------------------------------
    This file is part of the compare-ini tool.
    Copyright (C) 2014, 2022  Dirk Stolle

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

// return codes
const int rcInvalidParameter = 1;
const int rcFileError        = 2;

void showGPLNotice()
{
  std::cout << "compare-ini\n"
            << "  Copyright (C) 2014  Dirk Stolle\n"
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
            << "  --help    | -?     - Displays this help message and quits.\n"
            << "  --version | -v     - Displays the version of the program and quits.\n"
            << "  --license | -l     - Show license information.\n"
            << "  --comment C        - Set comment character to C.\n"
            << "  -c C | -cC         - short forms of --comment C\n"
            << "  --comment-left C   - Set comment character of first ini to C.\n"
            << "  --comment-first C  - Set comment character of first ini to C.\n"
            << "  --comment-right C  - Set comment character of second ini to C.\n"
            << "  --comment-second C - Set comment character of second ini to C.\n"
            << "  -c1 C | -cl C      - short forms of --comment-left C\n"
            << "  -c2 C | -cr C      - short forms of --comment-right C\n";
}

void showVersion()
{
  std::cout << "compare-ini, version 0.04, 2014-08-09\n";
}

std::string pad(const std::string& str, const std::string::size_type len)
{
  const std::string::size_type sl = str.size();
  if (len > sl)
    return str + std::string(len - sl, ' ');
  return str;
}

int main(int argc, char **argv)
{
  std::string first = "";
  std::string second = "";
  char commentCharacterFirst = '\0';
  char commentCharacterSecond = '\0';

  if ((argc > 1) && (argv != NULL))
  {
    int i = 1;
    while (i < argc)
    {
      if (argv[i] != NULL)
      {
        const std::string param = std::string(argv[i]);
        // help parameter
        if ((param == "--help") || (param == "-?"))
        {
          showHelp();
          return 0;
        }
        // version information requested?
        else if ((param == "--version") || (param == "-v"))
        {
          showVersion();
          return 0;
        }
        // show license
        else if ((param == "--licence") || (param == "--license") || (param == "-l"))
        {
          showGPLNotice();
          return 0;
        }
        // set comment character
        else if ((param == "--comment") || (param == "-c"))
        {
          if (commentCharacterFirst != '\0')
          {
            std::cout << "First/left comment character was already set to '"
                      << commentCharacterFirst << "'.\n";
            return rcInvalidParameter;
          }
          if (commentCharacterSecond != '\0')
          {
            std::cout << "Second/right comment character was already set to '"
                      << commentCharacterSecond << "'.\n";
            return rcInvalidParameter;
          }
          // enough arguments left?
          if ((i + 1 < argc) && (argv[i+1] != NULL))
          {
            const std::string cc = std::string(argv[i+1]);
            if (cc.size() != 1)
            {
              std::cout << "Error: Comment character parameter must be exactly one character!\n";
              return rcInvalidParameter;
            }
            commentCharacterFirst = cc[0];
            commentCharacterSecond = cc[0];
            // skip next parameter, because it's already used as comment character
            ++i;
          }
          else
          {
            std::cout << "Error: You have to specify a comment character after \""
                      << param << "\".\n";
            return rcInvalidParameter;
          }
        }
        else if ((param == "--comment-first") || (param == "--comment-left")
              || (param == "-c1") || (param == "-cl"))
        {
          if (commentCharacterFirst != '\0')
          {
            std::cout << "First/left comment character was already set to '"
                      << commentCharacterFirst << "'.\n";
            return rcInvalidParameter;
          }
          // enough arguments left?
          if ((i + 1 < argc) && (argv[i+1] != NULL))
          {
            const std::string cc = std::string(argv[i+1]);
            if (cc.size() != 1)
            {
              std::cout << "Error: Comment character parameter must be exactly one character!\n";
              return rcInvalidParameter;
            }
            commentCharacterFirst = cc[0];
            // skip next parameter, because it's already used as comment character
            ++i;
          }
          else
          {
            std::cout << "Error: You have to specify a comment character after \""
                      << param << "\".\n";
            return rcInvalidParameter;
          }
        }
        else if ((param == "--comment-second") || (param == "--comment-right")
              || (param == "-c2") || (param == "-cr"))
        {
          if (commentCharacterSecond != '\0')
          {
            std::cout << "Second/right comment character was already set to '"
                      << commentCharacterSecond << "'.\n";
            return rcInvalidParameter;
          }
          // enough arguments left?
          if ((i + 1 < argc) && (argv[i+1] != NULL))
          {
            const std::string cc = std::string(argv[i+1]);
            if (cc.size() != 1)
            {
              std::cout << "Error: comment character parameter must be exactly one character!\n";
              return rcInvalidParameter;
            }
            commentCharacterSecond = cc[0];
            // skip next parameter, because it's already used as comment character
            ++i;
          }
          else
          {
            std::cout << "Error: You have to specify a comment character after \""
                      << param << "\".\n";
            return rcInvalidParameter;
          }
        }
        // shorter way to set comment character
        else if ((param.size() == 3) && (param.find("-c") == 0))
        {
          if (commentCharacterFirst != '\0')
          {
            std::cout << "First/left comment character was already set to '"
                      << commentCharacterFirst << "'.\n";
            return rcInvalidParameter;
          }
          if (commentCharacterSecond != '\0')
          {
            std::cout << "Second/right comment character was already set to '"
                      << commentCharacterSecond << "'.\n";
            return rcInvalidParameter;
          }
          commentCharacterFirst = param[2];
          commentCharacterSecond = param[2];
        }
        else if ((param.size() == 4) && ((param.find("-c1") == 0) || (param.find("-cl") == 0)))
        {
          if (commentCharacterFirst!='\0')
          {
            std::cout << "First/left comment character was already set to '"
                      << commentCharacterFirst << "'.\n";
            return rcInvalidParameter;
          }
          commentCharacterFirst = param[3];
        }
        else if ((param.size() == 4) && ((param.find("-c2") == 0) || (param.find("-cr") == 0)))
        {
          if (commentCharacterSecond != '\0')
          {
            std::cout << "Second/right comment character was already set to '"
                      << commentCharacterSecond << "'.\n";
            return rcInvalidParameter;
          }
          commentCharacterSecond = param[3];
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
          // unknown or wrong parameter
          std::cout << "Invalid parameter given: \"" << param << "\".\n"
                    << "Use --help to get a list of valid parameters.\n";
          return rcInvalidParameter;
        }
      }
      else
      {
        std::cout << "Parameter at index " << i << " is NULL.\n";
        return rcInvalidParameter;
      }
      ++i; // on to next parameter
    } // while
  } // if argc

  if (first.empty() || second.empty())
  {
    std::cout << "Not enough parameters given: You have to specify two ini files to compare!\n";
    return rcInvalidParameter;
  }

  // check comment character
  if (commentCharacterFirst == '\0')
  {
    // was not set, set it to default
    commentCharacterFirst = ';';
  }
  if (commentCharacterSecond == '\0')
  {
    // was not set, set it to default
    commentCharacterSecond = ';';
  }

  // read first ini
  Ini ini_first;
  if (!ini_first.setCommentCharacter(commentCharacterFirst))
  {
    std::cout << "Error: Invalid comment character specified!\n";
    return rcInvalidParameter;
  }
  unsigned int lc = 0;
  std::string error_msg = "";
  if (!ini_first.read(first, lc, error_msg))
  {
    std::cout << "Failed to read ini from " << first << ".\nLine: " << lc
              << "; message: " << error_msg << "\n";
    return rcFileError;
  }

  // read second ini
  Ini ini_second;
  if (!ini_second.setCommentCharacter(commentCharacterSecond))
  {
    std::cout << "Error: Invalid comment character specified!\n";
    return rcInvalidParameter;
  }
  lc = 0;
  error_msg = "";
  if (!ini_second.read(second, lc, error_msg))
  {
    std::cout << "Failed to read ini from " << second << ".\nLine: " << lc
              << "; message: " << error_msg << "\n";
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
    while (cLeftIter != out_left.end())
    {
      const std::string::size_type l = cLeftIter->size();
      if (l > maxLeftLength)
        maxLeftLength = l;
      ++cLeftIter;
    }

    // output
    std::cout << std::endl;
    cLeftIter = out_left.begin();
    std::vector<std::string>::const_iterator cRightIter = out_right.begin();
    while (cLeftIter != out_left.end())
    {
      std::cout << pad(*cLeftIter, maxLeftLength) << " | " << *cRightIter << std::endl;
      ++cLeftIter;
      ++cRightIter;
    }
  } // if different / comparison needed

  return 0;
}
