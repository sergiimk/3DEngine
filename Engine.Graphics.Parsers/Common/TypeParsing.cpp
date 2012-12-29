/*========================================================
* TypeParsing.cpp
* @author Sergey Mikhtonyuk
* @date 17 August 2009
=========================================================*/
#include "TypeParsing.h"
#include <iostream>
#include <string>

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		
		const char* EElemUsage_ToString(EElemUsage val)
		{
			switch(val)
			{
			case USG_POSITION:			return "USG_POSITION";
			case USG_BLENDWEIGHT:		return "USG_BLENDWEIGHT";
			case USG_BLENDINDICES:		return "USG_BLENDINDICES";
			case USG_NORMAL:			return "USG_NORMAL";
			case USG_PSIZE:				return "USG_PSIZE";
			case USG_TEXCOORD:			return "USG_TEXCOORD";
			case USG_TANGENT:			return "USG_TANGENT";
			case USG_BINORMAL:			return "USG_BINORMAL";
			case USG_COLOR:				return "USG_COLOR";
			case USG_UNUSED:			return "USG_UNUSED";
			};
			return 0;
		}

		EElemUsage EElemUsage_FromString(const char* s)
		{
			if(!strcmp(s, "USG_POSITION"))				return USG_POSITION;
			else if(!strcmp(s, "USG_BLENDWEIGHT"))		return USG_BLENDWEIGHT;
			else if(!strcmp(s, "USG_BLENDINDICES"))		return USG_BLENDINDICES;
			else if(!strcmp(s, "USG_NORMAL"))			return USG_NORMAL;
			else if(!strcmp(s, "USG_PSIZE"))			return USG_PSIZE;
			else if(!strcmp(s, "USG_TEXCOORD"))			return USG_TEXCOORD;
			else if(!strcmp(s, "USG_TANGENT"))			return USG_TANGENT;
			else if(!strcmp(s, "USG_BINORMAL"))			return USG_BINORMAL;
			else if(!strcmp(s, "USG_COLOR"))			return USG_COLOR;
			else if(!strcmp(s, "USG_UNUSED"))			return USG_UNUSED;
			else return (EElemUsage)-1;
		}

		std::ostream& operator << (std::ostream& os, const EElemUsage& fmt)
		{
			const char* s = EElemUsage_ToString(fmt);
			os << (s ? s : "<null>");
			return os;
		}

		std::istream& operator >> (std::istream& is, EElemUsage& fmt)
		{
			std::string s;
			is >> s;
			EElemUsage mp = EElemUsage_FromString(s.c_str());
			if(mp == (EElemUsage)-1)
			{
				is.setstate(is.failbit);
				return is;
			}
			fmt = mp;
			return is;
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		const char* EElemType_ToString(EElemType val)
		{
			switch(val)
			{
			case ETYPE_FLOAT:			return "ETYPE_FLOAT";
			case ETYPE_FLOAT2:			return "ETYPE_FLOAT2";
			case ETYPE_FLOAT3:			return "ETYPE_FLOAT3";
			case ETYPE_FLOAT4:			return "ETYPE_FLOAT4";
			case ETYPE_UNUSED:			return "ETYPE_UNUSED";
			};
			return 0;
		}

		EElemType EElemType_FromString(const char* s)
		{
			if(!strcmp(s, "ETYPE_FLOAT"))			return ETYPE_FLOAT;
			else if(!strcmp(s, "ETYPE_FLOAT2"))		return ETYPE_FLOAT2;
			else if(!strcmp(s, "ETYPE_FLOAT3"))		return ETYPE_FLOAT3;
			else if(!strcmp(s, "ETYPE_FLOAT4"))		return ETYPE_FLOAT4;
			else if(!strcmp(s, "ETYPE_UNUSED"))		return ETYPE_UNUSED;
			else return (EElemType) -1;
		}

		std::ostream& operator << (std::ostream& os, const EElemType& fmt)
		{
			const char* s = EElemType_ToString(fmt);
			os << (s ? s : "<null>");
			return os;
		}

		std::istream& operator >> (std::istream& is, EElemType& fmt)
		{
			std::string s;
			is >> s;
			EElemType mp = EElemType_FromString(s.c_str());
			if(mp == (EElemType)-1)
			{
				is.setstate(is.failbit);
				return is;
			}
			fmt = mp;
			return is;
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		const char* EEffectParam_ToString(EEffectParam val)
		{
			switch(val)
			{
			case FXP_MATRIX_WORLD:									return "matWorld";
			case FXP_MATRIX_VIEW:									return "matView";
			case FXP_MATRIX_PROJECTION:								return "matProjection";
			case FXP_MATRIX_WORLD_VIEW_PROJECTION:					return "matWorldViewProjection";
			case FXP_MATRIX_WORLD_INV:								return "matWorldInv";
			case FXP_MATRIX_VIEW_INV:								return "matViewInv";
			case FXP_MATRIX_WORLD_INV_TRANSPOSE:					return "matWorldInvTranspose";
			case FXP_MATRIX_WORLD_VIEW_INV_TRANSPOSE:				return "matWorldViewInvTranspose";
			case FXP_VECTOR_RT_RESOLUTION:							return "vecRTResolution";
			case FXP_VECTOR_RT_RESOLUTION_INV:						return "vecRTResolutionInv";
			case FXP_VECTOR_CAMERA_POSITION:						return "vecCameraPosition";
			case FXP_VECTOR_CAMERA_DIRECTION:						return "vecCameraDirection";
			case FXP_VECTOR_CAMERA_UP:								return "vecCameraUp";
			case FXP_VECTOR_DIRACTIONAL_LIGHT_SOURCE:				return "vecDirectionalLightSource";
			case FXP_COLOR_DIFFUSE:									return "clrDiffuse";
			case FXP_COLOR_SPECULAR:								return "clrSpecular";
			case FXP_COLOR_EMISSIVE:								return "clrEmissive";
			case FXP_COLOR_AMBIENT_LIGHT:							return "clrAmbientLight";
			case FXP_COLOR_DIRECTIONAL_LIGHT:						return "clrDirectionalLight";
			case FXP_TEXTURE_DIFFUSE:								return "texDiffuse";
			case FXP_TEXTURE_NORMAL:								return "texNormal";
			case FXP_TEXTURE_HEIGHT:								return "texHeight";
			case FXP_TEXTURE_SHININESS:								return "texShininess";
			case FXP_TEXTURE_SPECULAR:								return "texSpecular";
			case FXP_TEXTURE_EMISSIVE:								return "texEmissive";
			case FXP_TEXTURE_DEPTH:									return "texDepth";
			case FXP_TEXTURE_CUBEMAP:								return "texCubemap";
			case FXP_TEXTURE_LIGHT_ACC:								return "texLightAcc";
			case FXP_TEXTURE_SSAO:									return "texSSAO";
			case FXP_FLOAT_FRAME_TIME:								return "fltFrameTime";
			case FXP_FLOAT_Z_NEAR:									return "fltZNear";
			case FXP_FLOAT_Z_FAR:									return "fltZFar";
			case FXP_FLOAT_FOV:										return "fltFOV";
			case FXP_FLOAT_ASPECT_RATIO:							return "fltAspectRatio";
			case FXP_FLOAT_SHININESS:								return "fltShininess";
			};
			return 0;
		}

		EEffectParam EEffectParam_FromString(const char* s)
		{
			if(!strcmp(s,	   "matWorld"))								return FXP_MATRIX_WORLD;
			else if(!strcmp(s, "matView"))								return FXP_MATRIX_VIEW;
			else if(!strcmp(s, "matProjection"))						return FXP_MATRIX_PROJECTION;
			else if(!strcmp(s, "matWorldViewProjection"))				return FXP_MATRIX_WORLD_VIEW_PROJECTION;
			else if(!strcmp(s, "matWorldInv"))							return FXP_MATRIX_WORLD_INV;
			else if(!strcmp(s, "matViewInv"))							return FXP_MATRIX_VIEW_INV;
			else if(!strcmp(s, "matWorldInvTranspose"))					return FXP_MATRIX_WORLD_INV_TRANSPOSE;
			else if(!strcmp(s, "matWorldViewInvTranspose"))				return FXP_MATRIX_WORLD_VIEW_INV_TRANSPOSE;
			else if(!strcmp(s, "vecRTResolution"))						return FXP_VECTOR_RT_RESOLUTION;
			else if(!strcmp(s, "vecRTResolutionInv"))					return FXP_VECTOR_RT_RESOLUTION_INV;
			else if(!strcmp(s, "vecCameraPosition"))					return FXP_VECTOR_CAMERA_POSITION;
			else if(!strcmp(s, "vecCameraDirection"))					return FXP_VECTOR_CAMERA_DIRECTION;
			else if(!strcmp(s, "vecCameraUp"))							return FXP_VECTOR_CAMERA_UP;
			else if(!strcmp(s, "vecDirectionalLightSource"))			return FXP_VECTOR_DIRACTIONAL_LIGHT_SOURCE;
			else if(!strcmp(s, "clrDiffuse"))							return FXP_COLOR_DIFFUSE;
			else if(!strcmp(s, "clrSpecular"))							return FXP_COLOR_SPECULAR;
			else if(!strcmp(s, "clrEmissive"))							return FXP_COLOR_EMISSIVE;
			else if(!strcmp(s, "clrAmbientLight"))						return FXP_COLOR_AMBIENT_LIGHT;
			else if(!strcmp(s, "clrDirectionalLight"))					return FXP_COLOR_DIRECTIONAL_LIGHT;
			else if(!strcmp(s, "texDiffuse"))							return FXP_TEXTURE_DIFFUSE;
			else if(!strcmp(s, "texNormal"))							return FXP_TEXTURE_NORMAL;
			else if(!strcmp(s, "texHeight"))							return FXP_TEXTURE_HEIGHT;
			else if(!strcmp(s, "texShininess"))							return FXP_TEXTURE_SHININESS;
			else if(!strcmp(s, "texSpecular"))							return FXP_TEXTURE_SPECULAR;
			else if(!strcmp(s, "texEmissive"))							return FXP_TEXTURE_EMISSIVE;
			else if(!strcmp(s, "texDepth"))								return FXP_TEXTURE_DEPTH;
			else if(!strcmp(s, "texCubemap"))							return FXP_TEXTURE_CUBEMAP;
			else if(!strcmp(s, "texLightAcc"))							return FXP_TEXTURE_LIGHT_ACC;
			else if(!strcmp(s, "texSSAO"))								return FXP_TEXTURE_SSAO;
			else if(!strcmp(s, "fltFrameTime"))							return FXP_FLOAT_FRAME_TIME;
			else if(!strcmp(s, "fltZNear"))								return FXP_FLOAT_Z_NEAR;
			else if(!strcmp(s, "fltZFar"))								return FXP_FLOAT_Z_FAR;
			else if(!strcmp(s, "fltFOV"))								return FXP_FLOAT_FOV;
			else if(!strcmp(s, "fltAspectRatio"))						return FXP_FLOAT_ASPECT_RATIO;
			else if(!strcmp(s, "fltShininess"))							return FXP_FLOAT_SHININESS;

			return (EEffectParam)-1;
		}

		std::ostream& operator << (std::ostream& os, const EEffectParam& fmt)
		{
			const char* s = EEffectParam_ToString(fmt);
			os << (s ? s : "<null>");
			return os;
		}

		std::istream& operator >> (std::istream& is, EEffectParam& fmt)
		{
			std::string s;
			is >> s;
			EEffectParam mp = EEffectParam_FromString(s.c_str());
			if(mp == (EEffectParam)-1)
			{
				is.setstate(is.failbit);
				return is;
			}
			fmt = mp;
			return is;
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////


		const char* EEffectCap_ToString(EEffectCap val)
		{
			switch(val)
			{
			case FXC_DIFFUSE_MAP:		return "DIFFUSE_MAP";
			case FXC_NORMAL_MAP:		return "NORMAL_MAP";
			case FXC_HEIGHT_MAP:		return "HEIGHT_MAP";
			case FXC_SPECULAR_MAP:		return "SPECULAR_MAP";
			case FXC_SHININESS_MAP:		return "SHININESS_MAP";
			case FXC_EMISSIVE_MAP:		return "EMISSIVE_MAP";
			case FXC_CUBE_MAP:			return "CUBE_MAP";
			case FXC_SSAO_MAP:			return "SSAO_MAP";
			case FXC_AMBIENT_LIGHT:		return "AMBIENT_LIGHT";
			case FXC_DIRECTIONAL_LIGHT:	return "DIRECTIONAL_LIGHT";
			};
			return 0;
		}

		EEffectCap EEffectCap_FromString(const char* s)
		{
			if(!strcmp(s,	   "DIFFUSE_MAP"))				return FXC_DIFFUSE_MAP;
			else if(!strcmp(s, "NORMAL_MAP"))				return FXC_NORMAL_MAP;
			else if(!strcmp(s, "HEIGHT_MAP"))				return FXC_HEIGHT_MAP;
			else if(!strcmp(s, "SPECULAR_MAP"))				return FXC_SPECULAR_MAP;
			else if(!strcmp(s, "SHININESS_MAP"))			return FXC_SHININESS_MAP;
			else if(!strcmp(s, "EMISSIVE_MAP"))				return FXC_EMISSIVE_MAP;
			else if(!strcmp(s, "CUBE_MAP"))					return FXC_CUBE_MAP;
			else if(!strcmp(s, "SSAO_MAP"))					return FXC_SSAO_MAP;
			else if(!strcmp(s, "AMBIENT_LIGHT"))			return FXC_AMBIENT_LIGHT;
			else if(!strcmp(s, "DIRECTIONAL_LIGHT"))		return FXC_DIRECTIONAL_LIGHT;

			return (EEffectCap)-1;
		}

		std::ostream& operator << (std::ostream& os, const EEffectCap& fmt)
		{
			const char* s = EEffectCap_ToString(fmt);
			os << (s ? s : "<null>");
			return os;
		}

		std::istream& operator >> (std::istream& is, EEffectCap& fmt)
		{
			std::string s;
			is >> s;
			EEffectCap mp = EEffectCap_FromString(s.c_str());
			if(mp == (EEffectCap)-1)
			{
				is.setstate(is.failbit);
				return is;
			}
			fmt = mp;
			return is;
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace