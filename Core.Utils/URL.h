/*========================================================
* URL.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef __URL__H__
#define __URL__H__

#include <string>

namespace Utils
{
	/// Unified Resource Locator
	/** URL is used to define the location of resource either in some package or just in file
	 *  @ingroup Utils */
	struct URL
	{
		URL()
		{ }

		URL(const std::string& name)
			: Name(name)
		{ }

		/// Unique name of resource
		std::string Name;
	};

} // namespace

#endif