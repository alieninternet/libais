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

#ifndef _INCLUDE_AISUTIL_TIME_H_
# define _INCLUDE_AISUTIL_TIME_H_ 1

# include <string>
# include <ctime>
# include <sys/time.h>

namespace AISutil {
   //! Basic time routines (supposed to be simplistic)
   struct Time {
      //! Seconds (since the UNIX Epoch; 1970-01-01 00:00)
      signed long seconds;

      //! Nanoseconds (additional to 'seconds')
      signed long nanoseconds;


      //! Addition operator
      Time operator+(const Time& rhs) const;

      //! Subtraction operator
      Time operator-(const Time& rhs) const;

      //! Division operator
      double operator/(const Time& rhs) const;


      //! Convert this to a 'time_t' (we hope)
      operator time_t(void) const
	{
	   return time_t(seconds);
	};

      //! Convert this to a 'struct timespec'
      operator timespec(void) const
	{
	   timespec result;
	   result.tv_sec = seconds;
	   result.tv_nsec = nanoseconds;
	   return result;
	};

      //! Convert this to a 'struct timeval'
      operator timeval(void) const
	{
	   timeval result;
	   result.tv_sec = seconds;
	   result.tv_usec = nanoseconds / 1000;
	   return result;
	};


      //! Set the time to the time given (as a 'time_t')
      void setTime(const time_t& time)
	{
	   seconds = time;
	   nanoseconds = 0;
	};

      //! Set the time to the time given (as a 'struct timespec')
      void setTime(const timespec& time)
	{
	   seconds = time.tv_sec;
	   nanoseconds = time.tv_nsec;
	};

      //! Set the time to the time given (as a 'struct timeval')
      void setTime(const timeval& time)
	{
	   seconds = time.tv_sec;
	   nanoseconds = time.tv_usec * 1000;
	};

      //! Set the time to the time now (according to the local timezone)
      bool setTime(void);
   }; // struct Time
}; // namespace AISutil
   
#endif // _INCLUDE_AISUTIL_TIME_H_
