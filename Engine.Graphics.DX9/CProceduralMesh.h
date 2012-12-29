/*========================================================
* CProceduralMesh.h
* @author Sergey Mikhtonyuk
* @date 20 May 2009
=========================================================*/
#ifndef _CPROCEDURALMESH_H__
#define _CPROCEDURALMESH_H__

#include "CBaseMesh.h"
#include "../Engine.Graphics/Interfaces/IGeometryManager.h"
#include "../Core.COM/Intellectual.h"

namespace DXRenderer
{

	/// Procedurally-generated mesh
	/** @ingroup DX9 */
	class NOVTABLE CProceduralMesh : 
		public Core::SCOM::ComRootObject<>,
		public CBaseMesh
	{
		friend class CGeometry;

	public:
		DECLARE_IMPLEMENTATIONA(CProceduralMesh, VML::AlignedAllocator)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IMesh)
			INTERFACE_ENTRY(IGraphicsResource)
			INTERFACE_ENTRY(IResourceInternal)
		END_INTERFACE_MAP()

		//////////////////////////////////////////////////////////////////////////

		CProceduralMesh();
		~CProceduralMesh();
		void	FinalConstruct(IProceduralMeshCallback* callback);

		//////////////////////////////////////////////////////////////////////////

		EPrimitiveType getPrimitiveType() const { return mPrimType; }
		void	setPrimitiveType(EPrimitiveType t) { mPrimType = t; }
		void	Load();
		void	Unload();
		void	OnDeviceLost();
		void	OnDeviceReset();

		//////////////////////////////////////////////////////////////////////////

	private:
		Core::SCOM::ComPtr<IProceduralMeshCallback> mProcCallback;
		EPrimitiveType mPrimType;
	};

} // namespace

#endif	// _CPROCEDURALMESH_H__