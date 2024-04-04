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

#ifndef INISECTION_HPP
#define INISECTION_HPP

#include <string>
#include <map>
#include <vector>

class IniSection
{
  public:
    IniSection();


    /** \brief Add a new entry to the section or replace an existing entry.
     *
     * \param name the name of the entry
     * \param value the value of the entry
     */
    void addEntry(const std::string& name, const std::string& value);


    /** \brief Checks if a entry / key exists in the current section.
     *
     * \param name  the name of the entry
     * \return Returns true, if the entry exists; returns false otherwise.
     */
    bool hasEntry(const std::string& name) const;


    /** \brief Retrieves value of an entry.
     *
     * \param name the name of the entry
     * \return Returns the entry's value, if an entry with the given name is present.
     * \remarks If the requested entry is not present, then the function will
     *          throw an exception.
     */
    const std::string& getValue(const std::string& name) const;


    /** \brief Returns a vector containing the names of all entries in the section.
     *
     * \return vector of std::strings containing the entry names
     */
    std::vector<std::string> getEntryNames() const;


    /** \brief Deletes all entries from the current section.
     */
    void clear();


    /** \brief Determines whether this section and another section have the same
     *         key-value pairs.
     * \param other the other section
     * \return Returns true, if key-value pairs are equal. Returns false otherwise.
     */
    bool operator==(const IniSection& other) const;

    /// inequality operator
    bool operator!=(const IniSection& other) const;


    /** \brief Determines whether this section and another section have the same key names.
     *
     * \param other the other section
     * \return Returns true, if key names are equal. Returns false otherwise.
     */
    bool hasSameKeys(const IniSection& other) const;
  private:
    std::map<std::string, std::string> m_Values;
}; // class

#endif // INISECTION_HPP
