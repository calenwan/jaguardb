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
#ifndef _JagParseAttribute_h_
#define _JagParseAttribute_h_

class JagCfg;
class JagDBServer;

class JagParseAttribute
{
  public:
	int timediff;
	int servtimediff;
	AbaxDataString dfdbname;
	const JagCfg *cfg;
	const JagDBServer *servobj;

	JagParseAttribute()
	{
		timediff = 0;
		servtimediff = 0;
		//dfdbname = "";
		cfg = NULL;
		servobj = NULL;
	}

	JagParseAttribute( const JagDBServer *iservobj, int itimediff=0, int iservtimediff=0, 
					   AbaxDataString idbname="", const JagCfg *icfg=NULL ) 
    {
		timediff = itimediff;
		servtimediff = iservtimediff;
		dfdbname = idbname;
		cfg = icfg;
		servobj = iservobj;
	}

	void clean() {
		timediff = 0;
		servtimediff = 0;
		dfdbname = "";
	}
};

#endif
