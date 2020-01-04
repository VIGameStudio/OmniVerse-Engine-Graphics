#pragma once

#include <string>

namespace ove
{
	namespace graphics
	{
		enum class shader_target
		{
			VERTEX_SHADER,
			PIXEL_SHADER,
			GEOMETRY_SHADER,
		};

		enum class shader_var
		{
			SVAR_U8,
			SVAR_U16,
			SVAR_U32,

			SVAR_I8,
			SVAR_I16,
			SVAR_I32,

			SVAR_F32,

			SVAR_V2F,
			SVAR_V3F,
			SVAR_V4F,

			SVAR_M22,
			SVAR_M33,
			SVAR_M44,

			SVAR_SAMPLER2D,
			SVAR_CUBEMAP,
		};

		struct shader_attribs_t
		{
			shader_target target = shader_target::VERTEX_SHADER;
			std::string source;
			std::string filepath;
		};

		struct shader_var_t
		{
			std::string name;
			shader_var type;
			void* pData;
		};

		struct shader_resource_t
		{
			std::vector<shader_var_t> variables;
		};

		struct shader_t
		{
		};
	}
}