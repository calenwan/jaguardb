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

#include <abax.h>
#include <JagUtil.h>

AbaxFixString::AbaxFixString() 
{
		_buf = NULL;
		_length = 0;
		_readOnly = false;
}

AbaxFixString::AbaxFixString( const char *str, unsigned int len ) 
{ 
		_readOnly = false;

		_buf = (char*)jagmalloc(len+1);
		memcpy( _buf, str, len );
		_buf[len] = '\0';
		_length = len;
}

/***
// AbaxFixString::AbaxFixString( unsigned int len ) 
{ 
		_readOnly = false;
		_buf = (char*)jagmalloc(len+1);
		memset( _buf, 0, len+1);
		_length = len;
		printf("s3939 AbaxFixString(int) called\n"); fflush( stdout );
}
******/

AbaxFixString::AbaxFixString( const AbaxFixString &str ) 
{ 
		_readOnly = false;
		int len = str._length;
		_buf = (char*)jagmalloc(len+1);
		memcpy( _buf, str._buf, len );
		_buf[len] = '\0';
		_length = len;
}
	
AbaxFixString::AbaxFixString( const AbaxDataString &str ) 
{ 
		_readOnly = false;
		int len = str.size();
		_buf = (char*)jagmalloc(len+1);
		memcpy( _buf, str.c_str(), len );
		_buf[len] = '\0';
		_length = len;
		// printf("s3929 AbaxFixString(int) called\n"); fflush( stdout );
}

AbaxFixString& AbaxFixString:: operator=( const AbaxFixString &str ) 
{ 
		if ( _buf == str._buf ) {
			return *this;
		}

		if ( _buf && ! _readOnly ) {
			free ( _buf );
		}

		int len = str._length;
		_buf = (char*)jagmalloc(len+1);
		memcpy( _buf, str._buf, len );
		_length = len;
		_buf[len] = '\0';
		_readOnly = false;
		return *this;
}
 		
AbaxFixString& AbaxFixString:: operator=( const AbaxDataString &str ) 
{ 
		if ( _buf && ! _readOnly ) {
			free ( _buf );
		}

		int len = str.size();
		_buf = (char*)jagmalloc(len+1);
		memcpy( _buf, str.c_str(), len );
		_buf[len] = '\0';
		_length = len;
		_readOnly = false;
		return *this;
}

int AbaxFixString::operator== ( const AbaxFixString &s2 )  const 
{
    return (memcmp(_buf, s2._buf, _length ) == 0);
}


int AbaxFixString::operator< ( const AbaxFixString &s2 ) const 
{
		if ( ! _buf && ! s2._buf ) return 0;
		if ( ! _buf ) return 1;
		if ( ! s2._buf ) return 0;
    return (memcmp(_buf, s2._buf, _length ) < 0);
}

int AbaxFixString::operator<= ( const AbaxFixString &s2 ) const 
{
		if ( ! _buf && ! s2._buf ) return 1;
		if ( ! _buf ) return 1;
		if ( ! s2._buf ) return 0;
    return (memcmp(_buf, s2._buf, _length ) <= 0);
}

int AbaxFixString::operator> ( const AbaxFixString &s2 ) const 
{
		if ( ! _buf && ! s2._buf ) return 0;
		if ( ! _buf ) return 0;
		if ( ! s2._buf ) return 1;
   	return (memcmp(_buf, s2._buf, _length ) > 0);
}

int AbaxFixString::operator>= ( const AbaxFixString &s2 ) const 
{
		if ( ! _buf && ! s2._buf ) return 1;
		if ( ! _buf ) return 0;
		if ( ! s2._buf ) return 1;
   	return (memcmp(_buf, s2._buf, _length ) >= 0);
}

AbaxFixString& AbaxFixString::operator+= (const AbaxFixString &s ) 
{
		_buf = (char*)realloc( (void*)_buf, _length+s._length+1 );
		memcpy( _buf+_length, s._buf, s._length );
		_buf[_length+s._length] = '\0';
		_length += s._length;
		_readOnly = false;
		return *this;
}

AbaxFixString AbaxFixString::operator+ (const AbaxFixString &s ) const 
{
		AbaxFixString res = *this;
		res += s;
		return res;
}

void AbaxFixString::point( const AbaxFixString &fs )
{
	point( fs.c_str(), fs.length() );
}

void AbaxFixString::point(const char *str, unsigned int len )
{
		if ( _buf && ! _readOnly ) {
			free( _buf );
		}

		_buf = (char*)str;
		_length = len;
		_readOnly = true;
}

AbaxFixString::AbaxFixString( const char *str, unsigned int len, bool ref ) 
{
		_readOnly = true;
		point( str, len );
}

// caller make sure length(data) <= _length
void AbaxFixString::strcpy( const char *data )
{
	::strcpy(_buf, data );
}

AbaxFixString::~AbaxFixString()
{
	if ( _readOnly ) {
		return;
	}

	if ( _buf )
	{
		free ( _buf );
	    // _num -= _length;
	}
	_buf = NULL;
}

/********
// inline abaxint hashCode64() const 
abaxint AbaxFixString::hashCode() const 
{
    unsigned int hash[4];                
    unsigned int seed = 42;             
    register void *str = (void *)_buf;
    int len = _length;
    MurmurHash3_x64_128( str, len, seed, hash);
    uint64_t res2 = ((uint64_t*)hash)[0]; 
    abaxint res = res2 % LLONG_MAX;
    return res;
}
*******/
// inline abaxint hashCode64() const 
abaxint AbaxFixString::hashCode() const 
{
    unsigned int hash[4];                
    unsigned int seed = 42;             
    register void *str = (void *)_buf;
	char *p;
	char *newbuf = (char*)jagmalloc( _length + 1 );
	memset( newbuf, 0, _length +1);
	int len = 0;
	p = newbuf;
	for ( int i =0; i < _length; ++i ) {
		if ( _buf[i] != '\0' ) {
			*p ++ = _buf[i];
			++len;
		}
	}
	//printf("s6231 buf=[%s] newbuf=[%s]\n", _buf, newbuf );

    // MurmurHash3_x64_128( str, len, seed, hash);
    MurmurHash3_x64_128( (void*)newbuf, len, seed, hash);

    uint64_t res2 = ((uint64_t*)hash)[0]; 
    abaxint res = res2 % LLONG_MAX;
	// printf("s9226 AbaxFixString::hashCode() buf=[%s] newbuf=[%s] hashcode=%lld _length=[%lld]\n", _buf, newbuf, res, _length );
	free( newbuf );
    return res;
}


void AbaxFixString::ltrim()
{
	int i;
	char *p = _buf;
	if ( *p != ' ' && *p != '\t' && *p != '\r' && *p != '\n' ) return;
	while ( *p == ' ' || *p == '\t' && *p == '\r' && *p == '\n' ) ++p;
	int d = p-_buf; 
	for ( i = d; i < _length; ++i ) {
		_buf[i-d] = _buf[i];
	}
	for ( i = _length-d; i < _length; ++i ) {
		_buf[i] = '\0';
	}
}

void AbaxFixString::rtrim()
{
	if ( _buf[0] == '\0' ) return;
	char *p = _buf + _length - 1;
	while ( *p == '\0' && p != _buf ) --p;
	if ( p == _buf ) return;
	while ( *p == ' ' || *p == '\t' && *p == '\r' && *p == '\n' ) { *p = '\0'; --p; }
}

void AbaxFixString::trim()
{
	ltrim();
	rtrim();
}

void AbaxFixString::substr( abaxint start, abaxint len )
{
	int i;
	if ( start < 0 ) start = 0;
	else if ( start >= _length ) start = _length-1;

	/**
	if ( len > (_length - start) ) {
		len = _length - start;
	}
	**/

	if ( len < 0 ) {
		/**
    	for ( i = start; i < _length; ++i ) {
    		_buf[i-start] = _buf[i];
    	}
    	for ( i = _length-start; i < _length; ++i ) {
    		_buf[i] = '\0';
    	}
		**/
	} else if ( len == 0 ) {
		memset( _buf, 0, _length );
	} else {
		if ( start + len > _length ) {
			len = _length - start;
		}

    	for ( i = start; i < start + len; ++i ) {
    		_buf[i-start] = _buf[i];
    	}
    	for ( i = len; i < _length; ++i ) {
    		_buf[i] = '\0';
    	}
	}
}

AbaxFixString AbaxFixString::concat( const AbaxFixString& s2 )
{
	int s2len = s2.length();
	char newbuf[_length + s2len + 1 ];
	char *p, *pb;
	pb = newbuf;
	for ( p = _buf; *p != '\0' && (p-_buf)<_length; ++p ) {
		*pb++ = *p;
	}

	for ( p = (char*)s2.c_str(); p < (char*)s2.c_str() + s2len; ++p ) {
		*pb++ = *p;
	}
	*pb = '\0';

	return AbaxFixString( newbuf, _length + s2len );
}


void AbaxFixString::dump() const
{
	printf("fixstr: ");
	for ( int i=0; i < _length; ++i ) {
		if ( _buf[i] ) {
			printf("%c", _buf[i] );
		} else {
			printf("\\0" );
		}
	}
	printf("\n"); fflush( stdout );
}

void AbaxFixString::replace( char oldc, char newc )
{
	for ( int i=0; i < _length; ++i ) {
		if ( oldc == _buf[i] ) {
			_buf[i] = newc;
		}
	}
}


AbaxDataString AbaxFixString::firstToken( char sep ) const
{
    if ( _length < 1 ) return "";
    char *p = _buf;
    while ( *p != sep && *p != '\0' ) ++p;
    return AbaxCStr(_buf, p-_buf);
}

