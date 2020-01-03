#include "ogl3_render_device.hpp"

#include <windows.h>
#include <gl/GL.h>

using namespace ove::core;
using namespace ove::graphics;

void ogl3_render_device_t::setViewport(i32 x, i32 y, i32 width, i32 height)
{
	glViewport(x, y, width, width);
}

void ogl3_render_device_t::clearRenderTarget(f32 r, f32 g, f32 b, f32 a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}