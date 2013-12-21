#pragma once

#ifndef __ARC_DATETIME_H__
#define __ARC_DATETIME_H__

#include "Date.h"
#include "Time.h"

namespace Arc
{

	class DateTime :
		public ManagedObject
	{
	private:

		Date _date;
		Time _time;

	public:

		inline DateTime( Date date, Time time )
			: _date(date),
			  _time(time) { }

		inline DateTime( const DateTime& rhs )
			: _date(rhs._date),
			  _time(rhs._time) { }

		inline virtual ~DateTime( void ) { }

		inline virtual string toString( void ) const { return "DateTime"; }

		static inline DateTime now( void )
		{
			return DateTime(Date::now(), Time::now());
		}

		inline Date& getDate( void ) { return _date; }
		inline void setDate( Date val ) { _date = val; }

		inline Time& getTime( void ) { return _time; }
		inline void setTime( Time val ) { _time = val; }

	}; // class DateTime

} // namespace Arc

#endif // __ARC_DATETIME_H__