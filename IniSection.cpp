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

#include "IniSection.hpp"
#include "EntryNotFoundException.hpp"

IniSection::IniSection()
: m_Values(std::map<std::string, std::string>())
{
}

void IniSection::addValue(const std::string& name, const std::string& value)
{
  m_Values[name] = value;
}

bool IniSection::hasValue(const std::string& name) const
{
  return m_Values.find(name) != m_Values.end();
}

const std::string& IniSection::getValue(const std::string& name) const
{
  const auto iter = m_Values.find(name);
  if (iter != m_Values.end())
    return iter->second;
  throw EntryNotFoundException(name);
}

std::vector<std::string> IniSection::getValueNames() const
{
  std::vector<std::string> result;
  for (const auto& value: m_Values)
  {
    result.push_back(value.first);
  }
  return result;
}

void IniSection::clear()
{
  m_Values.clear();
}

bool IniSection::hasSameValues(const IniSection& other) const
{
  std::vector<std::string> otherNames = other.getValueNames();
  if (otherNames.size() != m_Values.size())
    return false;
  for (const auto& value: m_Values)
  {
    if (!other.hasValue(value.first))
      return false;
    if (other.getValue(value.first) != value.second)
        return false;
  }
  return true;
}

bool IniSection::hasSameKeys(const IniSection& other) const
{
  return getValueNames() == other.getValueNames();
}
