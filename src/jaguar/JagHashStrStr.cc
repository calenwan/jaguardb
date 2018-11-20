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
#include <JagGlobalDef.h>
#include <JagHashStrStr.h>
#include <JagUtil.h>

// ctor
JagHashStrStr::JagHashStrStr()
{
	//prt(("s8540 JagHashStrStr simple ctor this=%x\n", this ));
	jag_hash_init( &_hash, 10 );
	_len = 0;
}

// dtor
JagHashStrStr::~JagHashStrStr()
{
	//prt(("s8540 JagHashStrStr dtor this=%x\n", this ));
	jag_hash_destroy( &_hash );
}

bool JagHashStrStr::addKeyValue( const AbaxDataString & key, const AbaxDataString &val )
{
	if ( key.size() < 1 ) return 0;
	int rc = jag_hash_insert( &_hash, key.c_str(), val.c_str() );
	if ( rc ) {
		++ _len;
		//prt(("s3039 JagHashStrStr::addKeyValue this=%0x key=[%s] val=%d\n", this, key.c_str(), val ));
		return true;
	} 
	return false;
}

void JagHashStrStr::removeKey( const AbaxDataString & key )
{
	if ( key.size() < 1 ) return;
	int rc = jag_hash_delete( &_hash, key.c_str() );
	if ( rc ) {
		-- _len;
		//prt(("s2039 JagHashStrStr::removeKey this=%0x key=[%s]\n", this, key.c_str() ));
	}
}

bool JagHashStrStr::keyExist( const AbaxDataString & key ) const
{
	if ( key.size() < 1 ) return false;
	char *pval = jag_hash_lookup( &_hash, key.c_str() );
	if ( pval ) return true;
	return false;
}

char* JagHashStrStr::getValue( const AbaxDataString &key ) const
{
	return jag_hash_lookup( &_hash, key.c_str() );
}

AbaxDataString JagHashStrStr::getValue( const AbaxDataString &key, bool &rc ) const
{
	char *p = jag_hash_lookup( &_hash, key.c_str() );
	if ( p ) {
		rc = true;
		return p;
	} else {
		rc = false;
		return "";
	}
}

bool JagHashStrStr::getValue( const AbaxDataString &key, AbaxDataString &val ) const
{
	char *p = jag_hash_lookup( &_hash, key.c_str() );
	if ( p ) {
		val = p;
		return true;
	} else {
		val = "";
		return false;
	}
}

void JagHashStrStr::reset()
{
	jag_hash_destroy( &_hash );
	jag_hash_init( &_hash, 10 );
}


// copy ctor 
JagHashStrStr::JagHashStrStr( const JagHashStrStr &o )
{
	//prt(("s8540 JagHashStrStr copy ctor this=%x o=%0x\n", this, &o ));
	jag_hash_init( &_hash, 10 );

	HashNodeT *node;
	for ( int i = 0; i < o._hash.size; ++i ) {
		node = o._hash.bucket[i];
		while ( node != NULL ) {
			jag_hash_insert( &_hash, node->key, node->value );
			node = node->next;
		}
	}
}

// assignment =
JagHashStrStr& JagHashStrStr:: operator= ( const JagHashStrStr &o )
{
	if ( this == &o ) return *this;
	//prt(("s8820 JagHashStrStr this=%0x assignment by o=%0x\n", this, &o ));

	reset();

	HashNodeT *node;
	for ( int i = 0; i < o._hash.size; ++i ) {
		node = o._hash.bucket[i];
		while ( node != NULL ) {
			jag_hash_insert( &_hash, node->key, node->value );
			node = node->next;
		}
	}

	return *this;
}

/***
JagVector<AbaxPair<AbaxDataString,AbaxDataString>> JagHashStrStr::getStrStrVector()
{
	JagVector<AbaxPair<AbaxDataString,AbaxDataString>> vec;

	HashNodeT *node;
	AbaxDataString key;
	AbaxDataString val;
	for ( int i = 0; i < _hash.size; ++i ) {
		node = _hash.bucket[i];
		while ( node != NULL ) {
			key = node->key;
			val = node->value;
			AbaxPair<AbaxDataString,AbaxDataString> pair(key, val);
			vec.append( pair );
			node = node->next;
		}
	}

	return vec;
}
***/

AbaxDataString JagHashStrStr::getKVStrings( const char *sep)
{
	AbaxDataString res;

	HashNodeT *node;
	for ( int i = 0; i < _hash.size; ++i ) {
		node = _hash.bucket[i];
		while ( node != NULL ) {
			if ( res.size() < 1 ) {
				res = AbaxDataString(node->key) + "=" + node->value;
			} else {
				res += AbaxDataString(sep) + AbaxDataString(node->key) + "=" + node->value;
			}
			node = node->next;
		}
	}

	return res;
}


int JagHashStrStr::size()
{
	return _len;
}

void JagHashStrStr::removeAllKey()
{
	reset();
}

