#pragma once

#ifndef __ARC_DATE_H__
#define __ARC_DATE_H__

#include "Common.h"
#include "ManagedObject.h"
#include "WeekDay.h"
#include "Month.h"

namespace Arc
{

	class Date :
		public ManagedObject
	{
	private:

		WeekDays _weekDay;
		unsigned int _day;
		Months _month;
		unsigned int _year;
		
	public:

		inline Date( WeekDays days = INVALID_WEEK_DAY, unsigned int weeks = 0, Months months = INVALID_MONTH, unsigned int years = 0 )
			: _weekDay(days),
			_day(weeks),
			_month(months),
			_year(years) { }

		inline Date( const Date& rhs )
			: _weekDay(rhs._weekDay),
			_day(rhs._day),
			_month(rhs._month),
			_year(rhs._year) { }

		inline virtual ~Date( void ) { }

		inline virtual string toString( void ) const { return "Date"; }

		static inline Date today( void )
		{
			time_t rawtime;
			struct tm * timeinfo;

			time (&rawtime);
			timeinfo = localtime (&rawtime);

			// TODO Implement millisecond grab for Now
			return Date((WeekDays)timeinfo->tm_wday, timeinfo->tm_mday, (Months)timeinfo->tm_mon, timeinfo->tm_year);
		}

		inline WeekDays getWeekDay( void ) const { return _weekDay; }
		inline void setWeekDay( WeekDays val ) { _weekDay = val; }

		inline unsigned int getDay( void ) const { return _day; }
		inline void setDay( unsigned int val ) { _day = val; }

		inline Months getMonths( void ) const { return _month; }
		inline void setMonths( Months val ) { _month = val; }

		inline unsigned int getYears( void ) const { return _year; }
		inline void setYears( unsigned int val ) { _year = val; }

	}; // class Time

} // namespace Arc

#endif __ARC_DATE_H__