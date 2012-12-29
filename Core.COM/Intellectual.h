/*========================================================
* Intellectual.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
=========================================================*/
#ifndef _INTELLECTUAL_H__
#define _INTELLECTUAL_H__

#include <cassert>

namespace Core
{
	namespace SCOM
	{

		//////////////////////////////////////////////////////////////////////////

		/// This tricky class protects you from calling AddRef/Release on pointer wrapped by ComPtr
		/** @ingroup SCOM */
		template <class T>
		class NoRefCountPtr : public T
		{
		private:
			virtual unsigned long AddRef() = 0;
			virtual unsigned long Release() = 0;
		};

		//////////////////////////////////////////////////////////////////////////

		static inline IUnknown* _ComPtrAssign(IUnknown** pp, IUnknown* lp)
		{
			if (lp != 0) lp->AddRef();
			if (*pp) (*pp)->Release();
			*pp = lp;
			return lp;
		}

		static inline IUnknown* _ComQIPtrAssign(IUnknown** pp, IUnknown* lp, SCOM_RIID riid)
		{
			IUnknown* pTemp = *pp;
			*pp = 0;
			if (lp != 0) lp->QueryInterface(riid, (void**)pp);
			if (pTemp) pTemp->Release();

			return *pp;
		}


		//////////////////////////////////////////////////////////////////////////




		/// Base class for intellectual Com pointers
		/** @ingroup SCOM */
		template <class T>
		class ComPtr
		{
		//////////////////////////////////////////////////////////////////////////
		// Members
		//////////////////////////////////////////////////////////////////////////

		private:
			/// Wrapped pointer
			T* p;

		public:
			typedef T					interface_type;
			typedef T*					pointer_type;
			typedef NoRefCountPtr<T>*	safe_pointer_type;

		//////////////////////////////////////////////////////////////////////////
		// Ctors / Destructors
		//////////////////////////////////////////////////////////////////////////
		public:
			/// Empty ctor
			ComPtr() : p(0) { }

			/// Construct around pointer
			ComPtr(T* lp) : p(lp) { if (p != 0) p->AddRef(); }

			/// Copy ctor
			ComPtr(const ComPtr<T>& other) : p(other.p) { if (p != 0) p->AddRef(); }

			/// Cast ctor
			ComPtr(IUnknown* pUnk) : p(0) { if (pUnk != 0) pUnk->QueryInterface(UUIDOF(T), (void **)&p); }

			/// Destructor
			~ComPtr() { if (p) p->Release(); }

		//////////////////////////////////////////////////////////////////////////
		// Operators
		//////////////////////////////////////////////////////////////////////////
		public:

			/// To pointer conversion
			operator T*() const { return p; }

			/// Dereferencing
			T& operator*() const { assert(p!=0); return *p; }

			/// Pointer to pointer
			T** wrapped() { assert(p==0); return &p; }

			/// 
			safe_pointer_type operator->() const { assert(p!=0); return (safe_pointer_type)p; }

			/// Negation
			bool operator!() const { return (p == 0); }

			/// Less operator
			bool operator<(T* pT) const { return p < pT; }

			/// Equality
			bool operator==(T* pT) const { return p == pT; }

			/// Not equality
			bool operator!=(T* pT) const { return !operator==(pT); }

			/// Assigning pointer
			T* operator = (T* lp)
			{
				if(*this != lp)
					return static_cast<T*>(_ComPtrAssign((IUnknown**)&p, lp));
				return *this;
			}

			/// Assigning intellectual pointer 
			T* operator = (const ComPtr<T>& lp)
			{
				if(*this != lp)
					return static_cast<T*>(_ComPtrAssign((IUnknown**)&p, lp));
				return *this;
			}

			/// Assigning pointer with type casting
			T* operator = (IUnknown* lp)
			{
				if(*this != lp)
					return static_cast<T*>(_ComQIPtrAssign((IUnknown**)&p, lp, UUIDOF(T)));
				return *this;
			}

			/// Assigning intellectual pointer with interface querying
			template <typename Q>
			T* operator = (const ComPtr<Q>& lp)
			{
				if(!Equal(lp))
					return static_cast<T*>(_ComQIPtrAssign((IUnknown**)&p, lp, UUIDOF(T)));
				return *this;
			}

		//////////////////////////////////////////////////////////////////////////
		// Methods
		//////////////////////////////////////////////////////////////////////////
		public:

			/// Releases the interface and sets ptr to 0
			void Release()
			{
				T* pTemp = p;
				if (pTemp) {
					p = 0;
					pTemp->Release();
				}
			}

			/// Compares two objects
			bool Equal(IUnknown* pObj)
			{
				if (p == 0 && pObj == 0)
					return true;

				if (p == 0 || pObj == 0)
					return false;

				ComPtr<IUnknown> punk1;
				ComPtr<IUnknown> punk2;
				p->QueryInterface(UUID_PPV(IUnknown, punk1.wrapped()));
				pObj->QueryInterface(UUID_PPV(IUnknown, punk2.wrapped()));
				return punk1 == punk2;
			}

			/// Attach to an existing interface (doesn't call AddRef)
			void Attach(T* p2) { if (p) p->Release(); p = p2; }

			/// Detach the interface (doesn't call Release)
			T* Detach() { T* pt = p; p = 0; return pt; }
		};




		//////////////////////////////////////////////////////////////////////////





		/// ComPtr specialization for IUnknown
		/** @ingroup SCOM */
		template<>
		class ComPtr<IUnknown>
		{
			//////////////////////////////////////////////////////////////////////////
			// Members
			//////////////////////////////////////////////////////////////////////////

		private:
			/// Wrapped pointer
			IUnknown* p;

		public:
			typedef IUnknown					interface_type;
			typedef IUnknown*					pointer_type;
			typedef NoRefCountPtr<IUnknown>*	safe_pointer_type;

			//////////////////////////////////////////////////////////////////////////
			// Ctors / Destructors
			//////////////////////////////////////////////////////////////////////////
		public:
			/// Empty ctor
			ComPtr() : p(0) { }

			/// Construct around pointer
			ComPtr(IUnknown* lp) : p(lp) { if (p != 0) p->AddRef(); }

			/// Copy ctor
			ComPtr(const ComPtr<IUnknown>& other) : p(other.p) { if (p != 0) p->AddRef(); }

			/// Destructor
			~ComPtr() { if (p) p->Release(); }

			//////////////////////////////////////////////////////////////////////////
			// Operators
			//////////////////////////////////////////////////////////////////////////
		public:

			/// To pointer conversion
			operator IUnknown*() const { return p; }

			/// Dereferencing
			IUnknown& operator*() const { assert(p!=0); return *p; }

			/// Pointer to pointer
			IUnknown** wrapped() { assert(p==0); return &p; }

			/// 
			safe_pointer_type operator->() const { assert(p!=0); return (safe_pointer_type)p; }

			/// Negation
			bool operator!() const { return (p == 0); }

			/// Less operator
			bool operator<(IUnknown* pT) const { return p < pT; }

			/// Equality
			bool operator==(IUnknown* pT) const { return p == pT; }

			/// Not equality
			bool operator!=(IUnknown* pT) const { return !operator==(pT); }

			/// Assigning intellectual pointer 
			IUnknown* operator = (const ComPtr<IUnknown>& lp)
			{
				if(*this != lp)
					return _ComPtrAssign(&p, lp);
				return *this;
			}

			/// Assigning pointer with type casting
			IUnknown* operator = (IUnknown* lp)
			{
				if(*this != lp)
					return _ComQIPtrAssign(&p, lp, UUIDOF(IUnknown));
				return *this;
			}

			/// Assigning intellectual pointer with interface querying
			template <typename Q>
			IUnknown* operator = (const ComPtr<Q>& lp)
			{
				if(!Equal(lp))
					return _ComQIPtrAssign(&p, lp, UUIDOF(IUnknown));
				return *this;
			}

			//////////////////////////////////////////////////////////////////////////
			// Methods
			//////////////////////////////////////////////////////////////////////////
		public:

			/// Releases the interface and sets ptr to 0
			void Release()
			{
				IUnknown* pTemp = p;
				if (pTemp) {
					p = 0;
					pTemp->Release();
				}
			}

			/// Compares two objects
			bool Equal(IUnknown* pObj)
			{
				return p == pObj;
			}

			/// Attach to an existing interface (doesn't call AddRef)
			void Attach(IUnknown* p2) { if (p) p->Release(); p = p2; }

			/// Detach the interface (doesn't call Release)
			IUnknown* Detach() { IUnknown* pt = p; p = 0; return pt; }
		};


	} // namespace
} // namespace


/// Specialization to ease the use with ComPtr
/** @ingroup SCOM */
template<class Impl, class Itf>
Core::SCOM::HResult scom_new(Core::SCOM::ComPtr<Itf>& ptr)
{
	return Impl::_ObjectClass::_CreateInstance(UUID_PPV(Itf, ptr.wrapped()));
}


#endif // _INTELLECTUAL_H__
