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

#include "Compare.hpp"
#include <set>

void addEmptyLines(std::vector<std::string>& out, const unsigned int n)
{
  unsigned int i;
  for (i=0; i<n; ++i)
    out.push_back("");
}

void addSection(std::vector<std::string>& out, const IniSection& sect, const std::string& sectName)
{
  out.push_back("["+sectName+"]");
  const std::vector<std::string> res = sect.getValueNames();
  std::vector<std::string>::const_iterator iter = res.begin();
  while (iter!=res.end())
  {
    out.push_back(*iter + " = " + sect.getValue(*iter));
    ++iter;
  } //while
}

void compare(const Ini& left, const Ini& right, std::vector<std::string>& out_left, std::vector<std::string>& out_right)
{
  std::set<std::string> sections;
  std::vector<std::string> res = left.getSectionNames();
  std::vector<std::string>::const_iterator iter = res.begin();
  while (iter!=res.end())
  {
    sections.insert(*iter);
    ++iter;
  } //while

  res = right.getSectionNames();
  iter = res.begin();
  while (iter!=res.end())
  {
    sections.insert(*iter);
    ++iter;
  } //while

  out_left.clear();
  out_right.clear();

  //walk through all sections
  std::set<std::string>::const_iterator secIter = sections.begin();
  while (secIter!=sections.end())
  {
    if (left.hasSection(*secIter) && right.hasSection(*secIter))
    {
      if (!left.getSection(*secIter).hasSameValues(right.getSection(*secIter)))
      {
        out_left.push_back(std::string("[")+*secIter+"]");
        out_right.push_back(std::string("[")+*secIter+"]");

        const IniSection& leftSec = left.getSection(*secIter);
        const IniSection& rightSec = right.getSection(*secIter);

        std::set<std::string> values;
        std::vector<std::string> res = leftSec.getValueNames();
        iter = res.begin();
        while (iter!=res.end())
        {
          values.insert(*iter);
          ++iter;
        } //while

        res = rightSec.getValueNames();
        iter = res.begin();
        while (iter!=res.end())
        {
          values.insert(*iter);
          ++iter;
        } //while

        std::set<std::string>::const_iterator valIter = values.begin();
        while (valIter!=values.end())
        {
          if (leftSec.hasValue(*valIter) && rightSec.hasValue(*valIter))
          {
            const std::string& leftVal = leftSec.getValue(*valIter);
            const std::string& rightVal = rightSec.getValue(*valIter);
            if (leftVal != rightVal)
            {
              out_left.push_back(*valIter + " = " + leftVal);
              out_right.push_back(*valIter + " = " + rightVal);
            }
          } //if value present in both
          else if (leftSec.hasValue(*valIter))
          {
            out_left.push_back(*valIter + " = " + leftSec.getValue(*valIter));
            out_right.push_back("");
          } //else if value is (only) present in left section
          else
          {
             //only present in right section
             out_left.push_back("");
             out_right.push_back(*valIter + " = " + rightSec.getValue(*valIter));
          } //else
          ++valIter;
        } //while more values


      } //if sections not equal
    } //if section present in both
    else if (left.hasSection(*secIter))
    {
      const IniSection& leftSec = left.getSection(*secIter);
      addSection(out_left, leftSec, *secIter);
      addEmptyLines(out_right, leftSec.getValueNames().size()+1);
    } //if section is only present in left ini
    else if (right.hasSection(*secIter))
    {
      const IniSection& rightSec = right.getSection(*secIter);
      addSection(out_right, rightSec, *secIter);
      addEmptyLines(out_left, rightSec.getValueNames().size()+1);
    } //if section is only present in left ini
    ++secIter;
  } //while
}
