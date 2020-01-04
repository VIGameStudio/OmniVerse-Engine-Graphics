#pragma once

#include <ove/graphics/renderer/buffer.hpp>

#include <glad/glad.h>

namespace ove
{
	namespace graphics
	{
		struct ogl_buffer_t : public buffer_t
		{
			GLuint handle = 0;
			GLenum target = 0;
		};
	}
}