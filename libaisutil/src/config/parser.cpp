/* $Id$
 * Configuration data parsing functions
 * 
 * Copyright (c) 2002 Alien Internet Services
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <fstream>
#include <sstream>
#include <cctype>
#include <cstring>

#ifdef LIBAISUTIL_DEBUG_ASSERT
# include <cassert>
#endif

#include "aisutil/config/data.h"
#include "aisutil/config/parser.h"

using namespace AISutil;


/* This is our 'magic marker char' used to, heh, 'encode' a string of text
 * within the munger function to help mark which file and line stuff is
 * located on so that the parser can look smart - all without either adding
 * an index to the data, or without over-complicating the parser to run
 * through a two-dimentional array as opposed to a one-dimentional array. It
 * also means if anyone wanted to they could pass information from the
 * loader/munger function to the parser function fairly easily.
 *
 * We use a new-line character here in the loader/munger turns a whole file
 * into one line (no new-lines) anyway, so this should be the safest possible
 * character to use at all :)
 */
#define MAGIC_MARKER_CHAR	'\n'


/* complain - Complain about something to the appropriate place
 * Original 13/03/2002 simonb
 */
inline void ConfigParser::complain(const String &segment, const String line)
{
   // This is temporary...
   std::cout << segment << " -> " << line << std::endl;
}


/* read - Load a file and return it as a single string of text (our munger)
 * Original 17/03/2002 simonb
 */
const String ConfigParser::read(const String &filename)
{
   // Open the file
   std::ifstream file(filename.c_str(), std::ios::in);

   // Check that we opened the file ok
   if (!file) {
      complain(filename, "Could not open configuration file");
      return "";
   }

   String configData, line, temp;

   // Stuff we need along the way...
   bool inComment = false, inQuote = false;
   char quoteChar = 0;
   unsigned long lineNum = 0;

#ifdef LIBAISUTIL_DEBUG_ASSERT
   /* The isspace() MUST return true for this or our magic char method
    * will break. See the comment above the define for MAGIC_MARKER_CHAR
    * at the top of this file. If this breaks on your system for some reason
    * then it must be really broken somehow :(
    */
   assert(isspace(MAGIC_MARKER_CHAR));
#endif

   /* Read the entire file into our configuration data buffer, cropping away
    * redundant data such as white-space, new lines, comments etc.
    */
   for (;;) {
      // Clear the temporary variable
      temp.clear();

      // Grab a line from the file
      std::getline(file, line);

      // Make sure the file is still happy..
      if (!file.good() || file.eof()) {
	 break;
      }

      // Increase the line counter
      lineNum++;

      // Trim away leading/trailing whitespace
      line = line.trim();

      // Skip an empty line..
      if (line.empty()) {
	 continue;
      }

      /* Run through the line and MUNG it down into something easier for us
       * to chew on later :)
       * Yes.. I know, bad pun, sorry. :( *hides from the pun police*
       */
      for (String::size_type i = 0; i < line.length(); i++) {
	 /* Is this an escape char ('\') or not? If so, we copy this and
	  * the next char literally unless the next three chars are numbers...
	  * If they are numbers, we process them into a real character, as
	  * long as they are not bad characters. The number must be in octal.
	  * If this char is found at the end of a line, it will be ignored --
	  * But who cares anyway, this parser's scope is the whole file and
	  * not a single line like a shell script :)
	  * 
	  * Why do we copy the escape char and the next char if we are not
	  * processing the escape literally?? Because the secondary parser will
	  * need to know if it is an escape for stuff like quotes... Seems
	  * rather messy, but it's the simplest (!!) method I came up with at
	  * the time. :( The best thing to do would be to integrate the two
	  * parsers neatly, but I really can't be bothered since it's only
	  * the configuration parser!
	  */
	 if ((line[i] == '\\') && (line.length() > i)) {
	    // Check if the next three characters are digits, the messy way..
	    if ((line.length() > (i + 3)) &&
		isdigit(line[i + 1]) &&
		isdigit(line[i + 2]) &&
		isdigit(line[i + 3])) {
	       // Convert the three digits from octal to a long
	       long value = strtol(line.substr(++i, 3).c_str(), NULL, 8);

	       // Jump over the last two chars..
	       i += 2;
	       
	       /* Check the character is OK..
		* Here we make sure it is within a character range (0..255),
		* it is not \0 (null), it is not \n or \r, or \b (backspace).
		* It is also checked to NOT be a data-control char (DC1-DC4)
		* to avoid any issues with terminal flow control..
		*/
	       if ((value > 0) && (value < 256) && 
		   (value != '\n') && (value != '\r') && (value != '\b') &&
		   ((value < 17) || (value > 20))) {
		  // OK! Add the char to the string
		  temp += char(value);
	       }
	    } else {
	       /* Copy the two chars (the escape char and the char being 
		* escaped) over...
		*/
	       temp += line[i++];
	       temp += line[i];
	    }
	    
	    continue;
	 }

	 // If we are in a quote, we have to copy this string over literally
	 if (inQuote) {
	    temp += line[i];

	    // Check if we are leaving a quote (and this char is not escaped)
	    if (line[i] == quoteChar) {
	       inQuote = false;
	    }

	    continue;
	 }

	 /* If we are in a comment, we need to ignore everything until the
	  * end of the comment.. So all we do here is check if we are done.
	  * Note, that C++/UNIX style comments run until the end of the
	  * line, so they end up aborting to the next line anyway, so all
	  # we are checking for here are C style comments. We do not check for
	  * nested comments, but the configuration file isn't a high-level
	  * programming language so SHUSH! :)
	  */
	 if (inComment) {
	    // Maybe this is the end of it?
	    if ((line[i] == '*') &&
		(line.length() > (i + 1)) &&
		(line[i + 1] == '/')) {
	       i++;
	       inComment = false;
	    }

	    continue;
	 }

	 /* This is a code 'neating' thingy. We check if the current
	  * char is considered whitespace, then skip it if the next
	  * char is also whitespace, or we are before/after an '='
	  * (sometimes used for definition statements), or before a class'
	  * opening parenthesis
	  */
	 if ((line.length() > i) &&
	     (isspace(line[i]) &&
	      (isspace(line[i + 1]) ||
	       (line[i + 1] == '=') ||
	       (line[i - 1] == '=') ||
	       (line[i + 1] == '{')))) {
	    continue;
	 }

	 // Examine the rest of the code carefully
	 switch (line[i]) {
	  case '/': // Comment perhaps?
	    // C or C++ style?
	    if (line[i + 1] == '*') {
	       // C style, continue on..
	       inComment = true;
	    } else if (line[i + 1] == '/') {
	       // C++ style, we gotta break out of this one at the EOL
	       i = line.length();
	    } else {
	       // Oh well, pass it through normally...
	       temp += line[i];
	    }
	    continue;

	  case '#': // A unix style comment?
	    // Just like the C++ style comment we must stop at the EOL mark
	    i = line.length();
	    continue;

	  case '=': // Translate '=' to a space for easier parsing
	    temp += ' ';
	    continue;

	  case '\'':
	  case '"':
	  case '`': // Beginning of a quote... (note - no break)
	    quoteChar = line[i];
	    inQuote = true;

	  default:
	    // Translate whitespace to a proper space or just copy?
	    if (isspace(line[i])) {
	       temp += ' ';
	    } else {
	       temp += line[i];
	    }
	 }
      }

      // Make sure our munged output is not blank
      if (!temp.empty()) {
	 // Add our segment information to the string
	 std::stringstream segmentInfo;
	 segmentInfo << MAGIC_MARKER_CHAR << filename << ':' << lineNum <<
	   MAGIC_MARKER_CHAR;
	 configData += segmentInfo.str();

	 // Add the line itself
	 configData += temp;
      }
   }

   // Check if comments were terminated properly
   if (inComment) {
      complain(filename, "Unterminated comment found");
      return "";
   }

   // Check if quotes were terminated properly
   if (inQuote) {
      complain(filename, "Unterminated quote found");
      return "";
   }

   // Close down the configuration file.
   file.close();

   return configData;
}


/* parse - Parse the given configuration data
 * Original 13/03/2002 simonb
 */
bool ConfigParser::parse(String &configData, String::size_type &position,
			 const void *definitionTable, ConfigData &dataClass)
{
   // Check the data
   if (configData.empty()) {
      // Nothing to parse, nothing to cause an error!
      return true;
   }
   
   // Stuff we need while running through the line
   char quoteChar = '\0';
   unsigned int i, classSkipDepth = 0;
   String segment = "START", definition, value, errString;
   bool readDef = false, gotDef = false;
   defValues_type values;
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(values.empty());
#endif

   // Our current class's definition table (as given to us)
   defTablePtr_type currentDefs = (defTablePtr_type)definitionTable;
#ifdef LIBAISUTIL_DEBUG_ASSERT
   assert(currentDefs != 0);
#endif

   // Run through the generated line...
   for (; position != configData.length(); position++) {
      switch (configData[position]) {
       case MAGIC_MARKER_CHAR: // Magic character for segment information
	   {
	      String::size_type len =
		configData.substr(++position).find(MAGIC_MARKER_CHAR);
#ifdef LIBAISUTIL_DEBUG_ASSERT
	      assert(len > 0);
#endif
	      segment = configData.substr(position, len);
	      position += len;
	      continue;
	   }

       case '\\': // Escape char (well, start of an escape anyway)
	 // Make sure there is another char after this..
	 if (configData.length() > position) {
	    // Jump to the character being escaped so it can be copied
	    position++;
	 } else {
	    complain(segment,
		     "Cannot complete escape beyond end of configuration");
	 }
	 break;

       case '\'':
       case '"':
       case '`': // Entry or exit of a quote..
	 if (quoteChar == '\0') {
	    quoteChar = configData[position];
	    continue;
	 } else if (configData[position] == quoteChar) {
	    quoteChar = '\0';
	    continue;
	 }
	 break;

       case ' ': // Separator between something special..
	 // Is this a separator between a definition and value(s)?
	 if (readDef) {
	    // Make sure the value is not empty..
	    if (!value.empty()) {
	       // Add the value to the list and clear the value string
	       values.push_back(value);
	       value.clear();
	    }
	 } else {
	    readDef = true;
	 }
	 continue;

       case '{': // Note - no break intentionally
	 // Are we skipping a class, or is this class without a name?
	 if (classSkipDepth) {
	    classSkipDepth++;
	    continue;
	 } else if (definition.empty()) {
	    complain(segment, "Skipping nameless class");
	    readDef = false;
	    classSkipDepth++;
	    continue;
	 }

       case ';': // Ah huh! End of a definition...
	   {
	      // Make sure the definition string actually contains something
	      if (definition.empty()) {
		 readDef = false;
		 continue;
	      }

	      /* If there is something left in the value string add it to the
	       * values queue
	       */
	      if (!value.empty()) {
		 values.push_back(value);
		 value.clear();
	      }

	      // Fix the definition up for our check
	      String fixedDefinition = definition.toUpper();

	      /* Check if the definition is a simple 'include'...
	       * Naturally, this definition CANNOT be over-ridden!
	       */
	      if (fixedDefinition == "INCLUDE") {
		 gotDef = true;

		 if (!values.empty()) {
		    // Insert the string back a char
		    configData.insert(position + 1, read(values.front()));
		 }
	      } else {
		 // Look up the definition in the current definitions table
		 for (i = 0; (*currentDefs)[i].name != 0; i++) {
		    // Work out how many characters we should check
		    int checkChars = ((fixedDefinition.length() > 
				       (*currentDefs)[i].relevantChars) ?
				      fixedDefinition.length() :
				      (*currentDefs)[i].relevantChars);

		    // Check the name for a match
		    if (!strncmp(fixedDefinition.data(),
				 (*currentDefs)[i].name,
				 checkChars)) {
		       // Break out at this point since this is it.
		       break;
		    }
		 }

		 // Now that we have an entry, what do we do with it? A class?
		 if ((configData[position] == '{') && 
		     ((*currentDefs)[i].defTable || 
		      (*currentDefs)[i].classHandler)) {
		    gotDef = true;
		    // If this definition has a handler, call it
		    if ((*currentDefs)[i].classHandler != 0) {
		       // Leave parsing up to the specific handler
		       if (!((*currentDefs)[i].
			     classHandler(errString, definition, values, 
					  dataClass,
					  (*currentDefs)[i].variablePtr,
					  configData, ++position))) {
			  complain(segment,
				   "Error at '" + definition + "': " +
				   (errString.empty() ?
				    "Incompletely processed" : errString));
			  classSkipDepth++;
			  position--;
		       } else if (!errString.empty()) {
			  complain(segment,
				   "Warning at '" + definition + "': " +
				   errString);
		       }
		    
		       errString.clear();
		    } else {
		       // Recurse, effectively using ourself as a handler
		       if (!parse(configData, ++position,
				  (void *)(*currentDefs)[i].defTable, 
				  dataClass)) {
			  return false;
		       }
		    }
		 } else if ((configData[position] == ';') &&
			    ((*currentDefs)[i].variableHandler != 0)) {
		    // This must be a variable then.
		    gotDef = true;

		    // Call the handler to do its magic
		    if (!((*currentDefs)[i].
			  variableHandler(errString, definition, values,
					  dataClass,
					  (*currentDefs)[i].variablePtr))) {
		       complain(segment,
				"Error at '" + definition + "': " +
				(errString.empty() ?
				 "Discarded" : errString));
		    } else if (!errString.empty()) {
		       complain(segment,
				"Warning at '" + definition + "': " +
				errString);
		    }
		    
		    errString.clear();
		 }
	      }

	      // Did we get anything useful? Skip it if not
	      if (!gotDef) {
		 switch (configData[position]) {
		  case '{': // Class
		    // Increment classSkipDepth to force a depth change
		    classSkipDepth++;
		    complain(segment,
			     "Skipping unknown class '" + definition + '\'');
		    break;

		  default: // Variable
		    complain(segment,
			     "Skipping unknown variable '" + definition +
			     '\'');
		 }
	      }

	      // Reset our running variables and soldier on
	      definition.clear();
	      value.clear();
	      readDef = gotDef = false;
	      values.clear();
	      continue;
	   }

       case '}': // End of a class
	 // If we are skipping this class, we need only to do a depth change
	 if (classSkipDepth) {
	    classSkipDepth--;
	 } else {
	    // Return to a previous call of ourselves happily
	    return true;
	 }

	 continue;
      }

      /* If we got down here, we are just going to copy the character
       * across literally. We need to pick the right string...
       * No point copying a char across if we are skipping, though.
       */
      if (!classSkipDepth) {
	 if (readDef) {
	    value += configData[position];
	 } else {
	    definition += configData[position];
	 }
      }
   }

   // If we got here, all must be well...
   return true;
}


/* configure - Load the configuration file(s) and pass them to the parser
 * Original 13/03/2002 simonb
 */
bool ConfigParser::configure(void) const
{
   // Load up the main data
   String configData = read(filename);

   // Check..
   if (configData.empty()) {
      complain(filename, "Loading of the main configuration file failed!");
      return false;
   }

   // Our position indicator, we start at the start :)
   String::size_type position = 0;
   
   // Throw control over to the parser
   return parse(configData, position, topDefs, dataClass);
}
