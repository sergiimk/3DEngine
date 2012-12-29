/*========================================================
* GUID.cpp
* @author Sergey Mikhtonyuk
* @date 22 April 2009
=========================================================*/
#include "GUID.h"
#include <string.h>
#include <iostream>
#include <stdio.h>

namespace Core
{
	namespace SCOM
	{
		//////////////////////////////////////////////////////////////////////////

		unsigned char* _InitGUIDTableLookup()
		{
			static unsigned char table[256];
			int	i;
			memset(table, 0, 256);

			for (i = 0; i < 10; i++) 
				table['0' + i] = i;

			for (i = 0; i < 6; i++) 
			{
				table['A' + i] = i+10;
				table['a' + i] = i+10;
			}

			return table;
		}

		//////////////////////////////////////////////////////////////////////////

		bool _GUIDFromString(GUID& id, const char* s)
		{
			int	i;
			static unsigned char *table = _InitGUIDTableLookup();

			if ((s[8]!='-') || (s[13]!='-') || (s[18]!='-') || (s[23]!='-'))
				return false;

			for (i=1; i<35; i++) 
			{
				if ((i == 8)||(i == 13)||(i == 18)||(i == 23)) 
					continue;
				if (!(((s[i] >= '0') && (s[i] <= '9'))  ||
					  ((s[i] >= 'a') && (s[i] <= 'f'))  ||
					  ((s[i] >= 'A') && (s[i] <= 'F'))))
					return false;
			}

			// in form {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}
			id.Data1 = (table[s[0]] << 28 | table[s[1]] << 24 | table[s[2]] << 20 | table[s[3]] << 16 |
						table[s[4]] << 12 | table[s[5]] << 8  | table[s[6]] << 4  | table[s[7]]);
			id.Data2 = table[s[9]] << 12 | table[s[10]] << 8 | table[s[11]] << 4 | table[s[12]];
			id.Data3 = table[s[14]] << 12 | table[s[15]] << 8 | table[s[16]] << 4 | table[s[17]];

			// these are just sequential bytes
			id.Data4[0] = table[s[19]] << 4 | table[s[20]];
			id.Data4[1] = table[s[21]] << 4 | table[s[22]];
			id.Data4[2] = table[s[24]] << 4 | table[s[25]];
			id.Data4[3] = table[s[26]] << 4 | table[s[27]];
			id.Data4[4] = table[s[28]] << 4 | table[s[29]];
			id.Data4[5] = table[s[30]] << 4 | table[s[31]];
			id.Data4[6] = table[s[32]] << 4 | table[s[33]];
			id.Data4[7] = table[s[34]] << 4 | table[s[35]];

			return true;
		}

		//////////////////////////////////////////////////////////////////////////

		bool GUID::FromString(const char* s)
		{
			if (!s) 
			{
				memset( this, 0, sizeof (GUID) );
				return true;
			}

			size_t size = strlen(s);
			if(size != 38 && size != 36)
				return false;

			if (size == 38 && ( s[0] != '{' || s[37] != '}' ) )
				return false;

			return size == 38 ? _GUIDFromString(*this, &s[1]) : _GUIDFromString(*this, s);
		}

		//////////////////////////////////////////////////////////////////////////

		void GUID::ToString(char* buf) const
		{
			static const char format[] = "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X";
			
			sprintf_s( buf, 37, format, Data1, Data2, Data3,
				Data4[0], Data4[1], Data4[2], Data4[3],
				Data4[4], Data4[5], Data4[6], Data4[7] );
		}

		//////////////////////////////////////////////////////////////////////////

		std::ostream& operator<<(std::ostream& os, const GUID& guid)
		{
			char buff[37];
			guid.ToString(buff);
			os << buff;
			return os;
		}

		//////////////////////////////////////////////////////////////////////////

		std::istream& operator>>(std::istream& is, GUID& guid)
		{
			char buff[39];
			is.get(buff, 37, '\n');
			if(buff[0] == '{')
				is.get(&buff[36], 3, '\n');

			if(!is) return is;
			if(!guid.FromString(buff))
				is.setstate(std::ios_base::failbit);

			return is;
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace