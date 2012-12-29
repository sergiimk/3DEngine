/*
   Copyright (C) 2006, 2007 Sony Computer Entertainment Inc.
   All rights reserved.

   Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Sony Computer Entertainment Inc nor the names
      of its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _VECTORMATH_VEC_AOS_CPP_H
#define _VECTORMATH_VEC_AOS_CPP_H

//-----------------------------------------------------------------------------
// Constants
// for permutes words are labeled [x,y,z,w] [a,b,c,d]

#define _VECTORMATH_PERM_X 0x00010203
#define _VECTORMATH_PERM_Y 0x04050607
#define _VECTORMATH_PERM_Z 0x08090a0b
#define _VECTORMATH_PERM_W 0x0c0d0e0f
#define _VECTORMATH_PERM_A 0x10111213
#define _VECTORMATH_PERM_B 0x14151617
#define _VECTORMATH_PERM_C 0x18191a1b
#define _VECTORMATH_PERM_D 0x1c1d1e1f
#define _VECTORMATH_PERM_XYZA (vec_uchar16)(vec_uint4){ _VECTORMATH_PERM_X, _VECTORMATH_PERM_Y, _VECTORMATH_PERM_Z, _VECTORMATH_PERM_A }
#define _VECTORMATH_PERM_ZXYW (vec_uchar16)(vec_uint4){ _VECTORMATH_PERM_Z, _VECTORMATH_PERM_X, _VECTORMATH_PERM_Y, _VECTORMATH_PERM_W }
#define _VECTORMATH_PERM_YZXW (vec_uchar16)(vec_uint4){ _VECTORMATH_PERM_Y, _VECTORMATH_PERM_Z, _VECTORMATH_PERM_X, _VECTORMATH_PERM_W }
#define _VECTORMATH_PERM_YZAB (vec_uchar16)(vec_uint4){ _VECTORMATH_PERM_Y, _VECTORMATH_PERM_Z, _VECTORMATH_PERM_A, _VECTORMATH_PERM_B }
#define _VECTORMATH_PERM_ZABC (vec_uchar16)(vec_uint4){ _VECTORMATH_PERM_Z, _VECTORMATH_PERM_A, _VECTORMATH_PERM_B, _VECTORMATH_PERM_C }
#define _VECTORMATH_PERM_XYAW (vec_uchar16)(vec_uint4){ _VECTORMATH_PERM_X, _VECTORMATH_PERM_Y, _VECTORMATH_PERM_A, _VECTORMATH_PERM_W }
#define _VECTORMATH_PERM_XAZW (vec_uchar16)(vec_uint4){ _VECTORMATH_PERM_X, _VECTORMATH_PERM_A, _VECTORMATH_PERM_Z, _VECTORMATH_PERM_W }
#define _VECTORMATH_MASK_0xF000 (vec_uint4){ 0xffffffff, 0, 0, 0 }
#define _VECTORMATH_MASK_0x0F00 (vec_uint4){ 0, 0xffffffff, 0, 0 }
#define _VECTORMATH_MASK_0x00F0 (vec_uint4){ 0, 0, 0xffffffff, 0 }
#define _VECTORMATH_MASK_0x000F (vec_uint4){ 0, 0, 0, 0xffffffff }
#define _VECTORMATH_UNIT_1000 _mm_setr_ps(1.0f,0.0f,0.0f,0.0f) // (__m128){ 1.0f, 0.0f, 0.0f, 0.0f }
#define _VECTORMATH_UNIT_0100 _mm_setr_ps(0.0f,1.0f,0.0f,0.0f) // (__m128){ 0.0f, 1.0f, 0.0f, 0.0f }
#define _VECTORMATH_UNIT_0010 _mm_setr_ps(0.0f,0.0f,1.0f,0.0f) // (__m128){ 0.0f, 0.0f, 1.0f, 0.0f }
#define _VECTORMATH_UNIT_0001 _mm_setr_ps(0.0f,0.0f,0.0f,1.0f) // (__m128){ 0.0f, 0.0f, 0.0f, 1.0f }
#define _VECTORMATH_SLERP_TOL 0.999f

//-----------------------------------------------------------------------------
// Definitions

#ifndef _VECTORMATH_INTERNAL_FUNCTIONS
#define _VECTORMATH_INTERNAL_FUNCTIONS

static inline __m128 _vmathVfDot3( const __m128& vec0, const __m128& vec1 )
{
    __m128 result = _mm_mul_ps( vec0, vec1);
    return _mm_add_ps( vec_splat( result, 0 ), _mm_add_ps( vec_splat( result, 1 ), vec_splat( result, 2 ) ) );
}

static inline __m128 _vmathVfDot4( const __m128& vec0, const __m128& vec1 )
{
    __m128 result = _mm_mul_ps(vec0, vec1);
	return _mm_add_ps(_mm_shuffle_ps(result, result, _MM_SHUFFLE(0,0,0,0)),
			_mm_add_ps(_mm_shuffle_ps(result, result, _MM_SHUFFLE(1,1,1,1)),
			_mm_add_ps(_mm_shuffle_ps(result, result, _MM_SHUFFLE(2,2,2,2)), _mm_shuffle_ps(result, result, _MM_SHUFFLE(3,3,3,3)))));
}

static inline __m128 _vmathVfCross( const __m128& vec0, const __m128& vec1 )
{
    __m128 tmp0, tmp1, tmp2, tmp3, result;
    tmp0 = _mm_shuffle_ps( vec0, vec0, _MM_SHUFFLE(3,0,2,1) );
    tmp1 = _mm_shuffle_ps( vec1, vec1, _MM_SHUFFLE(3,1,0,2) );
    tmp2 = _mm_shuffle_ps( vec0, vec0, _MM_SHUFFLE(3,1,0,2) );
    tmp3 = _mm_shuffle_ps( vec1, vec1, _MM_SHUFFLE(3,0,2,1) );
    result = vec_mul( tmp0, tmp1 );
    result = vec_nmsub( tmp2, tmp3, result );
    return result;
}
/*
static inline vec_uint4 _vmathVfToHalfFloatsUnpacked(const __m128& v)
{
#if 0
    vec_int4 bexp;
    vec_uint4 mant, sign, hfloat;
    vec_uint4 notZero, isInf;
    const vec_uint4 hfloatInf = (vec_uint4)(0x00007c00u);
    const vec_uint4 mergeMant = (vec_uint4)(0x000003ffu);
    const vec_uint4 mergeSign = (vec_uint4)(0x00008000u);

    sign = vec_sr((vec_uint4)v, (vec_uint4)16);
    mant = vec_sr((vec_uint4)v, (vec_uint4)13);
    bexp = vec_and(vec_sr((vec_int4)v, (vec_uint4)23), (vec_int4)0xff);

    notZero = (vec_uint4)vec_cmpgt(bexp, (vec_int4)112);
    isInf = (vec_uint4)vec_cmpgt(bexp, (vec_int4)142);

    bexp = _mm_add_ps(bexp, (vec_int4)-112);
    bexp = vec_sl(bexp, (vec_uint4)10);

    hfloat = vec_sel((vec_uint4)bexp, mant, mergeMant);
    hfloat = vec_sel((vec_uint4)(0), hfloat, notZero);
    hfloat = vec_sel(hfloat, hfloatInf, isInf);
    hfloat = vec_sel(hfloat, sign, mergeSign);

    return hfloat;
#else
	assert(0);
	return _mm_setzero_ps();
#endif
}

static inline vec_ushort8 _vmath2VfToHalfFloats(const __m128& u, const __m128& v)
{
#if 0
    vec_uint4 hfloat_u, hfloat_v;
    const vec_uchar16 pack = (vec_uchar16){2,3,6,7,10,11,14,15,18,19,22,23,26,27,30,31};
    hfloat_u = _vmathVfToHalfFloatsUnpacked(u);
    hfloat_v = _vmathVfToHalfFloatsUnpacked(v);
    return (vec_ushort8)vec_perm(hfloat_u, hfloat_v, pack);
#else
	assert(0);
	return _mm_setzero_si128();
#endif
}
*/

static inline __m128 _vmathVfInsert(const __m128& dst, const __m128& src, int slot)
{
	SSEFloat s;
	s.m128 = src;
	SSEFloat d;
	d.m128 = dst;
	d.f[slot] = s.f[slot];
	return d.m128;
}

#define _vmathVfSetElement(vec, scalar, slot) ((float *)&(vec))[slot] = scalar

static inline __m128 _vmathVfSplatScalar(float scalar)
{
	return _mm_set1_ps(scalar);
}

#endif

namespace VML {

#ifdef _VECTORMATH_NO_SCALAR_CAST
inline VecIdx::operator floatInVec() const
{
    return floatInVec(ref, i);
}

inline float VecIdx::getAsFloat() const
#else
inline VecIdx::operator float() const
#endif
{
    return ((float *)&ref)[i];
}

inline float VecIdx::operator =( float scalar )
{
    _vmathVfSetElement(ref, scalar, i);
    return scalar;
}

inline floatInVec VecIdx::operator =( const floatInVec &scalar )
{
    ref = _vmathVfInsert(ref, scalar.get128(), i);
    return scalar;
}

inline floatInVec VecIdx::operator =( const VecIdx& scalar )
{
    return *this = floatInVec(scalar.ref, scalar.i);
}

inline floatInVec VecIdx::operator *=( float scalar )
{
    return *this *= floatInVec(scalar);
}

inline floatInVec VecIdx::operator *=( const floatInVec &scalar )
{
    return *this = floatInVec(ref, i) * scalar;
}

inline floatInVec VecIdx::operator /=( float scalar )
{
    return *this /= floatInVec(scalar);
}

inline floatInVec VecIdx::operator /=( const floatInVec &scalar )
{
    return *this = floatInVec(ref, i) / scalar;
}

inline floatInVec VecIdx::operator +=( float scalar )
{
    return *this += floatInVec(scalar);
}

inline floatInVec VecIdx::operator +=( const floatInVec &scalar )
{
    return *this = floatInVec(ref, i) + scalar;
}

inline floatInVec VecIdx::operator -=( float scalar )
{
    return *this -= floatInVec(scalar);
}

inline floatInVec VecIdx::operator -=( const floatInVec &scalar )
{
    return *this = floatInVec(ref, i) - scalar;
}

#ifdef _DEBUG  // Debug versions check alignment before initialization

inline Vector3::Vector3( float _x, float _y, float _z )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_setr_ps(_x, _y, _z, 0.0f);
}

inline Vector3::Vector3( const floatInVec &_x, const floatInVec &_y, const floatInVec &_z )
{
	_CHECK_ALIGN(mVec128, 16);
	__m128 xz = _mm_unpacklo_ps( _x.get128(), _z.get128() );
	mVec128 = _mm_unpacklo_ps( xz, _y.get128() );
}

inline Vector3::Vector3( const Point3 &pnt )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = pnt.get128();
}

inline Vector3::Vector3( float scalar )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_set1_ps(scalar);
}

inline Vector3::Vector3( _t_min )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_set1_ps((std::numeric_limits<float>::min)());
}

inline Vector3::Vector3( _t_max )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_set1_ps((std::numeric_limits<float>::max)());
}

inline Vector3::Vector3( const floatInVec &scalar )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = scalar.get128();
}

inline Vector3::Vector3( const __m128& vf4 )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = vf4;
}

#else

inline Vector3::Vector3( float _x, float _y, float _z ) : mVec128( _mm_setr_ps(_x, _y, _z, 0.0f) ) { }

inline Vector3::Vector3( const floatInVec &_x, const floatInVec &_y, const floatInVec &_z )
{
	__m128 xz = _mm_unpacklo_ps( _x.get128(), _z.get128() );
	mVec128 = _mm_unpacklo_ps( xz, _y.get128() );
}

inline Vector3::Vector3( const Point3 &pnt ) :  mVec128( pnt.get128() ) { }

inline Vector3::Vector3( float scalar ) : mVec128(_mm_set1_ps(scalar)) { }

inline Vector3::Vector3( _t_min ) : mVec128(_mm_set1_ps((std::numeric_limits<float>::min)())) { }

inline Vector3::Vector3( _t_max ) : mVec128(_mm_set1_ps((std::numeric_limits<float>::max)())) { }

inline Vector3::Vector3( const floatInVec &scalar ) : mVec128( scalar.get128() ) { }

inline Vector3::Vector3( const __m128& vf4 ) : mVec128(vf4) { }

#endif

inline const Vector3 Vector3::xAxis( )
{
    return Vector3( _VECTORMATH_UNIT_1000 );
}

inline const Vector3 Vector3::yAxis( )
{
    return Vector3( _VECTORMATH_UNIT_0100 );
}

inline const Vector3 Vector3::zAxis( )
{
    return Vector3( _VECTORMATH_UNIT_0010 );
}

inline const Vector3 lerp( float t, const Vector3 &vec0, const Vector3 &vec1 )
{
    return lerp( floatInVec(t), vec0, vec1 );
}

inline const Vector3 lerp( const floatInVec &t, const Vector3 &vec0, const Vector3 &vec1 )
{
    return ( vec0 + ( ( vec1 - vec0 ) * t ) );
}

inline const Vector3 slerp( float t, const Vector3 &unitVec0, const Vector3 &unitVec1 )
{
    return slerp( floatInVec(t), unitVec0, unitVec1 );
}

inline const Vector3 slerp( const floatInVec &t, const Vector3 &unitVec0, const Vector3 &unitVec1 )
{
    __m128 scales, scale0, scale1, cosAngle, angle, tttt, oneMinusT, angles, sines;
    cosAngle = _vmathVfDot3( unitVec0.get128(), unitVec1.get128() );
    __m128 selectMask = _mm_cmpgt_ps( _mm_set1_ps(_VECTORMATH_SLERP_TOL), cosAngle );
    angle = acosf4( cosAngle );
    tttt = t.get128();
    oneMinusT = _mm_sub_ps( _mm_set1_ps(1.0f), tttt );
    angles = _mm_unpacklo_ps( _mm_set1_ps(1.0f), tttt ); // angles = 1, t, 1, t
    angles = _mm_unpacklo_ps( angles, oneMinusT );		// angles = 1, 1-t, t, 1-t
    angles = _mm_mul_ps( angles, angle );
    sines = sinf4( angles );
    scales = _mm_div_ps( sines, vec_splat( sines, 0 ) );
    scale0 = vec_sel( oneMinusT, vec_splat( scales, 1 ), selectMask );
    scale1 = vec_sel( tttt, vec_splat( scales, 2 ), selectMask );
    return Vector3( vec_madd( unitVec0.get128(), scale0, _mm_mul_ps( unitVec1.get128(), scale1 ) ) );
}

inline const __m128& Vector3::get128( ) const
{
    return mVec128;
}

inline void storeXYZ( const Vector3 &vec, __m128 * quad )
{
    __m128 dstVec = *quad;
	__declspec(align(16)) unsigned int sw[4] = {0, 0, 0, 0xffffffff}; // TODO: Centralize
    dstVec = vec_sel(vec.get128(), dstVec, sw);
    *quad = dstVec;
}

inline void loadXYZArray( Vector3 & vec0, Vector3 & vec1, Vector3 & vec2, Vector3 & vec3, const __m128 * threeQuads )
{
	const float *quads = (float *)threeQuads;
    vec0 = Vector3(  _mm_load_ps(quads) );
    vec1 = Vector3( _mm_loadu_ps(quads + 3) );
    vec2 = Vector3( _mm_loadu_ps(quads + 6) );
    vec3 = Vector3( _mm_loadu_ps(quads + 9) );
}

inline void storeXYZArray( const Vector3 &vec0, const Vector3 &vec1, const Vector3 &vec2, const Vector3 &vec3, __m128 * threeQuads )
{
	__m128 xxxx = _mm_shuffle_ps( vec1.get128(), vec1.get128(), _MM_SHUFFLE(0, 0, 0, 0) );
	__m128 zzzz = _mm_shuffle_ps( vec2.get128(), vec2.get128(), _MM_SHUFFLE(2, 2, 2, 2) );
	__declspec(align(16)) unsigned int xsw[4] = {0, 0, 0, 0xffffffff};
	__declspec(align(16)) unsigned int zsw[4] = {0xffffffff, 0, 0, 0};
	threeQuads[0] = vec_sel( vec0.get128(), xxxx, xsw );
    threeQuads[1] = _mm_shuffle_ps( vec1.get128(), vec2.get128(), _MM_SHUFFLE(1, 0, 2, 1) );
    threeQuads[2] = vec_sel( _mm_shuffle_ps( vec3.get128(), vec3.get128(), _MM_SHUFFLE(2, 1, 0, 3) ), zzzz, zsw );
}
/*
inline void storeHalfFloats( const Vector3 &vec0, const Vector3 &vec1, const Vector3 &vec2, const Vector3 &vec3, const Vector3 &vec4, const Vector3 &vec5, const Vector3 &vec6, const Vector3 &vec7, vec_ushort8 * threeQuads )
{
	assert(0);
#if 0
    __m128 xyz0[3];
    __m128 xyz1[3];
    storeXYZArray( vec0, vec1, vec2, vec3, xyz0 );
    storeXYZArray( vec4, vec5, vec6, vec7, xyz1 );
    threeQuads[0] = _vmath2VfToHalfFloats(xyz0[0], xyz0[1]);
    threeQuads[1] = _vmath2VfToHalfFloats(xyz0[2], xyz1[0]);
    threeQuads[2] = _vmath2VfToHalfFloats(xyz1[1], xyz1[2]);
#endif
}
*/
inline Vector3 & Vector3::operator =( const Vector3 &vec )
{
    mVec128 = vec.mVec128;
    return *this;
}

inline void Vector3::setX( float _x )
{
    _vmathVfSetElement(mVec128, _x, 0);
}

inline void Vector3::setX( const floatInVec &_x )
{
    mVec128 = _vmathVfInsert(mVec128, _x.get128(), 0);
}

inline const floatInVec Vector3::getX( ) const { return floatInVec( mVec128, 0 ); }

inline float Vector3::getXf( ) const { return getX(); }

inline void Vector3::setY( float _y ) { _vmathVfSetElement(mVec128, _y, 1); }

inline void Vector3::setY( const floatInVec &_y ) { mVec128 = _vmathVfInsert(mVec128, _y.get128(), 1); }

inline const floatInVec Vector3::getY( ) const { return floatInVec( mVec128, 1 ); }

inline float Vector3::getYf( ) const { return getY(); }

inline void Vector3::setZ( float _z ) { _vmathVfSetElement(mVec128, _z, 2); }

inline void Vector3::setZ( const floatInVec &_z ) { mVec128 = _vmathVfInsert(mVec128, _z.get128(), 2); }

inline const floatInVec Vector3::getZ( ) const { return floatInVec( mVec128, 2 ); }

inline float Vector3::getZf( ) const { return getZ(); }

inline void Vector3::setElem( int idx, float value ) { _vmathVfSetElement(mVec128, value, idx); }

inline void Vector3::setElem( int idx, const floatInVec &value ) { mVec128 = _vmathVfInsert(mVec128, value.get128(), idx); }

inline const floatInVec Vector3::getElem( int idx ) const { return floatInVec( mVec128, idx ); }

inline VecIdx Vector3::operator []( int idx )
{
    return VecIdx( mVec128, idx );
}

inline const floatInVec Vector3::operator []( int idx ) const
{
    return floatInVec( mVec128, idx );
}

inline const Vector3 Vector3::operator +( const Vector3 &vec ) const
{
    return Vector3( _mm_add_ps( mVec128, vec.mVec128 ) );
}

inline const Vector3 Vector3::operator -( const Vector3 &vec ) const
{
    return Vector3( _mm_sub_ps( mVec128, vec.mVec128 ) );
}

inline const Point3 Vector3::operator +( const Point3 &pnt ) const
{
    return Point3( _mm_add_ps( mVec128, pnt.get128() ) );
}

inline const Vector3 Vector3::operator *( float scalar ) const
{
    return *this * floatInVec(scalar);
}

inline const Vector3 Vector3::operator *( const floatInVec &scalar ) const
{
    return Vector3( _mm_mul_ps( mVec128, scalar.get128() ) );
}

inline Vector3 & Vector3::operator +=( const Vector3 &vec )
{
    *this = *this + vec;
    return *this;
}

inline Vector3 & Vector3::operator -=( const Vector3 &vec )
{
    *this = *this - vec;
    return *this;
}

inline Vector3 & Vector3::operator *=( float scalar )
{
    *this = *this * scalar;
    return *this;
}

inline Vector3 & Vector3::operator *=( const floatInVec &scalar )
{
    *this = *this * scalar;
    return *this;
}

inline const Vector3 Vector3::operator /( float scalar ) const
{
    return *this / floatInVec(scalar);
}

inline const Vector3 Vector3::operator /( const floatInVec &scalar ) const
{
    return Vector3( _mm_div_ps( mVec128, scalar.get128() ) );
}

inline Vector3 & Vector3::operator /=( float scalar )
{
    *this = *this / scalar;
    return *this;
}

inline Vector3 & Vector3::operator /=( const floatInVec &scalar )
{
    *this = *this / scalar;
    return *this;
}

inline const Vector3 Vector3::operator -( ) const
{
	return Vector3(_mm_sub_ps( _mm_setzero_ps(), mVec128 ) );
}

inline bool Vector3::operator < ( const Vector3 & vec ) const
{
	int		cmpmask = _mm_movemask_ps( _mm_cmplt_ps(mVec128, vec.mVec128) );
	return	(cmpmask == 0x7) || (cmpmask == 0xf);
}

inline bool Vector3::operator <= ( const Vector3 & vec ) const
{
	int		cmpmask = _mm_movemask_ps( _mm_cmple_ps(mVec128, vec.mVec128) );
	return	(cmpmask == 0x7) || (cmpmask == 0xf);
}

inline bool Vector3::operator > ( const Vector3 & vec ) const
{
	int		cmpmask = _mm_movemask_ps( _mm_cmpgt_ps(mVec128, vec.mVec128) );
	return	(cmpmask == 0x7) || (cmpmask == 0xf);
}

inline bool Vector3::operator >= ( const Vector3 & vec ) const
{
	int		cmpmask = _mm_movemask_ps( _mm_cmpge_ps(mVec128, vec.mVec128) );
	return	(cmpmask == 0x7) || (cmpmask == 0xf);
}

inline const floatInVec Vector3::maxElem( ) const
{
	return floatInVec( _mm_max_ps( _mm_max_ps( vec_splat( mVec128, 0 ), vec_splat( mVec128, 1 ) ), vec_splat( mVec128, 2 ) ) );
}

inline const floatInVec Vector3::minElem( ) const
{
	return floatInVec( _mm_min_ps( _mm_min_ps( vec_splat( mVec128, 0 ), vec_splat( mVec128, 1 ) ), vec_splat( mVec128, 2 ) ) );
}

inline const floatInVec Vector3::sum( ) const
{
	return floatInVec( _mm_add_ps( _mm_add_ps( vec_splat( mVec128, 0 ), vec_splat( mVec128, 1 ) ), vec_splat( mVec128, 2 ) ) );
}

inline const floatInVec Vector3::lengthSqr( ) const
{
	return floatInVec(  _vmathVfDot3( mVec128, mVec128 ), 0 );
}

inline const floatInVec Vector3::length( ) const
{
	return floatInVec(  _mm_sqrt_ps(_vmathVfDot3( mVec128, mVec128 )), 0 );
}

inline void Vector3::clampLength( float max_len )
{
	float lens = lengthSqr( );
	boolInVec b(lens > max_len * max_len);

	__m128 vscale = _mm_set1_ps( max_len / sqrtf( lens ) );
	__m128 allone = _mm_set1_ps( 1.0f );
	vscale = vec_sel( allone, vscale, b.get128() );

	mVec128 = _mm_mul_ps( mVec128, vscale );
}

inline void Vector3::setLength( float len )
{
	float lens = lengthSqr( );
	boolInVec b(lens < EQ_EPSILON * EQ_EPSILON);

	__m128 vscale = _mm_set1_ps( len / sqrtf( lens ) );
	__m128 allone = _mm_set1_ps( 1.0f );
	vscale = vec_sel( vscale, allone, b.get128() );

	mVec128 = _mm_mul_ps( mVec128, vscale );
}

inline void Vector3::normalize( )
{
	mVec128 = _mm_mul_ps( mVec128, _mm_rsqrt_ps( _vmathVfDot3( mVec128, mVec128 ) ) );
}

inline const Vector3 operator *( float scalar, const Vector3 &vec )
{
    return floatInVec(scalar) * vec;
}

inline const Vector3 operator *( const floatInVec &scalar, const Vector3 &vec )
{
    return vec * scalar;
}

inline const Vector3 mulPerElem( const Vector3 &vec0, const Vector3 &vec1 )
{
    return Vector3( _mm_mul_ps( vec0.get128(), vec1.get128() ) );
}

inline const Vector3 divPerElem( const Vector3 &vec0, const Vector3 &vec1 )
{
    return Vector3( _mm_div_ps( vec0.get128(), vec1.get128() ) );
}

inline const Vector3 recipPerElem( const Vector3 &vec )
{
    return Vector3( _mm_rcp_ps( vec.get128() ) );
}

inline const Vector3 absPerElem( const Vector3 &vec )
{
    return Vector3( fabsf4( vec.get128() ) );
}

inline const Vector3 copySignPerElem( const Vector3 &vec0, const Vector3 &vec1 )
{
	__m128 vmask = toM128(0x7fffffff);
	return Vector3( _mm_or_ps(
		_mm_and_ps   ( vmask, vec0.get128() ),			// Value
		_mm_andnot_ps( vmask, vec1.get128() ) ) );		// Signs
}

inline const Vector3 maxPerElem( const Vector3 &vec0, const Vector3 &vec1 )
{
    return Vector3( _mm_max_ps( vec0.get128(), vec1.get128() ) );
}

inline const Vector3 minPerElem( const Vector3 &vec0, const Vector3 &vec1 )
{
    return Vector3( _mm_min_ps( vec0.get128(), vec1.get128() ) );
}

inline const floatInVec dot( const Vector3 &vec0, const Vector3 &vec1 )
{
    return floatInVec( _vmathVfDot3( vec0.get128(), vec1.get128() ), 0 );
}

inline const Vector3 clampLength(const Vector3& vec, float max_len)
{
	float lens = vec.lengthSqr( );
	boolInVec b(lens > max_len * max_len);

	__m128 vscale = _mm_set1_ps( max_len / sqrtf( lens ) );
	__m128 allone = _mm_set1_ps( 1.0f );
	vscale = vec_sel( allone, vscale, b.get128() );

	return Vector3(_mm_mul_ps( vec.get128(), vscale ));
}

inline const Vector3 setLength(const Vector3& vec, float len)
{
	float lens = vec.lengthSqr( );
	boolInVec b(lens < EQ_EPSILON * EQ_EPSILON);

	__m128 vscale = _mm_set1_ps( len / sqrtf( lens ) );
	__m128 allone = _mm_set1_ps( 1.0f );
	vscale = vec_sel( vscale, allone, b.get128() );

	return Vector3( _mm_mul_ps( vec.get128(), vscale ) );
}

inline const Vector3 normalize( const Vector3 &vec )
{
    return Vector3( _mm_mul_ps( vec.get128(), _mm_rsqrt_ps( _vmathVfDot3( vec.get128(), vec.get128() ) ) ) );
}

inline const Vector3 cross( const Vector3 &vec0, const Vector3 &vec1 )
{
    return Vector3( _vmathVfCross( vec0.get128(), vec1.get128() ) );
}

inline const Vector3 select( const Vector3 &vec0, const Vector3 &vec1, bool select1 )
{
    return select( vec0, vec1, boolInVec(select1) );
}

inline const Vector3 select( const Vector3 &vec0, const Vector3 &vec1, const boolInVec &select1 )
{
	return Vector3(vec_sel( vec0.get128(), vec1.get128(), select1.get128() ));
}

inline bool equivalent (const Vector3 & vec0, const Vector3 & vec1, float epsilon)
{
	__m128	abs		= fabsf4( _mm_sub_ps( vec0.get128(), vec1.get128() ) );	// Subtract and abs
	__m128	eps		= _mm_set1_ps(epsilon);									// Construct epsilon
	int		cmpmask = _mm_movemask_ps( _mm_cmple_ps(abs, eps) );			// Compose mask
	return	(cmpmask == 0x7) || (cmpmask == 0xf);							// Ignore last bit
}

inline bool equivalentRelative(const Vector3 & vec0, const Vector3 & vec1, float precision)
{
	return m128_cmp_rel(vec0.get128(), vec1.get128(), precision, 3);
}

#ifdef _DEBUG  // Debug versions check alignment before initialization

inline Vector4::Vector4( float _x, float _y, float _z, float _w )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_setr_ps(_x, _y, _z, _w);
}

inline Vector4::Vector4( const floatInVec &_x, const floatInVec &_y, const floatInVec &_z, const floatInVec &_w )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_unpacklo_ps(
		_mm_unpacklo_ps( _x.get128(), _z.get128() ),
		_mm_unpacklo_ps( _y.get128(), _w.get128() ) );
}

inline Vector4::Vector4( const Vector3 &xyz, float _w )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = xyz.get128();
    _vmathVfSetElement(mVec128, _w, 3);
}

inline Vector4::Vector4( const Vector3 &xyz, const floatInVec &_w )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = xyz.get128();
    mVec128 = _vmathVfInsert(mVec128, _w.get128(), 3);
}

inline Vector4::Vector4( const Vector3 &vec )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = vec.get128();
    mVec128 = _vmathVfInsert(mVec128, _mm_setzero_ps(), 3);
}

inline Vector4::Vector4( const Point3 &pnt )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = pnt.get128();
    mVec128 = _vmathVfInsert(mVec128, _mm_set1_ps(1.0f), 3);
}

inline Vector4::Vector4( const Quat &quat )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = quat.get128();
}

inline Vector4::Vector4( float scalar )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_set1_ps(scalar);
}

inline Vector4::Vector4( _t_min )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_set1_ps((std::numeric_limits<float>::min)());
}

inline Vector4::Vector4( _t_max )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_set1_ps((std::numeric_limits<float>::max)());
}

inline Vector4::Vector4( const floatInVec &scalar )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = scalar.get128();
}

inline Vector4::Vector4( const __m128& vf4 )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = vf4;
}

#else

inline Vector4::Vector4( float _x, float _y, float _z, float _w ) : mVec128( _mm_setr_ps(_x, _y, _z, _w) ) { }

inline Vector4::Vector4( const floatInVec &_x, const floatInVec &_y, const floatInVec &_z, const floatInVec &_w )
{
	mVec128 = _mm_unpacklo_ps(
		_mm_unpacklo_ps( _x.get128(), _z.get128() ),
		_mm_unpacklo_ps( _y.get128(), _w.get128() ) );
}

inline Vector4::Vector4( const Vector3 &xyz, float _w ) : mVec128( xyz.get128() )
{ _vmathVfSetElement(mVec128, _w, 3); }

inline Vector4::Vector4( const Vector3 &xyz, const floatInVec &_w ) : mVec128( xyz.get128() )
{ mVec128 = _vmathVfInsert(mVec128, _w.get128(), 3); }

inline Vector4::Vector4( const Vector3 &vec ) : mVec128( vec.get128() )
{ mVec128 = _vmathVfInsert(mVec128, _mm_setzero_ps(), 3); }

inline Vector4::Vector4( const Point3 &pnt ) : mVec128( pnt.get128() )
{ mVec128 = pnt.get128(); mVec128 = _vmathVfInsert(mVec128, _mm_set1_ps(1.0f), 3); }

inline Vector4::Vector4( const Quat &quat ) : mVec128( quat.get128() ) { }

inline Vector4::Vector4( float scalar ) : mVec128(_mm_set1_ps(scalar)) { }

inline Vector4::Vector4( _t_min ) : mVec128(_mm_set1_ps((std::numeric_limits<float>::min)())) { }

inline Vector4::Vector4( _t_max ) : mVec128(_mm_set1_ps((std::numeric_limits<float>::max)())) { }

inline Vector4::Vector4( const floatInVec &scalar ) : mVec128(scalar.get128()) { }

inline Vector4::Vector4( const __m128& vf4 ) : mVec128( vf4 ) { }

#endif

inline const Vector4 Vector4::xAxis( )
{
    return Vector4( _VECTORMATH_UNIT_1000 );
}

inline const Vector4 Vector4::yAxis( )
{
    return Vector4( _VECTORMATH_UNIT_0100 );
}

inline const Vector4 Vector4::zAxis( )
{
    return Vector4( _VECTORMATH_UNIT_0010 );
}

inline const Vector4 Vector4::wAxis( )
{
    return Vector4( _VECTORMATH_UNIT_0001 );
}

inline const Vector4 lerp( float t, const Vector4 &vec0, const Vector4 &vec1 )
{
    return lerp( floatInVec(t), vec0, vec1 );
}

inline const Vector4 lerp( const floatInVec &t, const Vector4 &vec0, const Vector4 &vec1 )
{
    return ( vec0 + ( ( vec1 - vec0 ) * t ) );
}

inline const Vector4 slerp( float t, const Vector4 &unitVec0, const Vector4 &unitVec1 )
{
    return slerp( floatInVec(t), unitVec0, unitVec1 );
}

inline const Vector4 slerp( const floatInVec &t, const Vector4 &unitVec0, const Vector4 &unitVec1 )
{
    __m128 scales, scale0, scale1, cosAngle, angle, tttt, oneMinusT, angles, sines;
    cosAngle = _vmathVfDot4( unitVec0.get128(), unitVec1.get128() );
    __m128 selectMask = _mm_cmpgt_ps( _mm_set1_ps(_VECTORMATH_SLERP_TOL), cosAngle );
    angle = acosf4( cosAngle );
    tttt = t.get128();
    oneMinusT = _mm_sub_ps( _mm_set1_ps(1.0f), tttt );
    angles = _mm_unpacklo_ps( _mm_set1_ps(1.0f), tttt ); // angles = 1, t, 1, t
    angles = _mm_unpacklo_ps( angles, oneMinusT );		// angles = 1, 1-t, t, 1-t
    angles = _mm_mul_ps( angles, angle );
    sines = sinf4( angles );
    scales = _mm_div_ps( sines, vec_splat( sines, 0 ) );
    scale0 = vec_sel( oneMinusT, vec_splat( scales, 1 ), selectMask );
    scale1 = vec_sel( tttt, vec_splat( scales, 2 ), selectMask );
    return Vector4( vec_madd( unitVec0.get128(), scale0, _mm_mul_ps( unitVec1.get128(), scale1 ) ) );
}

inline const __m128& Vector4::get128( ) const
{
    return mVec128;
}
/*
inline void storeHalfFloats( const Vector4 &vec0, const Vector4 &vec1, const Vector4 &vec2, const Vector4 &vec3, vec_ushort8 * twoQuads )
{
    twoQuads[0] = _vmath2VfToHalfFloats(vec0.get128(), vec1.get128());
    twoQuads[1] = _vmath2VfToHalfFloats(vec2.get128(), vec3.get128());
}
*/
inline Vector4 & Vector4::operator =( const Vector4 &vec )
{
    mVec128 = vec.mVec128;
    return *this;
}

inline Vector4 & Vector4::setXYZ( const Vector3 &vec )
{
	__declspec(align(16)) unsigned int sw[4] = {0, 0, 0, 0xffffffff};
	mVec128 = vec_sel( vec.get128(), mVec128, sw );
    return *this;
}

inline const Vector3 Vector4::getXYZ( ) const
{
    return Vector3( mVec128 );
}

inline void Vector4::setX( float _x ) { _vmathVfSetElement(mVec128, _x, 0); }

inline void Vector4::setX( const floatInVec &_x ) { mVec128 = _vmathVfInsert(mVec128, _x.get128(), 0); }

inline const floatInVec Vector4::getX( ) const { return floatInVec( mVec128, 0 ); }

inline float Vector4::getXf( ) const { return getX(); }

inline void Vector4::setY( float _y ) { _vmathVfSetElement(mVec128, _y, 1); }

inline void Vector4::setY( const floatInVec &_y ) { mVec128 = _vmathVfInsert(mVec128, _y.get128(), 1); }

inline const floatInVec Vector4::getY( ) const { return floatInVec( mVec128, 1 ); }

inline float Vector4::getYf( ) const { return getY(); }

inline void Vector4::setZ( float _z ) { _vmathVfSetElement(mVec128, _z, 2); }

inline void Vector4::setZ( const floatInVec &_z ) { mVec128 = _vmathVfInsert(mVec128, _z.get128(), 2); }

inline const floatInVec Vector4::getZ( ) const { return floatInVec( mVec128, 2 ); }

inline float Vector4::getZf( ) const { return getZ(); }

inline void Vector4::setW( float _w ) { _vmathVfSetElement(mVec128, _w, 3); }

inline void Vector4::setW( const floatInVec &_w ) { mVec128 = _vmathVfInsert(mVec128, _w.get128(), 3); }

inline const floatInVec Vector4::getW( ) const { return floatInVec( mVec128, 3 ); }

inline float Vector4::getWf( ) const { return getW(); }

inline void Vector4::setElem( int idx, float value ) { _vmathVfSetElement(mVec128, value, idx); }

inline void Vector4::setElem( int idx, const floatInVec &value ) { mVec128 = _vmathVfInsert(mVec128, value.get128(), idx); }

inline const floatInVec Vector4::getElem( int idx ) const { return floatInVec( mVec128, idx ); }

inline VecIdx Vector4::operator []( int idx )
{
    return VecIdx( mVec128, idx );
}

inline const floatInVec Vector4::operator []( int idx ) const
{
    return floatInVec( mVec128, idx );
}

inline const Vector4 Vector4::operator +( const Vector4 &vec ) const
{
    return Vector4( _mm_add_ps( mVec128, vec.mVec128 ) );
}

inline const Vector4 Vector4::operator -( const Vector4 &vec ) const
{
    return Vector4( _mm_sub_ps( mVec128, vec.mVec128 ) );
}

inline const Vector4 Vector4::operator *( float scalar ) const
{
    return *this * floatInVec(scalar);
}

inline const Vector4 Vector4::operator *( const floatInVec &scalar ) const
{
    return Vector4( _mm_mul_ps( mVec128, scalar.get128() ) );
}

inline Vector4 & Vector4::operator +=( const Vector4 &vec )
{
    *this = *this + vec;
    return *this;
}

inline Vector4 & Vector4::operator -=( const Vector4 &vec )
{
    *this = *this - vec;
    return *this;
}

inline Vector4 & Vector4::operator *=( float scalar )
{
    *this = *this * scalar;
    return *this;
}

inline Vector4 & Vector4::operator *=( const floatInVec &scalar )
{
    *this = *this * scalar;
    return *this;
}

inline const Vector4 Vector4::operator /( float scalar ) const
{
    return *this / floatInVec(scalar);
}

inline const Vector4 Vector4::operator /( const floatInVec &scalar ) const
{
    return Vector4( _mm_div_ps( mVec128, scalar.get128() ) );
}

inline Vector4 & Vector4::operator /=( float scalar )
{
    *this = *this / scalar;
    return *this;
}

inline Vector4 & Vector4::operator /=( const floatInVec &scalar )
{
    *this = *this / scalar;
    return *this;
}

inline const Vector4 Vector4::operator -( ) const
{
	return Vector4(_mm_sub_ps( _mm_setzero_ps(), mVec128 ) );
}

inline bool Vector4::operator < ( const Vector4 & vec ) const
{
	int		cmpmask = _mm_movemask_ps( _mm_cmplt_ps(mVec128, vec.mVec128) );
	return	cmpmask == 0xf;
}

inline bool Vector4::operator <= ( const Vector4 & vec ) const
{
	int		cmpmask = _mm_movemask_ps( _mm_cmple_ps(mVec128, vec.mVec128) );
	return	cmpmask == 0xf;
}

inline bool Vector4::operator > ( const Vector4 & vec ) const
{
	int		cmpmask = _mm_movemask_ps( _mm_cmpgt_ps(mVec128, vec.mVec128) );
	return	cmpmask == 0xf;
}

inline bool Vector4::operator >= ( const Vector4 & vec ) const
{
	int		cmpmask = _mm_movemask_ps( _mm_cmpge_ps(mVec128, vec.mVec128) );
	return	cmpmask == 0xf;
}

inline const floatInVec Vector4::maxElem( ) const
{
	return floatInVec( _mm_max_ps(
		_mm_max_ps( vec_splat( mVec128, 0 ), vec_splat( mVec128, 1 ) ),
		_mm_max_ps( vec_splat( mVec128, 2 ), vec_splat( mVec128, 3 ) ) ) );
}

inline const floatInVec Vector4::minElem( ) const
{
	return floatInVec( _mm_min_ps(
		_mm_min_ps( vec_splat( mVec128, 0 ), vec_splat( mVec128, 1 ) ),
		_mm_min_ps( vec_splat( mVec128, 2 ), vec_splat( mVec128, 3 ) ) ) );
}

inline const floatInVec Vector4::sum( ) const
{
	return floatInVec( _mm_add_ps(
		_mm_add_ps( vec_splat( mVec128, 0 ), vec_splat( mVec128, 1 ) ),
		_mm_add_ps( vec_splat( mVec128, 2 ), vec_splat( mVec128, 3 ) ) ) );
}

inline const floatInVec Vector4::lengthSqr( ) const
{
	return floatInVec( _vmathVfDot4( mVec128, mVec128 ), 0 );
}

inline const floatInVec Vector4::length( ) const
{
	return floatInVec( _mm_sqrt_ps(_vmathVfDot4( mVec128, mVec128 )), 0 );
}

inline void Vector4::clampLength( float max_len )
{
	float lens = lengthSqr( );
	boolInVec b(lens > max_len * max_len);

	__m128 vscale = _mm_set1_ps( max_len / sqrtf( lens ) );
	__m128 allone = _mm_set1_ps( 1.0f );
	vscale = vec_sel( allone, vscale, b.get128() );

	mVec128 = _mm_mul_ps( mVec128, vscale );
}

inline void Vector4::setLength( float len )
{
	float lens = lengthSqr( );
	boolInVec b(lens < EQ_EPSILON * EQ_EPSILON);

	__m128 vscale = _mm_set1_ps( len / sqrtf( lens ) );
	__m128 allone = _mm_set1_ps( 1.0f );
	vscale = vec_sel( vscale, allone, b.get128() );

	mVec128 = _mm_mul_ps( mVec128, vscale );
}

inline void Vector4::normalize( )
{
	mVec128 = _mm_mul_ps( mVec128, _mm_rsqrt_ps( _vmathVfDot4( mVec128, mVec128 ) ) );
}

inline const Vector4 operator *( float scalar, const Vector4 &vec )
{
    return floatInVec(scalar) * vec;
}

inline const Vector4 operator *( const floatInVec &scalar, const Vector4 &vec )
{
    return vec * scalar;
}

inline const Vector4 mulPerElem( const Vector4 &vec0, const Vector4 &vec1 )
{
    return Vector4( _mm_mul_ps( vec0.get128(), vec1.get128() ) );
}

inline const Vector4 divPerElem( const Vector4 &vec0, const Vector4 &vec1 )
{
    return Vector4( _mm_div_ps( vec0.get128(), vec1.get128() ) );
}

inline const Vector4 recipPerElem( const Vector4 &vec )
{
    return Vector4( _mm_rcp_ps( vec.get128() ) );
}

inline const Vector4 absPerElem( const Vector4 &vec )
{
    return Vector4( fabsf4( vec.get128() ) );
}

inline const Vector4 copySignPerElem( const Vector4 &vec0, const Vector4 &vec1 )
{
	__m128 vmask = toM128(0x7fffffff);
	return Vector4( _mm_or_ps(
		_mm_and_ps   ( vmask, vec0.get128() ),			// Value
		_mm_andnot_ps( vmask, vec1.get128() ) ) );		// Signs
}

inline const Vector4 maxPerElem( const Vector4 &vec0, const Vector4 &vec1 )
{
    return Vector4( _mm_max_ps( vec0.get128(), vec1.get128() ) );
}

inline const Vector4 minPerElem( const Vector4 &vec0, const Vector4 &vec1 )
{
    return Vector4( _mm_min_ps( vec0.get128(), vec1.get128() ) );
}

inline const floatInVec dot( const Vector4 &vec0, const Vector4 &vec1 )
{
    return floatInVec( _vmathVfDot4( vec0.get128(), vec1.get128() ), 0 );
}

inline const Vector4 clampLength(const Vector4& vec, float max_len)
{
	float lens = vec.lengthSqr( );
	boolInVec b(lens > max_len * max_len);

	__m128 vscale = _mm_set1_ps( max_len / sqrtf( lens ) );
	__m128 allone = _mm_set1_ps( 1.0f );
	vscale = vec_sel( allone, vscale, b.get128() );

	return Vector4(_mm_mul_ps( vec.get128(), vscale ));
}

inline const Vector4 setLength(const Vector4& vec, float len)
{
	float lens = vec.lengthSqr( );
	boolInVec b(lens < EQ_EPSILON * EQ_EPSILON);

	__m128 vscale = _mm_set1_ps( len / sqrtf( lens ) );
	__m128 allone = _mm_set1_ps( 1.0f );
	vscale = vec_sel( vscale, allone, b.get128() );

	return Vector4( _mm_mul_ps( vec.get128(), vscale ) );
}

inline const Vector4 normalize( const Vector4 &vec )
{
    return Vector4( _mm_mul_ps( vec.get128(), _mm_rsqrt_ps( _vmathVfDot4( vec.get128(), vec.get128() ) ) ) );
}

inline const Vector4 select( const Vector4 &vec0, const Vector4 &vec1, bool select1 )
{
    return select( vec0, vec1, boolInVec(select1) );
}

inline const Vector4 select( const Vector4 &vec0, const Vector4 &vec1, const boolInVec &select1 )
{
    return Vector4( vec_sel( vec0.get128(), vec1.get128(), select1.get128() ) );
}

inline bool equivalent (const Vector4 & vec0, const Vector4 & vec1, float epsilon)
{
	__m128	abs		= fabsf4( _mm_sub_ps( vec0.get128(), vec1.get128() ) );	// Subtract and abs
	__m128	eps		= _mm_set1_ps(epsilon);									// Construct epsilon
	int		cmpmask = _mm_movemask_ps( _mm_cmple_ps(abs, eps) );			// Compose mask
	return	cmpmask == 0xf;
}

inline bool equivalentRelative(const Vector4 & vec0, const Vector4 & vec1, float precision)
{
	return m128_cmp_rel(vec0.get128(), vec1.get128(), precision, 4);
}


#ifdef _DEBUG // Check for alignment in debug mode

inline Point3::Point3( float _x, float _y, float _z )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_setr_ps(_x, _y, _z, 0.0f);
}

inline Point3::Point3( const floatInVec &_x, const floatInVec &_y, const floatInVec &_z )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_unpacklo_ps( _mm_unpacklo_ps( _x.get128(), _z.get128() ), _y.get128() );
}

inline Point3::Point3( const Vector3 &vec )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = vec.get128();
}

inline Point3::Point3( float scalar )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_set1_ps(scalar);
}

inline Point3::Point3( _t_min )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_set1_ps((std::numeric_limits<float>::min)());
}

inline Point3::Point3( _t_max )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = _mm_set1_ps((std::numeric_limits<float>::max)());
}

inline Point3::Point3( const floatInVec &scalar )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = scalar.get128();
}

inline Point3::Point3( const __m128& vf4 )
{
	_CHECK_ALIGN(mVec128, 16);
	mVec128 = vf4;
}

#else

inline Point3::Point3( float _x, float _y, float _z ) : mVec128( _mm_setr_ps(_x, _y, _z, 0.0f) ) { }

inline Point3::Point3( const floatInVec &_x, const floatInVec &_y, const floatInVec &_z )
: mVec128( _mm_unpacklo_ps( _mm_unpacklo_ps( _x.get128(), _z.get128() ), _y.get128() ) )
{ }

inline Point3::Point3( const Vector3 &vec ) : mVec128( vec.get128() ) { }

inline Point3::Point3( float scalar ) : mVec128( _mm_set1_ps(scalar) ) { }

inline Point3::Point3( _t_min ) : mVec128(_mm_set1_ps((std::numeric_limits<float>::min)())) { }

inline Point3::Point3( _t_max ) : mVec128(_mm_set1_ps((std::numeric_limits<float>::max)())) { }

inline Point3::Point3( const floatInVec &scalar ) : mVec128( scalar.get128() ) { }

inline Point3::Point3( const __m128& vf4 ) : mVec128( vf4 ) { }

#endif

inline const Point3 lerp( float t, const Point3 &pnt0, const Point3 &pnt1 )
{
    return lerp( floatInVec(t), pnt0, pnt1 );
}

inline const Point3 lerp( const floatInVec &t, const Point3 &pnt0, const Point3 &pnt1 )
{
    return ( pnt0 + ( ( pnt1 - pnt0 ) * t ) );
}

inline const __m128& Point3::get128( ) const
{
    return mVec128;
}

inline void storeXYZ( const Point3 &pnt, __m128 * quad )
{
    __m128 dstVec = *quad;
	__declspec(align(16)) unsigned int sw[4] = {0, 0, 0, 0xffffffff}; // TODO: Centralize
    dstVec = vec_sel(pnt.get128(), dstVec, sw);
    *quad = dstVec;
}

inline void loadXYZArray( Point3 & pnt0, Point3 & pnt1, Point3 & pnt2, Point3 & pnt3, const __m128 * threeQuads )
{
	const float *quads = (float *)threeQuads;
    pnt0 = Point3(  _mm_load_ps(quads) );
    pnt1 = Point3( _mm_loadu_ps(quads + 3) );
    pnt2 = Point3( _mm_loadu_ps(quads + 6) );
    pnt3 = Point3( _mm_loadu_ps(quads + 9) );
}

inline void storeXYZArray( const Point3 &pnt0, const Point3 &pnt1, const Point3 &pnt2, const Point3 &pnt3, __m128 * threeQuads )
{
	__m128 xxxx = _mm_shuffle_ps( pnt1.get128(), pnt1.get128(), _MM_SHUFFLE(0, 0, 0, 0) );
	__m128 zzzz = _mm_shuffle_ps( pnt2.get128(), pnt2.get128(), _MM_SHUFFLE(2, 2, 2, 2) );
	__declspec(align(16)) unsigned int xsw[4] = {0, 0, 0, 0xffffffff};
	__declspec(align(16)) unsigned int zsw[4] = {0xffffffff, 0, 0, 0};
	threeQuads[0] = vec_sel( pnt0.get128(), xxxx, xsw );
    threeQuads[1] = _mm_shuffle_ps( pnt1.get128(), pnt2.get128(), _MM_SHUFFLE(1, 0, 2, 1) );
    threeQuads[2] = vec_sel( _mm_shuffle_ps( pnt3.get128(), pnt3.get128(), _MM_SHUFFLE(2, 1, 0, 3) ), zzzz, zsw );
}
/*
inline void storeHalfFloats( const Point3 &pnt0, const Point3 &pnt1, const Point3 &pnt2, const Point3 &pnt3, const Point3 &pnt4, const Point3 &pnt5, const Point3 &pnt6, const Point3 &pnt7, vec_ushort8 * threeQuads )
{
#if 0
    __m128 xyz0[3];
    __m128 xyz1[3];
    storeXYZArray( pnt0, pnt1, pnt2, pnt3, xyz0 );
    storeXYZArray( pnt4, pnt5, pnt6, pnt7, xyz1 );
    threeQuads[0] = _vmath2VfToHalfFloats(xyz0[0], xyz0[1]);
    threeQuads[1] = _vmath2VfToHalfFloats(xyz0[2], xyz1[0]);
    threeQuads[2] = _vmath2VfToHalfFloats(xyz1[1], xyz1[2]);
#else
	assert(0);
#endif
}
*/
inline Point3 & Point3::operator =( const Point3 &pnt )
{
    mVec128 = pnt.mVec128;
    return *this;
}

inline void Point3::setX( float _x ) { _vmathVfSetElement(mVec128, _x, 0); }

inline void Point3::setX( const floatInVec &_x ) { mVec128 = _vmathVfInsert(mVec128, _x.get128(), 0); }

inline const floatInVec Point3::getX( ) const { return floatInVec( mVec128, 0 ); }

inline float Point3::getXf( ) const { return getX(); }

inline void Point3::setY( float _y ) { _vmathVfSetElement(mVec128, _y, 1); }

inline void Point3::setY( const floatInVec &_y ) { mVec128 = _vmathVfInsert(mVec128, _y.get128(), 1); }

inline const floatInVec Point3::getY( ) const { return floatInVec( mVec128, 1 ); }

inline float Point3::getYf( ) const { return getY(); }

inline void Point3::setZ( float _z ) { _vmathVfSetElement(mVec128, _z, 2); }

inline void Point3::setZ( const floatInVec &_z ) { mVec128 = _vmathVfInsert(mVec128, _z.get128(), 2); }

inline const floatInVec Point3::getZ( ) const { return floatInVec( mVec128, 2 ); }

inline float Point3::getZf( ) const { return getZ(); }

inline void Point3::setElem( int idx, float value ) { _vmathVfSetElement(mVec128, value, idx); }

inline void Point3::setElem( int idx, const floatInVec &value ) { mVec128 = _vmathVfInsert(mVec128, value.get128(), idx); }

inline const floatInVec Point3::getElem( int idx ) const { return floatInVec( mVec128, idx ); }

inline VecIdx Point3::operator []( int idx )
{
    return VecIdx( mVec128, idx );
}

inline const floatInVec Point3::operator []( int idx ) const
{
    return floatInVec( mVec128, idx );
}

inline const Vector3 Point3::operator -( const Point3 &pnt ) const
{
    return Vector3( _mm_sub_ps( mVec128, pnt.mVec128 ) );
}

inline const Point3 Point3::operator +( const Vector3 &vec ) const
{
    return Point3( _mm_add_ps( mVec128, vec.get128() ) );
}

inline const Point3 Point3::operator -( const Vector3 &vec ) const
{
    return Point3( _mm_sub_ps( mVec128, vec.get128() ) );
}

inline Point3 & Point3::operator +=( const Vector3 &vec )
{
    *this = *this + vec;
    return *this;
}

inline Point3 & Point3::operator -=( const Vector3 &vec )
{
    *this = *this - vec;
    return *this;
}

inline const floatInVec Point3::maxElem( ) const
{
	return floatInVec( _mm_max_ps( _mm_max_ps( vec_splat( mVec128, 0 ), vec_splat( mVec128, 1 ) ), vec_splat( mVec128, 2 ) ) );
}

inline const floatInVec Point3::minElem( ) const
{
	return floatInVec( _mm_min_ps( _mm_min_ps( vec_splat( mVec128, 0 ), vec_splat( mVec128, 1 ) ), vec_splat( mVec128, 2 ) ) );
}

inline const floatInVec Point3::sum( ) const
{
	return floatInVec( _mm_add_ps( _mm_add_ps( vec_splat( mVec128, 0 ), vec_splat( mVec128, 1 ) ), vec_splat( mVec128, 2 ) ) );
}

inline const floatInVec Point3::distSqrFromOrigin( ) const
{
	return Vector3( *this ).lengthSqr();
}

inline const floatInVec Point3::distFromOrigin( ) const
{
	return Vector3( *this ).length();
}

inline const Point3 mulPerElem( const Point3 &pnt0, const Point3 &pnt1 )
{
    return Point3( _mm_mul_ps( pnt0.get128(), pnt1.get128() ) );
}

inline const Point3 divPerElem( const Point3 &pnt0, const Point3 &pnt1 )
{
    return Point3( _mm_div_ps( pnt0.get128(), pnt1.get128() ) );
}

inline const Point3 recipPerElem( const Point3 &pnt )
{
    return Point3( _mm_rcp_ps( pnt.get128() ) );
}

inline const Point3 absPerElem( const Point3 &pnt )
{
    return Point3( fabsf4( pnt.get128() ) );
}

inline const Point3 copySignPerElem( const Point3 &pnt0, const Point3 &pnt1 )
{
	__m128 vmask = toM128(0x7fffffff);
	return Point3( _mm_or_ps(
		_mm_and_ps   ( vmask, pnt0.get128() ),			// Value
		_mm_andnot_ps( vmask, pnt1.get128() ) ) );		// Signs
}

inline const Point3 maxPerElem( const Point3 &pnt0, const Point3 &pnt1 )
{
    return Point3( _mm_max_ps( pnt0.get128(), pnt1.get128() ) );
}

inline const Point3 minPerElem( const Point3 &pnt0, const Point3 &pnt1 )
{
    return Point3( _mm_min_ps( pnt0.get128(), pnt1.get128() ) );
}

inline const Point3 scale( const Point3 &pnt, float scaleVal )
{
    return scale( pnt, floatInVec( scaleVal ) );
}

inline const Point3 scale( const Point3 &pnt, const floatInVec &scaleVal )
{
    return mulPerElem( pnt, Point3( scaleVal ) );
}

inline const Point3 scale( const Point3 &pnt, const Vector3 &scaleVec )
{
    return mulPerElem( pnt, Point3( scaleVec ) );
}

inline const floatInVec projection( const Point3 &pnt, const Vector3 &unitVec )
{
    return floatInVec( _vmathVfDot3( pnt.get128(), unitVec.get128() ), 0 );
}

inline const floatInVec distSqr( const Point3 &pnt0, const Point3 &pnt1 )
{
    return ( pnt1 - pnt0 ).lengthSqr();
}

inline const floatInVec dist( const Point3 &pnt0, const Point3 &pnt1 )
{
    return ( pnt1 - pnt0 ).length();
}

inline const Point3 select( const Point3 &pnt0, const Point3 &pnt1, bool select1 )
{
    return select( pnt0, pnt1, boolInVec(select1) );
}

inline const Point3 select( const Point3 &pnt0, const Point3 &pnt1, const boolInVec &select1 )
{
    return Point3( vec_sel( pnt0.get128(), pnt1.get128(), select1.get128() ) );
}

inline bool equivalent ( const Point3 & pnt0, const Point3 & pnt1, float epsilon)
{
	__m128	abs		= fabsf4( _mm_sub_ps( pnt0.get128(), pnt1.get128() ) );	// Subtract and abs
	__m128	eps		= _mm_set1_ps(epsilon);									// Construct epsilon
	int		cmpmask = _mm_movemask_ps( _mm_cmple_ps(abs, eps) );			// Compose mask
	return	(cmpmask == 0x7) || (cmpmask == 0xf);							// Ignore last bit
}

inline bool equivalentRelative( const Point3 & pnt0, const Point3 & pnt1, float precision )
{
	return m128_cmp_rel(pnt0.get128(), pnt1.get128(), precision, 3);
}

} // namespace VML

#endif