/*
 -------------------------------------------------------------------------------
    This file is part of the compare-ini tool.
    Copyright (C) 2014, 2022, 2024  Dirk Stolle

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
  return m_Sections.find(name) != m_Sections.end();
}

const IniSection& Ini::getSection(const std::string& name) const
{
  const auto iter = m_Sections.find(name);
  if (iter != m_Sections.end())
    return iter->second;
  throw EntryNotFoundException(name);
}

std::vector<std::string> Ini::getSectionNames() const
{
  std::vector<std::string> result;
  for (const auto& section: m_Sections)
  {
    result.push_back(section.first);
  }
  return result;
}

char Ini::getCommentCharacter() const
{
  return m_CommentChar;
}

bool Ini::setCommentCharacter(const char cc)
{
  if (cc != '[' && std::isgraph(static_cast<unsigned char>(cc)))
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

bool Ini::read(const std::filesystem::path& path, unsigned int& lineCount, std::string& error)
{
  lineCount = 0;
  std::ifstream input;
  input.open(path, std::ios::binary | std::ios::in);
  if (!input.good())
  {
    error = "Could not open file " + path.string() + " for reading!";
    return false;
  }

  return read(input, lineCount, error);
}

bool Ini::read(std::istream& stream, unsigned int& lineCount, std::string& error)
{
  lineCount = 0;
  std::string currentSection = "";
  const unsigned int buff_size = 4096;
  char buffer[buff_size];
  memset(buffer, '\0', buff_size);
  while (stream.getline(buffer, buff_size - 1))
  {
    ++lineCount;
    std::string line(buffer);
    trim(line);
    if (line.empty())
      continue;
    if (line[0] == m_CommentChar)
      continue;

    // new section?
    if (line[0] == '[')
    {
      // try to remove brackets
      if (!removeEnclosingBrackets(line))
      {
        error = "No closing bracket in section line!";
        return false;
      }
      if (line.empty())
      {
        error = "Empty section name!";
        return false;
      }
      currentSection = line;
      if (!hasSection(currentSection))
      {
          m_Sections[currentSection] = IniSection();
      }
    }
    // normal line / key-value pair
    else
    {
      std::string::size_type pos = line.find('=');
      if (pos == std::string::npos)
      {
        // failure
        error = "No equality sign in key-value line!";
        return false;
      }
      std::string key = line.substr(0, pos);
      trim(key);
      if (key.empty())
      {
        // no empty keys!
        error = "Empty key name!";
        return false;
      }
      std::string value = line.substr(pos);
      value.erase(0, 1); // remove '='
      trim(value);

      if (!hasSection(currentSection))
      {
          m_Sections[currentSection] = IniSection();
      }

      m_Sections[currentSection].addEntry(key, value);
    }
  }
  const bool eof_reached = stream.eof();
  error = "eof bit";
  return eof_reached;
}

bool Ini::operator==(const Ini& other) const
{
  return m_Sections == other.m_Sections;
}

bool Ini::hasSameSectionNames(const Ini& other) const
{
  return getSectionNames() == other.getSectionNames();
}
