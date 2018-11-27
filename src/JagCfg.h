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
#ifndef _jag_cfg_h_
#define _jag_cfg_h_

#include <stdlib.h>

#include <abax.h>
#include <JagDef.h>
#include <JagHashMap.h>

class JagDBServer;

class JagCfg
{
  public:
	// ctor
	JagCfg( int type = JAG_SERVER );
	~JagCfg();

	int init( int type );
	int destroy();
	int refresh();
	AbaxDataString  getValue( const AbaxString &name, const AbaxDataString &defaultValue="" ) const;
	AbaxDataString  getConfHOME() const;
	AbaxDataString  getJDBDataHOME( int objType=0 ) const;
	AbaxDataString  getTEMPDataHOME( int objType=0 ) const;
	AbaxDataString 	getTEMPJoinHOME() const;
	
	static const int _BLOCK= JAG_BLOCK_SIZE;
	int			_type;

  protected:
  	JagHashMap<AbaxString, AbaxString> *_map;

};

#endif
