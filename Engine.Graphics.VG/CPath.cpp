/*========================================================
* CPath.cpp
* @author Sergey Mikhtonyuk
* @date 19 July 2009
=========================================================*/
#include "CPath.h"
#include "VGExceptions.h"
#include "FillTessellator.h"
#include "StrokeTessellator.h"
#include "../Engine.Graphics/Interfaces/IRenderer.h"

namespace VG
{
	//////////////////////////////////////////////////////////////////////////
	const float FLOAT_CMP_EPSILON = 0.001f;
	//////////////////////////////////////////////////////////////////////////

	CPath::CPath()
		: mFillMesh(0), mStrokeMesh(0), mUsageRefs(0)
	{
		ResetProperties();
	}

	//////////////////////////////////////////////////////////////////////////

	CPath::~CPath()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CPath::FinalConstruct(IRenderer* pRenderer)
	{
		mRenderer = pRenderer;
	}

	//////////////////////////////////////////////////////////////////////////

	void CPath::AddUser()
	{ 
		assert(mUsageRefs >= 0); 
		if(!mUsageRefs++)
		{
			mRenderer->GetGeometryManager()->CreateProceduralMesh(this, &mFillMesh);
			mFillMesh->AddUser();

			mRenderer->GetGeometryManager()->CreateProceduralMesh(this, &mStrokeMesh);
			mStrokeMesh->AddUser(); 
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CPath::RemoveUser()
	{
		assert(mUsageRefs >  0);
		if(!(--mUsageRefs))
		{
			mStrokeMesh->RemoveUser();
			mStrokeMesh->Release();
			mStrokeMesh = 0;

			mFillMesh->RemoveUser();
			mFillMesh->Release();
			mFillMesh = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CPath::ResetProperties()
	{
		mProperties.properties[PP_DEFAULT_JOINT]	= LJOINT_MITER;
		mProperties.properties[PP_DEFAULT_ENDING]	= LEND_BUTT;
		mProperties.properties[PP_STROKE_STYLE]		= SS_LINE_SOLID;
		mProperties.properties[PP_FILL_STYLE]		= FS_NONE;
		mProperties.properties[PP_STROKE_COLOR1]	= 0xff000000;
		mProperties.properties[PP_STROKE_COLOR2]	= 0xff000000;
		mProperties.properties[PP_FILL_COLOR1]		= 0xff000000;
		mProperties.properties[PP_FILL_COLOR2]		= 0xff000000;

		mProperties.strokeWidth = 1.0f;
		mProperties.tolerance = 1.0f;
	}

	//////////////////////////////////////////////////////////////////////////

	void CPath::FillMeshData(IMesh* pMesh)
	{
		// React once on last query
		if(pMesh == mStrokeMesh)
			RecalculatePath();
	}

	//////////////////////////////////////////////////////////////////////////

	void CPath::RecalculatePath()
	{
		if(!mPathBuffer.IsValid())
			throw VGFormatException("Commands-points number mismatch, validate path");

		{
			ApproximationUnit appunit(&mPathBuffer, mCachedAppBuf, mProperties.tolerance);
			appunit.Approximate();
		}

		mFillMesh->ClearSubsets();
		if(mProperties.properties[PP_FILL_STYLE] != FS_NONE)
		{
			mFillMesh->setPrimitiveType(PT_TRIANGLE_LIST);
			VertexBuffer fvb(mFillMesh->GetVertexBuffer());

			FillTessellator ft(&mCachedAppBuf, fvb, mProperties);
			ft.Tessellate();

			IGeometry::TInterval ii(0, 0);
			IGeometry::TInterval vi(0, fvb.size());
			mFillMesh->AddSubset(vi, ii);
			mFillMesh->SetVertexDeclaration(VGVertex::getDeclaration());
		}

		mStrokeMesh->ClearSubsets();
		if(mProperties.properties[PP_STROKE_STYLE] != SS_NONE)
		{
			mStrokeMesh->setPrimitiveType(PT_TRIANGLE_STRIP);
			VertexBuffer svb(mStrokeMesh->GetVertexBuffer());

			StrokeTessellator st(&mCachedAppBuf, svb, mProperties);
			st.Tessellate();

			IGeometry::TInterval ii(0, 0);
			IGeometry::TInterval vi(0, svb.size());
			mStrokeMesh->AddSubset(vi, ii);
			mStrokeMesh->SetVertexDeclaration(VGVertex::getDeclaration());
		}

		mCachedAppBuf.points.clear();
		mCachedAppBuf.styleStops.clear();
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace