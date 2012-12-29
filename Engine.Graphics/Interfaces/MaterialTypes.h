/*========================================================
* MaterialTypes.h
* @author Sergey Mikhtonyuk
* @date 18 August 2009
=========================================================*/
#ifndef _MATERIALTYPES_H__
#define _MATERIALTYPES_H__

#include "../Graphics_fwd.h"
#include "EffectTypes.h"
#include "ITexture.h"
#include "ISurfaceManager.h"
#include "../../Core.Math/VML.h"

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		// Storage for binding values
		/// \todo optimize storage of bindings
		struct MaterialBindingValue {
			MaterialBindingValue() : val_texture(0) { }

			union {
				float val_float4[4];
				float val_float;
				ITexture* val_texture;
			};
		};

		//////////////////////////////////////////////////////////////////////////

		/// Stores the bindings of material
		/** @ingroup Graphics */
		struct SMaterialBindings
		{
			/// Ctor
			SMaterialBindings() : inUse(false) { }

			/// Destructor
			~SMaterialBindings() { clear(); }

			/// Checks if binding for specified parameter is active
			bool getBindingState(EEffectParam param) const;

			/// Removes binding for specified parameter
			void removeBinding(EEffectParam param);

			/// Adds binding for parameter with float value
			void addFloatBinding(EEffectParam param, float val);

			/// Adds binding for texture parameter
			void addTextureBinding(EEffectParam param, const char* val, ISurfaceManager* mgr);

			/// Adds binding for texture parameter
			void addTextureBinding(EEffectParam param, ITexture* val);

			/// Adds binding for parameter with vector4 value
			void addVector4Binding(EEffectParam param, const VML::Vector4& val);

			/// Adds binding for parameter with color value
			void addColorBinding(EEffectParam param, const VML::Vector4& val);

			/// Returns the bound value for specified parameter
			float getFloatBinding(EEffectParam param) const;

			/// Returns the bound value for specified parameter
			ITexture* getTextureBinding(EEffectParam param) const;

			/// Returns the bound value for specified parameter
			VML::Vector4 getVector4Binding(EEffectParam param) const;

			/// Returns the bound value for specified parameter
			VML::Vector4 getColorBinding(EEffectParam param) const;

			/// Removes all active bindings
			void clear();

			/// Sets the usage flag
			void setInUse(bool use);

		private:

			SEffectParams			params; ///< Marks active bindings

			MaterialBindingValue	bindings[FXP_NUM_PARAMS]; ///< Value storage

			bool					inUse; ///< Usage counter of resources should be incremented
		};


		//////////////////////////////////////////////////////////////////////////

		inline bool SMaterialBindings::getBindingState(EEffectParam param) const 
		{
			return params.getUsageState(param); 
		}

		//////////////////////////////////////////////////////////////////////////

		inline void SMaterialBindings::removeBinding(EEffectParam param)
		{
			if(!params.getUsageState(param)) return;
			if(bindings[param].val_texture && param > FXP_START_TEXTURE_TYPES && param < FXP_END_TEXTURE_TYPES)
			{
				if(inUse)
					bindings[param].val_texture->RemoveUser();

				bindings[param].val_texture->Release();
			}

			bindings[param].val_texture = 0;
			params.setUsageState(param, false);
		}

		//////////////////////////////////////////////////////////////////////////

		inline void SMaterialBindings::addFloatBinding(EEffectParam param, float val)
		{
			assert(param > FXP_START_FLOAT_TYPES && param < FXP_END_FLOAT_TYPES);
			removeBinding(param);
			params.setUsageState(param, true);
			bindings[param].val_float = val;
		}

		//////////////////////////////////////////////////////////////////////////

		inline void SMaterialBindings::addTextureBinding(EEffectParam param, const char* val, ISurfaceManager* mgr)
		{
			assert(param > FXP_START_TEXTURE_TYPES && param < FXP_END_TEXTURE_TYPES);
			removeBinding(param);
			params.setUsageState(param, true);

			if(param != FXP_TEXTURE_CUBEMAP)
				mgr->FindOrLoadTexture(Utils::URL(val), &bindings[param].val_texture);
			else
				mgr->FindOrLoadCubeTexture(Utils::URL(val), &bindings[param].val_texture);

			assert(bindings[param].val_texture);

			if(inUse)
				bindings[param].val_texture->AddUser();
		}

		//////////////////////////////////////////////////////////////////////////

		inline void SMaterialBindings::addTextureBinding(EEffectParam param, ITexture* val)
		{
			assert(val && param > FXP_START_TEXTURE_TYPES && param < FXP_END_TEXTURE_TYPES);
			removeBinding(param);
			params.setUsageState(param, true);
			bindings[param].val_texture = val;
			val->AddRef();

			if(inUse)
				val->AddUser();
		}

		//////////////////////////////////////////////////////////////////////////

		inline void SMaterialBindings::addVector4Binding(EEffectParam param, const VML::Vector4& val)
		{
			assert(param > FXP_START_VECTOR_TYPES && param < FXP_END_VECTOR_TYPES);
			removeBinding(param);
			params.setUsageState(param, true);
			bindings[param].val_float4[0] = val.getX();
			bindings[param].val_float4[1] = val.getY();
			bindings[param].val_float4[2] = val.getZ();
			bindings[param].val_float4[3] = val.getW();
		}

		//////////////////////////////////////////////////////////////////////////

		inline void SMaterialBindings::addColorBinding(EEffectParam param, const VML::Vector4& val)
		{
			assert(param > FXP_START_COLOR_TYPES && param < FXP_END_COLOR_TYPES);
			removeBinding(param);
			params.setUsageState(param, true);
			bindings[param].val_float4[0] = val.getX();
			bindings[param].val_float4[1] = val.getY();
			bindings[param].val_float4[2] = val.getZ();
			bindings[param].val_float4[3] = val.getW();
		}

		//////////////////////////////////////////////////////////////////////////

		inline float SMaterialBindings::getFloatBinding(EEffectParam param) const
		{
			assert(param > FXP_START_FLOAT_TYPES && param < FXP_END_FLOAT_TYPES && params.getUsageState(param));
			return bindings[param].val_float;
		}

		//////////////////////////////////////////////////////////////////////////

		inline ITexture* SMaterialBindings::getTextureBinding(EEffectParam param) const
		{
			assert(param > FXP_START_TEXTURE_TYPES && param < FXP_END_TEXTURE_TYPES && params.getUsageState(param));
			return bindings[param].val_texture;
		}

		//////////////////////////////////////////////////////////////////////////

		inline VML::Vector4 SMaterialBindings::getVector4Binding(EEffectParam param) const
		{
			assert(param > FXP_START_VECTOR_TYPES && param < FXP_END_VECTOR_TYPES && params.getUsageState(param));
			const float* fs = bindings[param].val_float4;
			return VML::Vector4(fs[0], fs[1], fs[2], fs[3]);
		}

		//////////////////////////////////////////////////////////////////////////

		inline VML::Vector4 SMaterialBindings::getColorBinding(EEffectParam param) const
		{
			assert(param > FXP_START_COLOR_TYPES && param < FXP_END_COLOR_TYPES && params.getUsageState(param));
			const float* fs = bindings[param].val_float4;
			return VML::Vector4(fs[0], fs[1], fs[2], fs[3]);
		}

		//////////////////////////////////////////////////////////////////////////

		inline void SMaterialBindings::clear()
		{
			setInUse(false);

			for(int i = 0; i != FXP_NUM_PARAMS; ++i)
				removeBinding((EEffectParam)i);
		}

		//////////////////////////////////////////////////////////////////////////

		inline void SMaterialBindings::setInUse(bool use)
		{
			if(use == inUse) return;

			inUse = use;

			if(use)
			{
				for(int i = FXP_START_TEXTURE_TYPES + 1; i != FXP_END_TEXTURE_TYPES; ++i)
				{
					EEffectParam param = (EEffectParam)i;
					if(getBindingState(param))
						bindings[param].val_texture->AddUser();
				}
			}
			else
			{
				for(int i = FXP_START_TEXTURE_TYPES + 1; i != FXP_END_TEXTURE_TYPES; ++i)
				{
					EEffectParam param = (EEffectParam)i;
					if(getBindingState(param))
						bindings[param].val_texture->RemoveUser();
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif // _MATERIALTYPES_H__