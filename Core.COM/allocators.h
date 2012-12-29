/*========================================================
* allocators.h
* @author Sergey Mikhtonyuk
* @date 20 May 2009
=========================================================*/
#ifndef _ALLOCATORS_H__
#define _ALLOCATORS_H__

#include "../Core.Utils/EnvironmentDefs.h"

namespace Core
{
	namespace SCOM
	{
		//////////////////////////////////////////////////////////////////////////

		/// Default new allocator used by SCOM factories
		/** @ingroup SCOM */
		template<typename T>
		class NewAllocator
		{
		public:

			//////////////////////////////////////////////////////////////////////////

			typedef T*			pointer;
			typedef const T*	const_pointer;
			typedef T&			reference;
			typedef const T&	const_reference;
			typedef T			value_type;
			typedef size_t		size_type;
			typedef ptrdiff_t	difference_type;

			//////////////////////////////////////////////////////////////////////////

			template<typename U> struct rebind 
			{
				typedef NewAllocator<U> other;
			};

			//////////////////////////////////////////////////////////////////////////

			NewAllocator() throw() {}

			NewAllocator( const NewAllocator& ) throw() {}

			template<typename U> 
			NewAllocator(const NewAllocator<U>&) throw() {}

			//////////////////////////////////////////////////////////////////////////

			pointer			address(reference x)		const {return &x;}

			const_pointer	address(const_reference x)	const {return &x;}

			//////////////////////////////////////////////////////////////////////////

			/// Allocates memory for n objects
			pointer allocate( size_type n ) 
			{
				return (pointer)::operator new( n * sizeof( value_type ) );
			}


#if defined (COMPILER_MSC)
			/// Required by some Microsoft's STL containers
			char* _Charalloc( size_type size )
			{
				return (char*)::operator new( size );
			}
#endif


			/// Free memory
			void deallocate( pointer p, size_type ) 
			{
				::operator delete( (void*)p );
			}

			/// Largest value for which method allocate might succeed
			size_type max_size() const throw() 
			{
				return return size_t(-1) / sizeof(value_type);
			}

			/// Copy-construct value placed at p.
			void construct( pointer p, const T& value )
			{
				// Placement new
				new ( static_cast<void*>( p ) ) value_type(value);
			}

			/// Calls destructor of object pointed by p
			void destroy( pointer p ) 
			{
				p->~T();
			}
		};

		//////////////////////////////////////////////////////////////////////////

		/// Void specialization (see ISO C++ Standard section 20.4.1)
		/** @ingroup SCOM */
		template<> 
		class NewAllocator<void> 
		{
		public:
			typedef void*		pointer;
			typedef const void*	const_pointer;
			typedef void		value_type;

			template<typename U>
			struct rebind 
			{
				typedef NewAllocator<U> other;
			};
		};

		//////////////////////////////////////////////////////////////////////////

		template<typename T, typename U>
		inline bool operator==( const NewAllocator<T>&, const NewAllocator<U>& )
		{
			return true;
		}

		template<typename T, typename U>
		inline bool operator!=( const NewAllocator<T>&, const NewAllocator<U>& ) 
		{
			return false;
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif	// _ALLOCATORS_H__