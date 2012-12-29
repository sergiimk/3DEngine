/*========================================================
* CPath.h
* @author Sergey Mikhtonyuk
* @date 19 July 2009
=========================================================*/
#ifndef _CPATH_H__
#define _CPATH_H__

#include "IPath.h"
#include "CPathBuffer.h"
#include "ApproximationUnit.h"
#include "../Engine.Graphics/Interfaces/IMesh.h"
#include "../Engine.Graphics/Interfaces/IGeometryManager.h"
#include "../Engine.Graphics/Graphics_fwd.h"
#include "../Core.COM/Implementations.h"

namespace VG
{
	using namespace Engine::Graphics;

	/// Implementation of IPath interface
	/** @ingroup VG */
	class NOVTABLE CPath : 
		public Core::SCOM::ComRootObject<>,
		public IPath,
		public IProceduralMeshCallback
	{
	public:
		
		DECLARE_IMPLEMENTATION(CPath)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IPath)
			INTERFACE_ENTRY(IProceduralMeshCallback)
		END_INTERFACE_MAP()

		CPath();

		~CPath();

		void FinalConstruct(IRenderer* pRenderer);

		IPathBuffer* getPathBuffer() const { return (IPathBuffer*)&mPathBuffer; }

		void RecalculatePath();

		IMesh* getFillMesh() { return mFillMesh; }

		IMesh* getStrokeMesh() { return mStrokeMesh; }

		unsigned int getProperty(PathProperty p) const { return mProperties.properties[p]; }

		void setProperty(PathProperty p, unsigned int val) { mProperties.properties[p] = val; }

		void ResetProperties();

		float getStrokeWidth() const { return mProperties.strokeWidth; }

		void setStrokeWidth(float w) { mProperties.strokeWidth = w; }

		float getTolerance() const { return mProperties.tolerance; }

		void setTolerance(float t) { mProperties.tolerance = t; }


		void FillMeshData(IMesh* pMesh);

		void AddUser();
		void RemoveUser();

	private:
		IRenderer*			mRenderer;
		IMesh*				mFillMesh;
		IMesh*				mStrokeMesh;
		CPathBuffer			mPathBuffer;
		ApproximationBuffer mCachedAppBuf;
		PathProperties		mProperties;

		int					mUsageRefs;
	};

} // namespace

#endif // _CPATH_H__