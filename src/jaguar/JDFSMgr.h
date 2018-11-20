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
#ifndef _JDFS_MGR_H_
#define _JDFS_MGR_H_

#include <abax.h>
#include <JagHashMap.h>

// manages all files
class JDFSMgr
{
	public:
		JDFSMgr();
		~JDFSMgr();

		int  open( const AbaxString &fpath, bool force=false );
		int  close( const AbaxString &fpath );
		int  getFD( const AbaxString &fpath );
		int  rename( const AbaxString &fpath, const AbaxString &newfpath );
		int  remove( const AbaxString &fpath );
		bool exist( const AbaxString &fpath );
		int mkdir( const AbaxString &fpath );
		int rmdir( const AbaxString &fpath );
		abaxint getStripeSize( const AbaxString &fpath, size_t kvlen, size_t stripeSize );
		abaxint getFileSize( const AbaxString &fpath, size_t kvlen );
		abaxint  pread( int fd, void *buf, size_t count, abaxint offset);
		abaxint  pwrite(int fd, const void *buf, size_t count, abaxint offset);


  protected:

		JagHashMap<AbaxString,AbaxInt> *_map;
};

// todo: pass KVLEN, stripeSIZE, STRIPES to file

#endif

