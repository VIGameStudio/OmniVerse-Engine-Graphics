#pragma once

#include <ove/core/util/types.hpp>
#include <ove/graphics/renderer/buffer.hpp>
#include <ove/graphics/renderer/pipeline_state.hpp>
#include <ove/graphics/renderer/texture.hpp>
#include <ove/graphics/renderer/shader.hpp>

namespace ove
{
	namespace graphics
	{
		enum class clear_flags
		{
			DEPTH_FLAG = 1,
			STENCIL_FLAG = 2,
		};

		struct render_device_config_t
		{
			core::u32 target_fps = 0;
		};

		struct draw_attribs_t
		{
			bool useIndices = false;

			shader_var indexVar = shader_var::SVAR_U32;

			size_t numIndices = 0;
			size_t numVertices = 0;

			size_t bufferStartOffset = 0;
		};

		struct render_device_t
		{
		public:
			virtual void setViewport(core::i32 x, core::i32 y, core::i32 width, core::i32 height) = 0;

			virtual void clearRenderTarget(core::f32 r, core::f32 g, core::f32 b, core::f32 a) = 0;

			virtual void clearDepthStencil(clear_flags flags, core::f32 depth, core::i32 stencil) = 0;

			virtual buffer_t* createBuffer(const buffer_attribs_t& attribs, size_t size, const core::u8* data) = 0;

			virtual void updateBuffer(buffer_t* pBuffer, size_t size, const core::u8* data) = 0;

			virtual texture_t* createTexture(const texture_attribs_t& attribs, size_t size, const core::u8* data) = 0;

			virtual shader_t* createShader(const shader_attribs_t& attribs) = 0;

			virtual pipeline_state_t* createPipelineState(const pipeline_attribs_t& attribs) = 0;

			virtual void setPipelineState(pipeline_state_t* pPipeline) = 0;

			virtual void commitShaderResources(const shader_resource_t& resources) = 0;

			virtual void setVertexBuffers(buffer_t* pBuffer) = 0;

			virtual void setIndexBuffer(buffer_t* pBuffer) = 0;

			virtual void setRenderTarget(const texture_t& renderTarget, const texture_t& depthStencil) = 0;

			virtual void draw(const draw_attribs_t& attribs) = 0;

		protected:
			pipeline_state_t* m_pCurrentPipeline = nullptr;
		};
	}
}