/*========================================================
* CGeometryManager.h
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#ifndef __CGEOMETRY_MANAGER_H__
#define __CGEOMETRY_MANAGER_H__

#include "../Engine.Graphics/Interfaces/IGeometryManager.h"
#include "../Core.COM/Implementations.h"
#include <hash_map>

namespace DXRenderer
{
	using namespace Engine::Graphics;

	/// Concrete geometry manager
	/** @ingroup DX9 */
	class NOVTABLE CGeometryManager : 
		public Core::SCOM::ComRootObject<>,
		public IGeometryManager
	{
	public:
		DECLARE_IMPLEMENTATION(CGeometryManager)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IGeometryManager)
			INTERFACE_ENTRY(IResourceManager)
		END_INTERFACE_MAP()
	
		CGeometryManager();
		~CGeometryManager();

		void		FindOrLoadMesh(const Utils::URL &url, IMesh** outMesh);
		void		CreatePlane(float x, float y, IMesh** outPlane);
		void		CreateBox(const VML::Vector3& a, const VML::Vector3& b, IMesh** outCube);
		void		CreateSphere(int nSegments, int nRings, float radius, IMesh** outSphere);
		void		CreateProceduralMesh(IProceduralMeshCallback* callback, IMesh** outProcMesh);

		void		CloseResourceHandle(IMesh* mesh);

		void		OnDeviceLost();
		void		OnDeviceReset();

	private:
		typedef std::hash_map<std::string, IMesh*>	MeshMap;
		typedef MeshMap::iterator					MeshMapIter;
		typedef MeshMap::const_iterator				MeshMapCIter;

		MeshMap		mMeshes;
	};	

} // namespace

#endif // __CGEOMETRY_MANAGER_H__