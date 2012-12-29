/*========================================================
* ICmpAppearance.h
* @author Sergey Mikhtonyuk
* @date 15 June 2009
=========================================================*/
#ifndef _ICMPAPPEARANCE_H__
#define _ICMPAPPEARANCE_H__

#include "../Engine_fwd.h"
#include "../../Engine.Graphics/Graphics_fwd.h"
#include "IComponent.h"
#include "../Engine_classid.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////
	
	/// Built-in entity component. Defines the appearance of the entity
	/** @ingroup Engine */
	SCOM_INTERFACE(ICmpAppearance, "d0e98721-051c-4e62-aafd-0186bebd2bf0", IComponent)
	{
	public:

		/// Returns the mesh assigned to this entity
		virtual Graphics::IMesh* getMesh() const = 0;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Appearance component description, used for component instantiation
	/** @ingroup Engine */
	struct SAppearanceDesc : public SComponentDesc
	{
		Graphics::IMesh*	Mesh;	///< Appearance of the entity

		SAppearanceDesc()
			:	SComponentDesc(&CLSID_CCmpAppearance),
				Mesh(0)
		{}

		SAppearanceDesc(Graphics::IMesh* mesh)
			:	SComponentDesc(&CLSID_CCmpAppearance),
				Mesh(mesh)
		{}

		void ResetDefaults() { Mesh = 0; }
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _ICMPAPPEARANCE_H__