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
#ifndef _jag_strsplit_with_quote_h_
#define _jag_strsplit_with_quote_h_

#include <abax.h>

class  JagSplitPosition
{
   public:
	   char *parsestart, *savestart, *saveend;
};

class JagStrSplitWithQuote
{
	public:   

		JagStrSplitWithQuote();
		JagStrSplitWithQuote(const char* str, char sep = ';');
		void init(const char* str, char sep);

		void destroy();
		~JagStrSplitWithQuote();

	    const AbaxDataString& operator[]( int i ) const;
		abaxint length() const;
		bool  exists(const AbaxDataString &token) const;
		void	print();

	private:
		AbaxDataString *list_;
		abaxint length_;
		char sep_;
};

#endif
