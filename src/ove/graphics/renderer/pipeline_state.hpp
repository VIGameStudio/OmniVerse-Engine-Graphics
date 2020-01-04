#pragma once

#include <string>
#include <vector>

#include <ove/graphics/renderer/shader.hpp>

namespace ove
{
	namespace graphics
	{
		enum class cull_mode
		{
			CULL_NONE,
			CULL_FRONT,
			CULL_BACK,
		};

		enum class topology_mode
		{
			MESH_POINTS,
			MESH_LINES,
			MESH_TRIANGLE_LIST,
		};

		struct layout_elem_t
		{
			std::string name = "";
			size_t location = 0;
			core::u8 count = 0;
		};

		struct pipeline_attribs_t
		{
			shader_t* pVertexShader = nullptr;
			shader_t* pPixelShader = nullptr;
			shader_t* pGeometryShader = nullptr;

			std::vector<layout_elem_t> inputLayout;

			bool enableDepth = false;
			bool enableBlend = false;
			bool enableFaceCull = false;
			bool frontFaceCCW = true;
			cull_mode cullMode = cull_mode::CULL_NONE;

			topology_mode topology = topology_mode::MESH_TRIANGLE_LIST;
		};

		struct pipeline_state_t
		{
			pipeline_attribs_t attribs;

			shader_t* pProgram = nullptr;

			//virtual void getStaticShaderVariable(shader_mode mode, const std::string& name) = 0;

			//virtual  const shader_resource_t& createShaderResource() = 0;
		};
	}
}