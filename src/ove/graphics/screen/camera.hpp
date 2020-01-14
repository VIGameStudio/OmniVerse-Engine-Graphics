#pragma once

#include <ove/math/vec.hpp>
#include <ove/math/quat.hpp>
#include <ove/math/mat.hpp>

namespace ove
{
	namespace graphics
	{
		struct camera_t
		{
			math::vec3f position;
			math::quatf rotation;
			math::mat4f projection;
		};
	}
}