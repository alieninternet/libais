/* $Id$
 *
 * Copyright (c) 2002,2003,2004 Alien Internet Services
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

#ifndef _INCLUDE_LIBAISUTIL_CONFIG_DEFINITIONS_H_
# define _INCLUDE_LIBAISUTIL_CONFIG_DEFINITIONS_H_ 1

# include <aisutil/config/var-handler.h>
# include <aisutil/config/seg-handler.h>

namespace AIS {
   namespace Util {
      namespace Config {
	 // Forward declaration of the Definition structure for typedefs
	 struct Definition;
	 
	 /*!
	  * \brief A table of definitions
	  * 
	  * This is a type definition for a table of configuration file
	  * definitions, used to provide a complete picture of which labels
	  * apply to what data within the data segment.
	  */
	 typedef Definition defTable_type[];
	 
	 //! A pointer to a table of definitions
	 typedef Definition* const defTable_ptr;

	 
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
	  * While using this structure a definition can be a segment or a variable, 
	  * or even both. Functionality is determined by which values are present 
	  * as dictated below.
	  * 
	  * If defTable is present (!= NULL) when called as a segment, the array 
	  * which it points to will be used. If the segmentHandler is also present, 
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
	  * entry for segments which are just lists, or have sub-segments which
	  * variable names etc.
	  */
	 struct Definition {
	    //! Name of definition
	    const char* const name;

	    //! Relevant chars in name
	    const unsigned int relevantChars;

	    
	    //! Data pointer
	    const void* variablePtr;

	    //! Handler (variable)
	    const VariableHandler* variableHandler;


	    //! Table (segment)
	    const defTable_ptr defTable;

	    //! Handler (segment)
	    const SegmentHandler* segmentHandler;
	 }; // struct Definition
      }; // namespace Config
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_CONFIG_DEFINITIONS_H_
