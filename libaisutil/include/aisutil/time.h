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

namespace AIS {
   namespace Util {
      /**
       * \brief Basic time routines
       * 
       * These basic time routines are intended to be extremely simplistic.
       * 
       * Intentionally, this class doesn't offer any special date formatting
       * routines, since such routines are already provided by \e Standard-C
       * and \e POSIX \e 1003.1-2001.
       * 
       * The class offers the ability to store time in seconds and nanoseconds,
       * however the precision of the nanoseconds field is based primarily on
       * the operating system and architecture of the machine you compile the
       * library on.
       * 
       * The time routines also offer a convenient way to convert between
       * common time types, such as \c time_t, \c struct \c timespec and
       * \c struct \c timeval (if they are available).
       * 
       * The two most important factors of these routines are the arithmetic
       * functions and the boolean functions. Times can be easily added,
       * subtracted, and divided, with nanoseconds overflowing into seconds
       * appropriately. Comparisons between times are equally simplified.
       * 
       * The ability to obtain the current system time has been provided
       * purely for convenience.
       */
      struct Time {
	 //! Type of the seconds variable
	 typedef signed long seconds_type;
	 
	 //! Type of the nanoseconds variable
	 typedef signed long nanoseconds_type;
	 
	 /**
	  * \brief Number of seconds
	  *
	  * This is the number of seconds field. If the time set from the
	  * system, this represents the number of seconds since the \e UNIX
	  * \e Epoch (1970-01-01 00:00:00.0)
	  */
	 seconds_type seconds;
	 
	 /**
	  * \brief Number of nanoseconds
	  * 
	  * This is the number of nanoseconds, following the \p seconds count.
	  */
	 nanoseconds_type nanoseconds;
	 
	 
	 /**
	  * \brief Default constructor
	  *
	  * This is a blank constructor, and will initialise the structure to
	  * zeros.
	  */
	 Time(void)
	   : seconds(0),
	     nanoseconds(0)
	   {};
      
	 /**
	  * \brief Copy constructor
	  * 
	  * Creates a brand new copy of another Time structure
	  * 
	  * \param time The Time structure to create a copy from
	  */
	 Time(const Time& time)
	   : seconds(time.seconds),
	     nanoseconds(time.nanoseconds)
	   {};
      
	 /**
	  * \brief Current time constructor
	  * 
	  * For convenience, passing a boolean value of \c true here will
	  * cause the current system time to be set on this object when it is
	  * created. The result will be a Time structure representing the time
	  * it was created.
	  */
	 explicit Time(const bool setTimeNow)
	   : seconds(0), nanoseconds(0)
	   {
	      if (setTimeNow) {
		 (void)setTime();
	      }
	   };
      
	 /**
	  * \brief Constructor (from a '\c time_t')
	  * 
	  * Convert a time of the \c time_t type into a new Time structure.
	  * 
	  * \param time The time you wish to convert, of \c time_t type
	  */
	 Time(const time_t& time)
	   : seconds(time),
	     nanoseconds(0)
	   {};
      
	 /**
	  * \brief Constructor (from a '\c struct \c timespec')
	  * 
	  * This will convert a \c struct \c timespec time structure into a
	  * Time structure.
	  * 
	  * \param time The \c struct \c timespec time you wish to convert
	  */
	 Time(const struct timespec& time)
	   : seconds(time.tv_sec),
	     nanoseconds(time.tv_nsec)
	   {};
      
	 /**
	  * \brief Constructor (from a '\c struct \c timeval')
	  * 
	  * This will convert a \c struct \c timeval structure to a Time
	  * structure. Note that the precision of the \c timeval structure is
	  * only as small as \e microseconds.
	  * 
	  * \param time A \c struct \c timeval time to convert
	  */
	 Time(const struct timeval& time)
	   : seconds(time.tv_sec),
	     nanoseconds(time.tv_usec * 1000)
	   {};
      
      
	 //! Destructor
	 ~Time(void)
	   {};
	 
	 
	 //! Addition operator
	 const Time operator+(const Time& rhs) const;
	 
	 //! Addition assignment operator
	 const Time& operator+=(const Time& rhs)
	   { return ((*this) = (*this) + rhs); };
	 
	 //! Subtraction operator
	 const Time operator-(const Time& rhs) const;
	 
	 //! Subtraction assignment operator
	 const Time& operator-=(const Time& rhs)
	   { return ((*this) = (*this) - rhs); };
	 
	 //! Division operator
	 const double operator/(const Time& rhs) const;
	 
	 
	 //! Equality operator
	 const bool operator==(const Time& rhs) const
	   {
	      return ((seconds == rhs.seconds) &&
		      (nanoseconds == rhs.nanoseconds));
	   };
	 
	 //! Not equal-to operator
	 const bool operator!=(const Time& rhs) const
	   { return (!((*this) == rhs)); };
	 
	 //! Greater-than operator
	 const bool operator>(const Time& rhs) const
	   {
	      if ((seconds > rhs.seconds) ||
		  ((seconds == rhs.seconds) &&
		   (nanoseconds > rhs.nanoseconds))) {
		 return true;
	      }
	      return false;
	   };
	 
	 //! Less-than operator
	 const bool operator<(const Time& rhs) const
	   {
	      if ((seconds < rhs.seconds) ||
		  ((seconds == rhs.seconds) &&
		   (nanoseconds < rhs.nanoseconds))) {
		 return true;
	      }
	      return false;
	   };
	 
	 //! Greater-than or equal to operator
	 const bool operator>=(const Time& rhs) const
	   { return (!((*this) < rhs)); };
	 
	 //! Less-than or equal to operator
	 const bool operator<=(const Time& rhs) const
	   { return (!((*this) > rhs)); };
	 
	 
	 //! Convert this to a 'time_t' (we hope)
	 operator time_t(void) const
	   { return time_t(seconds); };
	 
	 //! Convert this to a 'struct timespec'
	 operator struct timespec(void) const
	   {
	      struct timespec result;
	      result.tv_sec = seconds;
	      result.tv_nsec = nanoseconds;
	      return result;
	   };
	 
	 //! Convert this to a 'struct timeval'
	 operator struct timeval(void) const
	   {
	      struct timeval result;
	      result.tv_sec = seconds;
	      result.tv_usec = nanoseconds / 1000;
	      return result;
	   };
	 
	 
	 //! Assignment operator (from a 'time_t')
	 const Time& operator=(const time_t& time)
	   {
	      this->seconds = time;
	      this->nanoseconds = 0;
	      return (*this);
	   };
	 
	 //! Assignment operator (from a 'struct timespec')
	 const Time& operator=(const struct timespec& time)
	   {
	      this->seconds = time.tv_sec;
	      this->nanoseconds = time.tv_nsec;
	      return (*this);
	   };
	 
	 //! Assignment operator (from a 'struct timeval')
	 const Time& operator=(const struct timeval& time)
	   {
	      this->seconds = time.tv_sec;
	      this->nanoseconds = time.tv_usec * 1000;
	      return (*this);
	   };
	 
	 
	 //! Set the time to the time now (according to the local timezone)
	 const bool setTime(void);
      }; // struct Time
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_TIME_H_
