/*========================================================
* GUID.h
* @author Sergey Mikhtonyuk
* @date 23 July 2009
=========================================================*/
#ifndef _SCOM_GUID_H__
#define _SCOM_GUID_H__

#include <memory.h>
#include <cassert>
#include <iosfwd>

namespace Core
{
	namespace SCOM
	{

		//////////////////////////////////////////////////////////////////////////

	
		/// GUID structure
		/** Used to uniquely identify interface between modules 
		 *  @ingroup SCOM */
		struct GUID 
		{
			//@{
			/** Data fields */
			unsigned long  Data1;
			unsigned short Data2;
			unsigned short Data3;
			unsigned char  Data4[ 8 ];
			//@}
	
			/// Comparison operator
			bool operator == (const SCOM::GUID& rhs) const
			{
				return !memcmp(this, &rhs, sizeof(SCOM::GUID));
			}
	
			/// Comparison operator
			bool operator != (const SCOM::GUID& rhs) const
			{
				return !(this->operator ==(rhs));
			}

			/// Comparison operator
			bool operator < (const SCOM::GUID& rhs) const
			{
				if(Data1 < rhs.Data1 || Data2 < rhs.Data2 || Data3 < rhs.Data3)
					return true;

				for(int i = 0; i < 8; ++i)
					if(Data4[i] < rhs.Data4[i])
						return true;

				return false;
			}

			/// Sets data to zero
			void SetZero()
			{
				memset(this, 0, sizeof(SCOM::GUID));
			}

			/// Checks is GUID is zero
			bool IsZero() const
			{
				GUID zero = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };
				return memcmp(this, &zero, sizeof(GUID)) == 0;
			}

			/// Parses the GUID string
			bool FromString(const char* s);

			/// Buffer must be 37 bytes long
			void ToString(char* buf) const;
		};

		//////////////////////////////////////////////////////////////////////////

		inline GUID _GUIDFromString(const char* s)
		{
			GUID g;
			bool r = g.FromString(s);
			assert(r);
			return g;
		}

		//////////////////////////////////////////////////////////////////////////

		std::ostream& operator<<(std::ostream& os, const GUID& guid);

		std::istream& operator>>(std::istream& is, GUID& guid);

		//////////////////////////////////////////////////////////////////////////

	
		//@{
		/** Type masks */
		typedef GUID ClsID;
		typedef GUID IntfID;
	
		#define SCOM_IID  Core::SCOM::GUID
		#define SCOM_RIID const Core::SCOM::GUID&
		#define SCOM_CLSID  Core::SCOM::GUID
		#define SCOM_RCLSID const Core::SCOM::GUID&
		//@}


		//////////////////////////////////////////////////////////////////////////

		//@{
		/** Useful macros */

		/// Returns the offset between classes
		#define classoffset(base, derived) ((unsigned long)(static_cast<base*>((derived*)8))-8)

		/// Safe way to pass interface and void**
		#define UUID_PPV(infc, pp) UUIDOF(infc), reinterpret_cast<void**>(static_cast<infc**>(pp)) 

		//@}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace


//////////////////////////////////////////////////////////////////////////


/// Shouldn't be instantiated
template<class I> struct _scom_uuidof { };

/// Binds a GUID to some type
#define SCOM_DECLARE_GUID(Interface, guid_str)									\
class Interface;																\
	template<> struct _scom_uuidof<Interface> {									\
	static const Core::SCOM::GUID& getGUID() {									\
	static const Core::SCOM::GUID g = Core::SCOM::_GUIDFromString(guid_str);	\
	return g; }																	\
};

/// Returns the GUID of specified interface
#define UUIDOF(intrfc) _scom_uuidof<intrfc>::getGUID()


#endif // _SCOM_GUID_H__
