#pragma once

#include <ove/graphics/renderer/shader.hpp>

#include <GLES2/gl2.h>

namespace ove
{
	namespace graphics
	{
		struct gles_shader_t : public shader_t
		{
			GLuint handle = 0;
		};
	}
}