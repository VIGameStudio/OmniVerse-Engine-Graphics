#pragma once

namespace ove
{
	namespace graphics
	{
		enum class buffer_target
		{
			VERTEX_BUFFER,
			INDEX_BUFFER,
			UNIFORM_BUFFER
		};

		enum class buffer_usage
		{
			STATIC_BUFFER,
			DYNAMIC_BUFFER
		};

		struct buffer_attribs_t
		{
			buffer_target target;
			buffer_usage usage;
		};

		struct buffer_t
		{
		};
	}
}