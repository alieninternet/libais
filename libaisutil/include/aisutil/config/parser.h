/* $Id$
 * 
 * Copyright (c) 1998,2002,2003 Alien Internet Services
 *
 * This file is a part of LibAISutil.
 * 
 * LibAISutil is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * LibAISutil is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LibAISutil; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _INCLUDE_LIBAISUTIL_CONFIG_PARSER_H_
# define _INCLUDE_LIBAISUTIL_CONFIG_PARSER_H_ 1

# include <vector>

// Forwarded declarations (completed after class)
namespace AISutil {
   class ConfigData;
};

# include <aisutil/string/string.h>

//! Configuration class/variable handler template macro thingies
# define LIBAISUTIL_CONFIG_CLASS_HANDLER(x) \
     bool x(AISutil::String& errString, \
	    const AISutil::String& defName, \
            const AISutil::ConfigParser::defValues_type& values, \
	    AISutil::ConfigData& dataClass, \
	    const void* dataVariable, \
	    AISutil::String& configData, \
	    AISutil::String::size_type& position)
# define LIBAISUTIL_CONFIG_VARIABLE_HANDLER(x) \
     bool x(AISutil::String& errString, \
	    const AISutil::String& defName, \
	    const AISutil::ConfigParser::defValues_type& values, \
	    AISutil::ConfigData& dataClass, \
	    const void* dataVariable)

namespace AISutil {
   //! Configuration file parsing routines
   class ConfigParser {
    public:
      //! This type is for sequences of values/parameters for variable defs
      typedef std::vector <String> defValues_type;
      
      //! Our handler types (used for both variables and classes)
      typedef LIBAISUTIL_CONFIG_CLASS_HANDLER((*classHandlerPtr_type));
      typedef LIBAISUTIL_CONFIG_VARIABLE_HANDLER((*variableHandlerPtr_type));
      
      //! Forward declaration of the typedef so we can use it in the structure
      struct def_type;
      
      //! Type definitions for the definition table stuff
      typedef const struct def_type (defTable_type)[];
      typedef const defTable_type* defTablePtr_type;
      
      /*! Definition table structure.
       * 
       * USAGE NOTE:
       * 
       * When defining a list of these structures (a definition table) you can
       * tune your table to be easier for people to use by specifying an
       * appropriate number of 'relevant characters' out of the name for
       * scanning. For example the definition name "NICKNAME" could be
       * written short-hand as "NICK" (4 relevant characters) as long as there
       * aren't any other names in the definition table starting with "NICK".
       * This can become a time-saver for users.
       * 
       * While using this structure a definition can be a class or a variable, 
       * or even both. Functionality is determined by which values are present 
       * as dictated below.
       * 
       * If defTable is present (!= NULL) when called as a class, the array 
       * which it points to will be used. If the classHandler is also present, 
       * it will be called prior to switching into that table. If the return
       * value of the handler is false the switch into that table will not be 
       * made.
       * 
       * If BOTH variableHandler are present (!= NULL) when called as a 
       * variable, the handler will be called to 'handle' the given variable
       * pointer. If the handler returns false, the parsing process will 
       * continue but with a warning given to the user. Note that if you are 
       * using a custom handler you will have to type-cast the void *.
       * 
       * When used within a table, the last entry must have a NULL for the name
       * variable, however the other variables in this structure can be used 
       * and will act like a 'default' entry, or 'if not found, use this' 
       * entry for classes which are just lists, or have sub-classes which 
       * variable names etc.
       */
      struct def_type {
	 const char* name;				//!< Name of definition
	 const unsigned int relevantChars;		//!< Relevant chars in name
	 const void* variablePtr;			//!< Data pointer
	 const variableHandlerPtr_type variableHandler;	//!< Handler (variable)
	 const defTablePtr_type defTable;		//!< Table (class)
	 const classHandlerPtr_type classHandler;	//!< Handler (class)
      };
      
    private:
      ConfigData &dataClass;				//!< Data members' class
      const defTablePtr_type topDefs;			//!< Top definition list
      const String filename;				//!< Main config filename
      
      static void complain(const String& segment,
			   const String line);		//!< Complain routine
      
      //! Load a file and return it as a single string of text (our munger)
      static const String read(const String& filename);
      
    public:
      //! Our constructor (this void really should be a defTablePtr_type?!?!!!!)
      ConfigParser(ConfigData& dc, const void* t, const String& f)
	: dataClass(dc),
          topDefs((const defTablePtr_type)t),
          filename(f)
	{};

      //! Destructor
      ~ConfigParser(void)
	{};
      
      //! Grab the configuration file name
      const String getConfigFile(void) const {
	 return filename;
      };
      
      //! Parse the given configuration data
      static bool parse(String &configData, String::size_type& position,
			const void* definitionTable, ConfigData& dataClass);
      
      //! Load the configuration file(s) and pass them to the parser
      bool configure(void) const;
   }; // class ConfigParser
}; // namespace LibAISutil
   
// Complete forwarded declarations
# include <aisutil/config/data.h>
   
#endif // _INCLUDE_LIBAISUTIL_CONFIG_PARSER_H_
