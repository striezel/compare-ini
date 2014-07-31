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

#ifndef INI_HPP_INCLUDED
#define INI_HPP_INCLUDED

#include <string>
#include <map>
#include <vector>
#include "IniSection.hpp"

class Ini
{
  public:
    ///constructor
    Ini();


    /** \brief adds a new section to the ini or replaces an existing section of the same name
     *
     * \param name the name of the section
     * \param value the section
     */
    void addSection(const std::string& name, const IniSection& section);


    /** \brief check if a section exists within the ini
     *
     * \param name the name of the section
     * \return Returns true, if the section exists; returns false otherwise.
     */
    bool hasSection(const std::string& name) const;


    /** \brief retrieve a section
     *
     * \param name the name of the requested section
     * \return Returns the section, if a section with the given name is present.
     * \remarks If the requested section is not present, then the function will
     *          throw an exception.
     */
    const IniSection& getSection(const std::string& name) const;


    /** \brief returns a vector containing the names of all sections in the ini
     *
     * \return vector of std::strings containing the section names
     */
    std::vector<std::string> getSectionNames() const;

    char getCommentCharacter() const;
    void setCommentCharacter(const char cc);


    /** \brief removes all sections from the ini
     */
    void clear();


    /** \brief tries to read all ini data from a given file
     *
     * \param fileName path to the ini file
     * \param lineCount var that tracks the current line number in case of errors
     * \param error var that holds the error message in case of errors
     * \return Returns true, if the read was successful. Returns false otherwise.
     */
    bool read(const std::string& fileName, unsigned int& lineCount, std::string& error);


    /** \brief determines whether this ini and another section have the same
     *         sections with the same key-value pairs
     * \param other the other ini
     * \return Returns true, if both ini contents are equal. Returns false otherwise.
     */
    bool hasSameContent(const Ini& other) const;


    /** \brief determines whether this ini and another ini have the same section names
     *
     * \param other the other ini
     * \return Returns true, if Section names are equal. Returns false otherwise.
     */
    bool hasSameSectionNames(const Ini& other) const;
  private:
    std::map<std::string, IniSection> m_Sections;
    char m_CommentChar;
}; //class

#endif // INI_HPP_INCLUDED
