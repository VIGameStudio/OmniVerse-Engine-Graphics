#pragma once

#include <ove/graphics/renderer/shader.hpp>

#include <glad/glad.h>

namespace ove
{
	namespace graphics
	{
		struct ogl_shader_t : public shader_t
		{
			GLuint handle = 0;
		};
	}
}