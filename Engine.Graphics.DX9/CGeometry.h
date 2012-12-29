/*========================================================
* CGeometry.h
* @author Sergey Mikhtonyuk
* @date 09 May 2009
=========================================================*/
#ifndef _CGEOMETRY_H__
#define _CGEOMETRY_H__

#include "../Engine.Graphics/Interfaces/IGeometry.h"
#include "../Core.COM/Implementations.h"
#include "../Core.COM/Intellectual.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Engine::Graphics;
	class CBaseMesh;
	class CTextureSet;
	//////////////////////////////////////////////////////////////////////////

	/// Implementation of IGeometry interface
	/** @ingroup DX9 */
	class NOVTABLE CGeometry : 
		public Core::SCOM::ComRootObject<>,
		public IGeometry
	{
		friend class CBaseMesh;
		friend class CMesh;
		friend class CProceduralMesh;
	public:
		DECLARE_IMPLEMENTATION(CGeometry)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IGeometry)
		END_INTERFACE_MAP()

		CGeometry();
		~CGeometry();

		void				FinishInit();

		IMesh*				GetMesh() const;
		IMaterial*			GetMaterial() const;
		void				SetMaterial(IMaterial* mat);

		const TInterval&	GetIndexInterval() const;
		const TInterval&	GetVertexInterval() const;

	private:
		CBaseMesh*						mMesh;
		Core::SCOM::ComPtr<IMaterial>	mMaterial;
		TInterval						mIndexInterval;
		TInterval						mVertexInterval;
		bool							mIsInitialized;
	};

} // namespace

#endif	// _CGEOMETRY_H__