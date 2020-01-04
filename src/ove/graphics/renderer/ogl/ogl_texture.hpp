#pragma once

#include <ove/graphics/renderer/texture.hpp>

#include <glad/glad.h>

namespace ove
{
	namespace graphics
	{
		struct ogl_texture_t : public texture_t
		{
			GLuint handle = 0;
		};
	}
}