/*
 * Copyright (C) 2018 DataJaguar, Inc.
 *
 * This file is part of JaguarDB.
 *
 * JaguarDB is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * JaguarDB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JaguarDB (LICENSE.txt). If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _jag_time_h_
#define _jag_time_h_

#include <time.h>
#include <abax.h>
#include <JagParseAttribute.h>

class JagTime
{
	public:
		static int getTimeZoneDiff();  //  minutes
		static abaxint mtime();  //  time(NULL) + milliseconds
		static abaxint utime();  //  time(NULL) + microseconds
		static AbaxDataString makeRandDateTimeString( int N);
		static AbaxDataString makeRandTimeString();
		static AbaxDataString YYYYMMDDHHMM();
		static AbaxDataString YYYYMMDD();

		static AbaxDataString makeNowTimeStringSeconds();
		static AbaxDataString makeNowTimeStringMilliSeconds();
		static AbaxDataString makeNowTimeStringMicroSeconds();
		static abaxint nowMilliSeconds();
		static AbaxDataString nowYear();

		//static AbaxDataString rawToServerString( const JagParseAttribute &jpa, time_t rawSeconds, const AbaxDataString &ttype );
		static void setTimeInfo( const JagParseAttribute &jpa , const char *str, struct tm &timeinfo, int isTime );

		static AbaxFixString getValueFromTimeOrDate( const JagParseAttribute &jpa, const AbaxFixString &str,
 													 const AbaxFixString &str2, int op, const AbaxDataString &ddif );

		static void convertDateTimeToLocalStr( const AbaxDataString& instr, AbaxDataString& outstr, bool isnano=false );
		static void convertTimeToStr( const AbaxDataString& instr, AbaxDataString& outstr, int tmtype=2 );
		static void convertDateToStr( const AbaxDataString& instr, AbaxDataString& outstr );
		static int convertDateTimeFormat( const JagParseAttribute &jpa, char *outbuf, const char *inbuf, 
										  const int offset, const int length, bool isnano=false );

		static int convertTimeFormat( char *outbuf, const char *inbuf, const int offset, const int length, bool isnano = false );
		static int convertDateFormat( char *outbuf, const char *inbuf, const int offset, const int length );
		static abaxint getDateTimeFromStr( const JagParseAttribute &jpa, const char *str, bool isnano=false );
		static abaxint getTimeFromStr( const char *str, bool isnano=false );
		static bool getDateFromStr( const char *instr, char *outstr );





};

#endif
