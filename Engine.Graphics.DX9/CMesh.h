/*========================================================
* CMesh.h
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#ifndef __CMESH_H__
#define __CMESH_H__

#include "CBaseMesh.h"
#include "../Engine.Graphics.Parsers/MeshParser/MeshParser.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Engine::Graphics;
	class CGeometry;
	//////////////////////////////////////////////////////////////////////////


	/// Concrete class of mesh
	/** @ingroup DX9 */
	class NOVTABLE CMesh : 
		public Core::SCOM::ComRootObject<>,
		public IMeshParsingCallback,
		public CBaseMesh
	{
		friend class CGeometry;

	public:
		DECLARE_IMPLEMENTATIONA(CMesh, VML::AlignedAllocator)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IMesh)
			INTERFACE_ENTRY(IGraphicsResource)
			INTERFACE_ENTRY(IResourceInternal)
		END_INTERFACE_MAP()
	
		//////////////////////////////////////////////////////////////////////////

		CMesh();
		~CMesh();
		void	FinalConstruct(const Utils::URL &url);

		//////////////////////////////////////////////////////////////////////////

		EPrimitiveType getPrimitiveType() const { return PT_INDEXED_TRIANGLE_LIST; }

		void setPrimitiveType(EPrimitiveType t) { } 
 
		void	Load();
		void	Unload();
		void	OnDeviceLost();
		void	OnDeviceReset();

		//////////////////////////////////////////////////////////////////////////

		void OnError(const char* msg);
		void OnGeometryFile(const char* file);
		void OnSubsetMaterial(int sid, const char* material);
		void OnFinished(int nsubsets);

		//////////////////////////////////////////////////////////////////////////

	};	

} // namespace

#endif