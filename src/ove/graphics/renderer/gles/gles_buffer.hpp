#pragma once

#include <ove/graphics/renderer/buffer.hpp>

#include <GLES2/gl2.h>

namespace ove
{
	namespace graphics
	{
		struct gles_buffer_t : public buffer_t
		{
			GLuint handle = 0;
			GLenum target = 0;
		};
	}
}