/* $Id$
 * 
 * Copyright (c) 1996,1998,2001,2003 Alien Internet Services
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

#include <cctype>

# ifdef HAVE_FNMATCH_H
// Define this if you want to use fnmatch() instead of our match() routines
// .. which we want to do, because I broke our match() routines and cbf'd
// fixing them for now :(
#  define USING_FNMATCH
#  ifdef USING_FNMATCH
extern "C" {
#   include <fnmatch.h>
}
#  endif
# endif

#include "aisutil/string/mask.h"

using namespace AIS::Util;


/* matches - Do a mask check (case-insensitive)
 * Original 28/04/2003 pickle
 */
const bool StringMask::matches(const char* str) const
{
#ifdef USING_FNMATCH
   return (fnmatch(data(), str, FNM_CASEFOLD) == 0);
#else
   abort(); // eek.
#endif
}


/* matchesCase - Do a mask check (case-sensitive)
 * Original 28/04/2003 pickle
 */
const bool StringMask::matchesCase(const char* str) const
{
#ifdef USING_FNMATCH
   return (fnmatch(data(), str, 0) == 0);
#else
   abort();
#endif
}
