#pragma once

#include <GLES2/gl2.h>

namespace ove
{
	namespace graphics
	{
		namespace gles_util
		{
			void checkForErrors()
			{
				GLenum error = glGetError();
				if (error != GL_NO_ERROR)
				{
					switch (error)
					{
					case GL_INVALID_ENUM:
						throw "GL error: Invalid enum!";
						break;

					case GL_INVALID_VALUE:
						throw "GL error: Invalid value!";
						break;

					case GL_INVALID_OPERATION:
						throw "GL error: Invalid operation!";
						break;

					case GL_INVALID_FRAMEBUFFER_OPERATION:
						throw "GL error: Invalid framebuffer operation!";
						break;

					case GL_OUT_OF_MEMORY:
						throw "GL error: Out of memory!";
						break;
					}
				}
			}

			//bool parseShaderFile(std::string& source, const std::string& filepath, const resource_loader_t& loader);
		}
	}
}