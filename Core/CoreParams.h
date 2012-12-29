/*========================================================
* CoreParams.h
* @author Sergey Mikhtonyuk
* @date 21 May 2009
=========================================================*/
#ifndef _COREPARAMS_H__
#define _COREPARAMS_H__

#include <string>
#include <set>

namespace Core
{
	/// Holds core parameters
	/** @ingroup Core */
	class CoreParams
	{
	public:

		/// Checks if this plugin should be loaded
		bool ShouldLoad(const std::string& plugin) const;

		/// Parses settings file
		bool ParseFile(const char* file);

	private:
		std::set<std::string> mLoadOnlyPlugins;
	};

} // namespace

#endif	// _COREPARAMS_H__