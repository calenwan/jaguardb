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
#ifndef _jag_line_file_h_
#define _jag_line_file_h_

#include <abax.h>
#include <stdio.h>

class JagLineFile
{
  public:
	JagLineFile( int bufline = 10000 );
	~JagLineFile();
	void append( const AbaxDataString &line );
	abaxint size() const;
	JagLineFile& operator+= ( JagLineFile &f2 );


	void startRead();
	bool getLine( AbaxDataString &line );
	bool hasData();
	bool _hasStartedRead;
	bool print() const;

  protected:
    AbaxDataString *_buf;
	FILE *_fp;
	int  _bufLen;
	int  _bufMax;
	abaxint _fileLen;
	AbaxDataString _fname;
	abaxint  _i;

	//pthread_mutex_t _mutex; 
	
};

#endif
