/* $Id$
 * 
 * Copyright (c) 2003 Alien Internet Services
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

#include <aisutil/string/string.h>

#include "tests.h"

using namespace AIS::Util;


int main(int argc, char **argv)
{
   TEST_STATUS("toLower()");
   TEST_ASSERT(String("EJiejfEF8913r~!@#$%^&*()_").toLower() == 
	       "ejiejfef8913r~!@#$%^&*()_");
   
   TEST_STATUS("toUpper()");
   TEST_ASSERT(String("EJiejfEF8913r~!@#$%^&*()_").toUpper() ==
	       "EJIEJFEF8913R~!@#$%^&*()_");
   
   
   TEST_STATUS("toInt()");
   TEST_ASSERT((String("113487613").toInt() == 113487613) &&
	       (String("+971864").toInt() == 971864) &&
	       (String("-8173418").toInt() == -8173418) &&
	       (String("0").toInt() == 0));
   
   TEST_STATUS("toLong()");
   TEST_ASSERT((String("2085725464").toLong() == 2085725464) &&
	       (String("+82347211").toLong() == 82347211) &&
	       (String("-392841").toLong() == -392841) &&
	       (String("0").toLong() == 0));
   
   TEST_STATUS("toDouble()");
   TEST_ASSERT((String("98731.2389").toDouble() == 98731.2389) &&
	       (String("+8723.1238").toDouble() == 8723.1238) &&
	       (String("-132.487124").toDouble() == -132.487124) &&
	       (String("987112398").toDouble() == 987112398.0) &&
	       (String("-837123").toDouble() == -837123.0) &&
	       (String("0").toDouble() == 0));

   
   TEST_STATUS("prepad()");
   String prepad("12345");
   TEST_ASSERT((prepad.prepad(10).length() == 10) &&
	       (prepad.prepad(5).length() == 5) &&
	       (prepad.prepad(1).length() == 5) &&
	       (prepad.prepad(10)[0] == ' ') &&
	       (prepad.prepad(10, '\0')[0] == '\0'));
   
   
   TEST_STATUS("trim()");
   TEST_ASSERT((String("\tblah\t").trim() == "blah") &&
	       (String("  blah  ").trim() == "blah") &&
	       (String("\r\n\tblah\t\n\r").trim() == "blah") &&
	       (String("\t   \tblah blah  \t ").trim() == "blah blah"));

   TEST_STATUS("trimQuotes()");
   TEST_ASSERT((String("'blah'").trimQuotes() == "blah") &&
	       (String("'\"blah\"'").trimQuotes() == "blah"));
   
   
   TEST_STATUS("clear()");
   String cleared("kafhkhfea");
   cleared.clear();
   TEST_ASSERT(cleared.empty() &&
	       (cleared == "") &&
	       (cleared.length() == 0));


   TEST_END;
}
