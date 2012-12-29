/*========================================================
* IfThenElse.h
* @author Sergey Mikhtonyuk
* @date 05 April 2009
=========================================================*/
#ifndef _IFTHENELSE_H__
#define _IFTHENELSE_H__

namespace Utils
{
	/// IfThenElse template for compile-time choice between types
	/** @ingroup Utils */
	template<bool COND, class T, class F>
	struct IfThenElse { typedef void value; };

	/// IfThenElseInt template for compile-time choice between integral values
	/** @ingroup Utils */
	template<bool COND, int T, int F>
	struct IfThenElseInt { static const int value = -1; };

	//////////////////////////////////////////////////////////////////////////

	template<class T, class F>
	struct IfThenElse<true, T, F> { typedef T value; };

	template<class T, class F>
	struct IfThenElse<false, T, F> { typedef F value; };

	//////////////////////////////////////////////////////////////////////////

	template<int T, int F>
	struct IfThenElseInt<true, T, F> { static const int value = T; };

	template<int T, int F>
	struct IfThenElseInt<false, T, F> { static const int value = F; };	

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _IFTHENELSE_H__