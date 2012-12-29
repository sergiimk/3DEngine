/*========================================================
* InterpolatorsVec3.cpp
* @author Sergey Mikhtonyuk
* @date 16 July 2009
=========================================================*/
#include "InterpolatorsVec3.h"

namespace Time
{

	//////////////////////////////////////////////////////////////////////////
	// Linear ////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	VML::Vector3 Vec3Linear::Interpolate(float t) const
	{
		assert(IsReady());

		processTime(t);
		size_t segm = findSegment(t); 

		const SKeyframeVec3& p0 = mKeyframes[segm];
		const SKeyframeVec3& p1 = mKeyframes[segm + 1];
		float u = (t - p0.time) / (p1.time - p0.time);
		return (p1.data - p0.data) * u + p0.data;
	}

	//////////////////////////////////////////////////////////////////////////
	// Catmull-Rom ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	VML::Vector3 Vec3CatmullRom::Interpolate(float t) const
	{
		assert(IsReady());

		processTime(t);
		size_t segm = findSegment(t); 
		size_t n_ctrl = mKeyframes.size();

		const VML::Vector3& p0 = mKeyframes[segm].data;
		const VML::Vector3& p1 = mKeyframes[segm + 1].data;
		float time0 = mKeyframes[segm].time;
		float time1 = mKeyframes[segm + 1].time;

		VML::Vector3 t0(0);
		VML::Vector3 t1(0);

		if(segm > 0 && segm < n_ctrl - 2)
		{
			t0 = (p1 - mKeyframes[segm - 1].data) * 0.5f;
			t1 = (mKeyframes[segm + 2].data - p0) * 0.5f;
		}
		else if(segm == 0 && n_ctrl > 2)
		{
			t0 = (p1 + p1 - mKeyframes[segm + 2].data - p0) * 0.5f;
			t1 = (mKeyframes[segm + 2].data - p0) * 0.5f;
		}
		else if (segm == n_ctrl - 2 && n_ctrl > 2)
		{
			t0 = (p1 - mKeyframes[segm - 1].data) * 0.5f;
			t1 = - (p0 + p0 - mKeyframes[segm - 1].data - p1) * 0.5f;
		}

		float u = (t - time0) / (time1 - time0), u2 = u*u, u3 = u2*u;
		VML::Vector3 pos = p0*(2.0f*u3 - 3.0f*u2 + 1.0f) + p1*(-2.0f*u3 + 3.0f*u2) + t0*(u3 - 2.0f*u2 + u) + t1*(u3 - u2);
		return pos;
	}

	//////////////////////////////////////////////////////////////////////////
	// Cubic spline //////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	void Vec3CubicSpline::SetKeyframes(const Time::SKeyframeVec3 *frames, size_t n)
	{
		if(mTangents.size())
			mTangents.clear();

		CInterpolatorVec3Base::SetKeyframes(frames, n);
	}

	//////////////////////////////////////////////////////////////////////////

	void Vec3CubicSpline::ClearKeyframes()
	{
		CInterpolatorVec3Base::ClearKeyframes();
		mTangents.clear();
	}

	//////////////////////////////////////////////////////////////////////////

	void Vec3CubicSpline::AddKeyframe(const Time::SKeyframeVec3 &pnt)
	{
		if(mTangents.size())
			mTangents.clear();

		CInterpolatorVec3Base::AddKeyframe(pnt);
	}

	//////////////////////////////////////////////////////////////////////////

	void Vec3CubicSpline::setKeyframe(const Time::SKeyframeVec3 &pnt, size_t index)
	{
		if(mTangents.size())
			mTangents.clear();

		CInterpolatorVec3Base::setKeyframe(pnt, index);
	}

	//////////////////////////////////////////////////////////////////////////

	bool Vec3CubicSpline::IsReady() const
	{
		return mTangents.size() > 0;
	}

	//////////////////////////////////////////////////////////////////////////

	// Fills solution into x. Warning: will modify c and d
	void TridiagonalSolve(const float *a, const float *b, float *c, VML::Vector3 *d, VML::Vector3 *x, int n)
	{
		int i;

		// Modify the coefficients
		c[0] /= b[0];
		d[0] /= b[0];
		for(i = 1; i < n; i++){
			float id = (b[i] - c[i-1] * a[i]);
			c[i] /= id;
			d[i] = (d[i] - d[i-1] * a[i])/id;
		}

		// Now back substitute
		x[n - 1] = d[n - 1];
		for(i = n - 2; i >= 0; i--)
			x[i] = d[i] - c[i] * x[i + 1];
	}

	//////////////////////////////////////////////////////////////////////////

	void Vec3CubicSpline::Build()
	{
		size_t n_ctrl = mKeyframes.size();
		if(n_ctrl < 2) return;

		// Fill tridiagonal
		float *a = new float[n_ctrl];
		for(int i = 0; i != n_ctrl; ++i)
			a[i] = 1.0f;

		float *c = new float[n_ctrl];
		for(int i = 0; i != n_ctrl; ++i)
			c[i] = 1.0f;

		float *b = new float[n_ctrl];
		for(int i = 1; i != n_ctrl - 1; ++i)
			b[i] = 4.0f;
		b[0] = 2.0f;
		b[n_ctrl - 1] = 2.0f;

		VML::AlignedAllocator<VML::Vector3> alloc;
		VML::Vector3 *d = (VML::Vector3*)alloc.allocate(n_ctrl);
		
		VML::Vector3 vt;
		for(int i = 1; i != n_ctrl - 1; ++i)
		{
			vt = (mKeyframes[i + 1].data - mKeyframes[i - 1].data) * 3.0f;
			alloc.construct(&d[i], vt);
		}
		vt = (mKeyframes[1].data - mKeyframes[0].data) * 3.0f;
		alloc.construct(&d[0], vt);
		vt = (mKeyframes[n_ctrl - 1].data - mKeyframes[n_ctrl - 2].data) * 3.0f;
		alloc.construct(&d[n_ctrl - 1], vt);

		mTangents.resize(n_ctrl);
		TridiagonalSolve(a, b, c, d, &mTangents[0], n_ctrl);

		delete[] a;
		delete[] b;
		delete[] c;

		for(int i = 0; i != n_ctrl; ++i)
			alloc.destroy(&d[i]);
		alloc.deallocate(d, n_ctrl);
	}

	//////////////////////////////////////////////////////////////////////////

	VML::Vector3 Vec3CubicSpline::Interpolate(float t) const
	{
		assert(IsReady());

		processTime(t);
		size_t segm = findSegment(t); 
		size_t n_ctrl = mKeyframes.size();

		const SKeyframeVec3& p0 = mKeyframes[segm];
		const SKeyframeVec3& p1 = mKeyframes[segm + 1];
		const VML::Vector3& t0 = mTangents[segm];
		const VML::Vector3& t1 = mTangents[segm+1];

		float u = (t - p0.time) / (p1.time - p0.time), u2 = u*u, u3 = u2*u;
		VML::Vector3 pos = p0.data*(2.0f*u3 - 3.0f*u2 + 1.0f) + p1.data*(-2.0f*u3 + 3.0f*u2) + t0*(u3 - 2.0f*u2 + u) + t1*(u3 - u2);

		return pos;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace