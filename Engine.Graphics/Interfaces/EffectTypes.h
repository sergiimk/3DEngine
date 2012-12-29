/*========================================================
* MaterialTypes.h
* @author Sergey Mikhtonyuk
* @date 16 May 2009
=========================================================*/
#ifndef _EFFECTTYPES_H__
#define _EFFECTTYPES_H__

#include <bitset>
#include <cassert>

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		/// Used for binding effect parameters to data queried from material callback
		/** Names in brackets should be used to address parameters in material files
		 *  @ingroup Graphics */
		enum EEffectParam
		{
			FXP_START_MATRIX_TYPES,						//////////////////////////////////////////////////////////
			FXP_MATRIX_WORLD,							///< 4x4 matrix of world transformation [matWorld]
			FXP_MATRIX_VIEW,							///< 4x4 matrix of view transform [matView]
			FXP_MATRIX_PROJECTION,						///< 4x4 matrix of projection transform [matProjection]
			FXP_MATRIX_WORLD_VIEW_PROJECTION,			///< 4x4 matrix of combined transforms [matWorldViewProjection]
			FXP_MATRIX_WORLD_INV,						///< 4x4 matrix to transform from world to object space [matWorldInv]
			FXP_MATRIX_VIEW_INV,						///< 4x4 matrix to transform from view to world space [matViewInv]
			FXP_MATRIX_WORLD_INV_TRANSPOSE,				///< 4x4 matrix to transform normals to world space [matWorldInvTranspose]
			FXP_MATRIX_WORLD_VIEW_INV_TRANSPOSE,		///< 4x4 matrix to transform normals to view space [matWorldViewInvTranspose]
			FXP_END_MATRIX_TYPES,						//////////////////////////////////////////////////////////

			FXP_START_VECTOR_TYPES,						//////////////////////////////////////////////////////////
			FXP_VECTOR_RT_RESOLUTION,					///< resolution of render target [vecRTResolution]
			FXP_VECTOR_RT_RESOLUTION_INV,				///< reciprocal resolution of render target [vecRTResolutionInv]
			FXP_VECTOR_CAMERA_POSITION,					///< 4x vector of camera position in world space [vecCameraPosition]
			FXP_VECTOR_CAMERA_DIRECTION,				///< 4x vector of camera direction in world space [vecCameraDirection]
			FXP_VECTOR_CAMERA_UP,						///< 4x vector of camera Up direction in world space [vecCameraUp]
			FXP_VECTOR_DIRACTIONAL_LIGHT_SOURCE,		///< vector opposite to rays of directional light [vecDirectionalLightSource]
			FXP_END_VECTOR_TYPES,						//////////////////////////////////////////////////////////

			FXP_START_COLOR_TYPES,						//////////////////////////////////////////////////////////
			FXP_COLOR_DIFFUSE,							///< 4x vector of diffuse color in rgba format [clrDiffuse]
			FXP_COLOR_SPECULAR,							///< 4x vector of specular color in rgba format [clrSpecular]
			FXP_COLOR_EMISSIVE,							///< 4x vector of emissive color in rgba format [clrEmissive]
			FXP_COLOR_AMBIENT_LIGHT,					///< 4x vector of ambient light irradiance [clrAmbientLight]
			FXP_COLOR_DIRECTIONAL_LIGHT,				///< 4x vector of directional light irradiance [clrDirectionalLight]
			FXP_END_COLOR_TYPES,						//////////////////////////////////////////////////////////

			FXP_START_TEXTURE_TYPES,					//////////////////////////////////////////////////////////
			FXP_TEXTURE_DIFFUSE,						///< texture with diffuse color [texDiffuse]
			FXP_TEXTURE_NORMAL,							///< texture with encoded normals [texNormal]
			FXP_TEXTURE_HEIGHT,							///< texture with encoded height [texHeight]
			FXP_TEXTURE_SHININESS,						///< texture with encoded shininess (specular power) [texShininess]
			FXP_TEXTURE_SPECULAR,						///< texture with encoded specular color [texSpecular]
			FXP_TEXTURE_EMISSIVE,						///< texture with encoded emissive color [texEmissive]
			FXP_TEXTURE_DEPTH,							///< texture with encoded depth [texDepth]
			FXP_TEXTURE_CUBEMAP,						///< cube map texture [texCubemap]
			FXP_TEXTURE_LIGHT_ACC,						///< light accumulation texture [texLightAcc]
			FXP_TEXTURE_SSAO,							///< ambient occlusion texture [texSSAO]
			FXP_END_TEXTURE_TYPES,						//////////////////////////////////////////////////////////

			FXP_START_FLOAT_TYPES,						//////////////////////////////////////////////////////////
			FXP_FLOAT_FRAME_TIME,						///< frame time in seconds [fltFrameTime]
			FXP_FLOAT_Z_NEAR,							///< camera's zNear clip plane distance [fltZNear]
			FXP_FLOAT_Z_FAR,							///< camera's zFar clip plane distance [fltZFar]
			FXP_FLOAT_FOV,								///< camera's field of view [fltFOV]
			FXP_FLOAT_ASPECT_RATIO,						///< camera's aspect ratio [fltAspectRatio]
			FXP_FLOAT_SHININESS,						///< float value of shininess (specular power) [fltShininess]
			FXP_END_FLOAT_TYPES,						//////////////////////////////////////////////////////////

			FXP_NUM_PARAMS,
		};


		//////////////////////////////////////////////////////////////////////////


		/// Effect caps are used to describe compile time branching of effects
		/** When capability is not available the fallback in [] will be used
		 *  in effect description files as well as in the shader defines same 
		 *  names, but without FXC_ prefix are used
		 *  @ingroup Graphics */
		enum EEffectCap
		{
			FXC_DIFFUSE_MAP,		///< Supports diffuse textures		[solid color]
			FXC_NORMAL_MAP,			///< Supports normal mapping		[vertex normals]
			FXC_HEIGHT_MAP,			///< Supports height mapping		[normals only]
			FXC_SPECULAR_MAP,		///< Supports specular textures		[uniform spec color]
			FXC_SHININESS_MAP,		///< Supports shininess textures	[uniform spec power]
			FXC_EMISSIVE_MAP,		///< Supports emissive textures		[uniform emissive color]
			FXC_CUBE_MAP,			///< Supports cube mapping
			FXC_SSAO_MAP,			///< Supports SSAO

			FXC_AMBIENT_LIGHT,		///< Supports ambient light
			FXC_DIRECTIONAL_LIGHT,	///< Supports directional light

			FXC_NUM_CAPS,
		};


		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////


		/// Holds the set of parameters required by effect
		/** @ingroup Graphics */
		struct SEffectParams
		{
		public:

			/// Returns true if parameter is used by effect
			bool getUsageState(EEffectParam param) const
			{
				return mBitfield.test(param);
			}

			/// Sets the usage flag for specified parameter
			void setUsageState(EEffectParam param, bool state)
			{
				mBitfield.set(param, state ? 1 : 0);
			}

			/// combines all parameters to this one (union)
			void add(const SEffectParams& other)
			{
				mBitfield |= other.mBitfield;
			}

			/// Clears all parameters
			void clear()
			{
				mBitfield.reset();
			}

			//////////////////////////////////////////////////////////////////////////
			/// Iterator for parameter collection
			struct iterator
			{
				struct key_val { EEffectParam param; bool state; };

				iterator(const iterator& other)
				{
					kv = other.kv;
					owner = other.owner;
				}

				iterator& operator++()
				{
					if(kv.param != FXP_NUM_PARAMS)
					{
						kv.param = (EEffectParam)(kv.param + 1);
						if(kv.param != FXP_NUM_PARAMS)
							kv.state = owner->getUsageState(kv.param);
					}
					return *this;
				}

				iterator operator++(int)
				{
					iterator other(*this);
					++(*this);
					return other;
				}

				const key_val& operator*() const
				{
					assert(kv.param != FXP_NUM_PARAMS);
					return kv;
				}

				const key_val* operator->() const
				{
					assert(kv.param != FXP_NUM_PARAMS);
					return &kv;
				}

				bool operator==(const iterator& rhs)
				{
					return kv.param == rhs.kv.param && owner == rhs.owner;
				}

				bool operator!=(const iterator& rhs)
				{
					return !(*this == rhs);
				}

			private:
				iterator(size_t _pos, const SEffectParams* _owner) : owner(_owner) 
				{
					kv.param = (EEffectParam)_pos;
					if(kv.param != FXP_NUM_PARAMS)
						kv.state = owner->getUsageState(kv.param);
				}

				friend struct SEffectParams;

				const SEffectParams* owner;
				key_val kv;
			};
			//////////////////////////////////////////////////////////////////////////

			/// Iterator to the first entry
			iterator begin() const
			{
				return iterator(0, this);
			}

			/// Iterator for the entry after the last one
			iterator end() const
			{
				return iterator(FXP_NUM_PARAMS, this);
			}

		private:

			std::bitset<FXP_NUM_PARAMS> mBitfield;
		};


		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////


		/// Holds the set of caps required supported by the effect
		/** @ingroup Graphics */
		struct SEffectCaps
		{
		public:

			/// Returns true if parameter is used by effect
			bool getSupportState(EEffectCap cap) const
			{
				return mBitfield.test(cap);
			}

			/// Sets the usage flag for specified parameter
			void setSupportState(EEffectCap cap, bool state)
			{
				mBitfield.set(cap, state ? 1 : 0);
			}

			/// Clears all parameters
			void clear()
			{
				mBitfield.reset();
			}

			bool operator == (const SEffectCaps& other) const
			{
				return mBitfield == other.mBitfield;
			}

			bool operator != (const SEffectCaps& other) const
			{
				return mBitfield != other.mBitfield;
			}

			size_t hash() const
			{
				return mBitfield.to_ulong();
			}

			//////////////////////////////////////////////////////////////////////////
			/// Iterator for parameter collection
			struct iterator
			{
				struct key_val { EEffectCap cap; bool state; };

				iterator(const iterator& other)
				{
					kv = other.kv;
					owner = other.owner;
				}

				iterator& operator++()
				{
					if(kv.cap != FXC_NUM_CAPS)
					{
						kv.cap = (EEffectCap)(kv.cap + 1);
						if(kv.cap != FXC_NUM_CAPS)
							kv.state = owner->getSupportState(kv.cap);
					}
					return *this;
				}

				iterator operator++(int)
				{
					iterator other(*this);
					++(*this);
					return other;
				}

				const key_val& operator*() const
				{
					assert(kv.cap != FXC_NUM_CAPS);
					return kv;
				}

				const key_val* operator->() const
				{
					assert(kv.cap != FXC_NUM_CAPS);
					return &kv;
				}

				bool operator==(const iterator& rhs)
				{
					return kv.cap == rhs.kv.cap && owner == rhs.owner;
				}

				bool operator!=(const iterator& rhs)
				{
					return !(*this == rhs);
				}

			private:
				iterator(size_t _pos, const SEffectCaps* _owner) : owner(_owner) 
				{
					kv.cap = (EEffectCap)_pos;
					if(kv.cap != FXC_NUM_CAPS)
						kv.state = owner->getSupportState(kv.cap);
				}

				friend struct SEffectCaps;

				const SEffectCaps* owner;
				key_val kv;
			};
			//////////////////////////////////////////////////////////////////////////

			/// Iterator to the first entry
			iterator begin() const
			{
				return iterator(0, this);
			}

			/// Iterator for the entry after the last one
			iterator end() const
			{
				return iterator(FXC_NUM_CAPS, this);
			}

		private:

			std::bitset<FXC_NUM_CAPS> mBitfield;
		};


		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		/// Describes all caps supported by effect and corresponding parameters
		/** @ingroup Graphics */
		struct SEffectDesc
		{
		public:

			/// Returns the global effect parameters (const)
			const SEffectParams* getGlobalParameters() const 
			{
				return &mGlobalParams;
			}

			/// Returns the global effect parameters
			SEffectParams* getGlobalParameters() 
			{
				return &mGlobalParams;
			}

			/// Checks if effect supports this capability
			bool getCapSupport(EEffectCap cap) const
			{
				return mCaps.getSupportState(cap);
			}

			/// Sets the support flag for specific capability
			void setCapSupport(EEffectCap cap, bool val)
			{
				mCaps.setSupportState(cap, val);
			}

			/// Returns parameter set for specific cap (const)
			const SEffectParams* getScopedParameters(EEffectCap cap) const
			{
				if(!mCaps.getSupportState(cap)) return 0;
				return &mScopedParams[cap];
			}

			/// Returns parameter set for specific cap
			SEffectParams* getScopedParameters(EEffectCap cap)
			{
				if(!mCaps.getSupportState(cap)) return 0;
				return &mScopedParams[cap];
			}

			/// Clears all values
			void clear()
			{
				mGlobalParams.clear();
				for(int i = 0; i != FXC_NUM_CAPS; ++i)
					mScopedParams[i].clear();
				mCaps.clear();
			}

			//////////////////////////////////////////////////////////////////////////
			/// Iterator for parameter collection
			struct iterator
			{
				struct key_val { EEffectCap cap; const SEffectParams* params; };

				iterator(const iterator& other)
				{
					kv = other.kv;
					owner = other.owner;
				}

				iterator& operator++()
				{
					if(kv.cap != FXC_NUM_CAPS)
					{
						kv.cap = (EEffectCap)(kv.cap + 1);
						if(kv.cap != FXC_NUM_CAPS)
							kv.params = owner->getScopedParameters(kv.cap);
					}
					return *this;
				}

				iterator operator++(int)
				{
					iterator other(*this);
					++(*this);
					return other;
				}

				const key_val& operator*() const
				{
					assert(kv.cap != FXC_NUM_CAPS);
					return kv;
				}

				const key_val* operator->() const
				{
					assert(kv.cap != FXC_NUM_CAPS);
					return &kv;
				}

				bool operator==(const iterator& rhs)
				{
					return kv.cap == rhs.kv.cap && owner == rhs.owner;
				}

				bool operator!=(const iterator& rhs)
				{
					return !(*this == rhs);
				}

			private:
				iterator(size_t _pos, const SEffectDesc* _owner) : owner(_owner) 
				{
					kv.cap = (EEffectCap)_pos;
					if(kv.cap != FXC_NUM_CAPS)
						kv.params = owner->getScopedParameters(kv.cap);
				}

				friend struct SEffectDesc;

				const SEffectDesc* owner;
				key_val kv;
			};
			//////////////////////////////////////////////////////////////////////////

			/// Iterator to the first entry
			iterator begin() const
			{
				return iterator(0, this);
			}

			/// Iterator for the entry after the last one
			iterator end() const
			{
				return iterator(FXC_NUM_CAPS, this);
			}

		private:

			SEffectParams	mGlobalParams;
			SEffectParams	mScopedParams[FXC_NUM_CAPS];
			SEffectCaps		mCaps;
		};

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif	// _EFFECTTYPES_H__