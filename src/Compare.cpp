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

#include "Compare.hpp"
#include <set>

void addEmptyLines(std::vector<std::string>& out, const unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out.push_back("");
}

void addSection(std::vector<std::string>& out, const IniSection& sect, const std::string& sectName)
{
  out.push_back("[" + sectName + "]");
  const auto res = sect.getEntryNames();
  for (const auto& item: res)
  {
    out.push_back(item + " = " + sect.getValue(item));
  }
}

void compare(const Ini& left, const Ini& right, std::vector<std::string>& out_left, std::vector<std::string>& out_right)
{
  std::set<std::string> sections;
  auto res = left.getSectionNames();
  for (const auto& section: res)
  {
    sections.insert(section);
  }

  res = right.getSectionNames();
  for (const auto& section: res)
  {
    sections.insert(section);
  }

  out_left.clear();
  out_right.clear();

  // walk through all sections
  for (const auto& section: sections)
  {
    if (left.hasSection(section) && right.hasSection(section))
    {
      if (left.getSection(section) != right.getSection(section))
      {
        out_left.push_back(std::string("[") + section + "]");
        out_right.push_back(std::string("[") + section + "]");

        const IniSection& leftSec = left.getSection(section);
        const IniSection& rightSec = right.getSection(section);

        std::set<std::string> entries;
        res = leftSec.getEntryNames();
        for (const auto& entry_name: res)
        {
          entries.insert(entry_name);
        }

        res = rightSec.getEntryNames();
        for (const auto& entry_name: res)
        {
          entries.insert(entry_name);
        }

        for (const auto& entry_name: entries)
        {
          // entry is present in both
          if (leftSec.hasEntry(entry_name) && rightSec.hasEntry(entry_name))
          {
            const std::string& leftVal = leftSec.getValue(entry_name);
            const std::string& rightVal = rightSec.getValue(entry_name);
            if (leftVal != rightVal)
            {
              out_left.push_back(entry_name + " = " + leftVal);
              out_right.push_back(entry_name + " = " + rightVal);
            }
          }
          // entry is (only) present in left section
          else if (leftSec.hasEntry(entry_name))
          {
            out_left.push_back(entry_name + " = " + leftSec.getValue(entry_name));
            out_right.push_back("");
          }
          else
          {
             // only present in right section
             out_left.push_back("");
             out_right.push_back(entry_name + " = " + rightSec.getValue(entry_name));
          }
        }
      } // if sections not equal
    } // if section present in both
    else if (left.hasSection(section))
    {
      const IniSection& leftSec = left.getSection(section);
      addSection(out_left, leftSec, section);
      addEmptyLines(out_right, leftSec.getEntryNames().size() + 1);
    } // if section is only present in left ini
    else if (right.hasSection(section))
    {
      const IniSection& rightSec = right.getSection(section);
      addSection(out_right, rightSec, section);
      addEmptyLines(out_left, rightSec.getEntryNames().size() + 1);
    } // if section is only present in left ini
  }
}
