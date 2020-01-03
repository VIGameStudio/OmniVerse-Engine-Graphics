#pragma once

#include <ove/graphics/renderer/render_device.hpp>

namespace ove
{
	namespace graphics
	{
		struct ogl3_render_device_t : public render_device_t
		{
		public:
			virtual void setViewport(core::i32 x, core::i32 y, core::i32 width, core::i32 height);

			virtual void clearRenderTarget(core::f32 r, core::f32 g, core::f32 b, core::f32 a);
		};
	}
}