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

#include "Ini.hpp"
#include "EntryNotFoundException.hpp"
#include <fstream>
#include <cstring>
#include <cctype>
#include "StringFunctions.hpp"

Ini::Ini()
: m_Sections(std::map<std::string, IniSection>()),
  m_CommentChar(';')
{
}

void Ini::addSection(const std::string& name, const IniSection& section)
{
  m_Sections[name] = section;
}

bool Ini::hasSection(const std::string& name) const
{
  return (m_Sections.find(name) != m_Sections.end());
}

const IniSection& Ini::getSection(const std::string& name) const
{
  const std::map<std::string, IniSection>::const_iterator iter =
          m_Sections.find(name);
  if (iter!=m_Sections.end())
    return iter->second;
  throw EntryNotFoundException(name);
}

std::vector<std::string> Ini::getSectionNames() const
{
  std::vector<std::string> result;
  std::map<std::string, IniSection>::const_iterator iter =
          m_Sections.begin();
  while (iter!=m_Sections.end())
  {
    result.push_back(iter->first);
    ++iter;
  } //while
  return result;
}

char Ini::getCommentCharacter() const
{
  return m_CommentChar;
}

bool Ini::setCommentCharacter(const char cc)
{
  if (cc!='[' && std::isgraph(cc))
  {
    m_CommentChar = cc;
    return true;
  }
  return false;
}

void Ini::clear()
{
  m_Sections.clear();
}

bool Ini::read(const std::string& fileName, unsigned int& lineCount, std::string& error)
{
  lineCount = 0;
  std::ifstream input;
  input.open(fileName.c_str(), std::ios::binary | std::ios::in);
  if (!input.good())
  {
    error = "Could not open file "+fileName+" for reading!";
    return false;
  }

  std::string currentSection = "";
  const unsigned int buff_size = 4096;
  char buffer[buff_size];
  memset(buffer, '\0', buff_size);
  while (input.getline(buffer, buff_size-1))
  {
    ++lineCount;
    std::string line(buffer);
    trim(line);
    if (!line.empty())
    {
      if (line[0]!= m_CommentChar)
      {
        //new section?
        if (line[0]=='[')
        {
          //try to remove brackets
          if (!removeEnclosingBrackets(line))
          {
            input.close();
            error = "No closing bracket in section line!";
            return false;
          }
          if (line.empty())
          {
            input.close();
            error = "Empty section name!";
            return false;
          }
          currentSection = line;
        } //if section
        //normal line / key-value pair
        else
        {
          std::string::size_type pos = line.find('=');
          if (pos == std::string::npos)
          {
            //failure
            input.close();
            error = "No equality sign in key-value line!";
            return false;
          }
          std::string key = line.substr(0, pos);
          trim(key);
          if (key.empty())
          {
            //no empty keys!
            input.close();
            error = "Empty key name!";
            return false;
          }
          std::string value = line.substr(pos);
          value.erase(0, 1); //remove '='
          trim(value);

          if (!hasSection(currentSection))
          {
              m_Sections[currentSection] = IniSection();
          }

          m_Sections[currentSection].addValue(key, value);
        } //else
      } //if not comment
    } //if not empty
  }//while
  const bool eof_reached = input.eof();
  input.close();
  error = "eof bit";
  return eof_reached;
}

bool Ini::hasSameContent(const Ini& other) const
{
  std::vector<std::string> otherNames = other.getSectionNames();
  if (otherNames.size()!=m_Sections.size())
    return false;
  std::map<std::string, IniSection>::const_iterator iter =
          m_Sections.begin();
  while (iter!=m_Sections.end())
  {
    if (!other.hasSection(iter->first))
      return false;
    if (!other.getSection(iter->first).hasSameValues(iter->second))
        return false;
    ++iter;
  } //while
  return true;
}

bool Ini::hasSameSectionNames(const Ini& other) const
{
  return (getSectionNames()==other.getSectionNames());
}
