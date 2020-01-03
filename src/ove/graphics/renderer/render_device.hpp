#pragma once

#include <ove/core/util/types.hpp>

namespace ove
{
	namespace graphics
	{
		struct render_device_config_t
		{
			core::u32 target_fps = 0;
		};

		struct render_device_t
		{
		public:
			virtual void setViewport(core::i32 x, core::i32 y, core::i32 width, core::i32 height) = 0;

			virtual void clearRenderTarget(core::f32 r, core::f32 g, core::f32 b, core::f32 a) = 0;
		};
	}
}