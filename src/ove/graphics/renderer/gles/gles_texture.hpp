#pragma once

#include <ove/graphics/renderer/texture.hpp>

#include <GLES2/gl2.h>

namespace ove
{
	namespace graphics
	{
		struct gles_texture_t : public texture_t
		{
			GLuint handle = 0;
		};
	}
}