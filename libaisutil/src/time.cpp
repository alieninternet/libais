/* $Id$
 * 
 * Copyright (c) 1996,2003 Alien Internet Services
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

#include "aisutil/time.h"

using namespace AISutil;


/* Addition operator
 * Original 21/05/1996 pickle
 */
Time Time::operator+(const Time& rhs) const
{
   Time result;
   
   // Do the addition
   result.seconds = seconds + rhs.seconds;
   result.nanoseconds = nanoseconds + rhs.nanoseconds;
   
   // Replace the overflowed nanoseconds (if any)
   while (result.nanoseconds >= 1000000000) {
      result.seconds++;
      result.nanoseconds -= 1000000000;
   }
   
   return result;
}


/* Subtraction operator
 * Original 21/05/1996 pickle
 */
Time Time::operator-(const Time& rhs) const
{
   Time result;
   
   // Do the addition
   result.seconds = seconds - rhs.seconds;
   result.nanoseconds = nanoseconds - rhs.nanoseconds;
   
   // Replace the overflowed nanoseconds (if any)
   while (result.nanoseconds < 0) {
      result.seconds--;
      result.nanoseconds += 1000000000;
   }
   
   return result;
}


/* Division operator
 * Original 23/05/1996 pickle
 */
double Time::operator/(const Time& rhs) const
{
   unsigned long long a = (seconds * 1000000000) + nanoseconds;
   unsigned long long b = (rhs.seconds * 1000000000) + rhs.nanoseconds;
   
   return (a / b);
}


/* setTime - Set the time (according to the time locally)
 * Original 20/05/1996 pickle
 */
bool Time::setTime(void)
{  
   struct timeval time;

   // Obtain the time
   if (gettimeofday(&time, NULL) == 0) {
      // Copy the time across accordingly
      setTime(time);
      return true;
   }
   
   // Something went wrong..
   return false;
}
