#pragma once

#include <ove/graphics/renderer/render_device.hpp>

namespace ove
{
	namespace graphics
	{
		struct gles_render_device_t : public render_device_t
		{
		public:
			virtual void setViewport(core::i32 x, core::i32 y, core::i32 width, core::i32 height);

			virtual void clearRenderTarget(core::f32 r, core::f32 g, core::f32 b, core::f32 a);

			virtual void clearDepthStencil(clear_flags flags, core::f32 depth, core::i32 stencil);

			virtual buffer_t* createBuffer(const buffer_attribs_t& attribs, size_t size, const core::u8* data);

			virtual void updateBuffer(buffer_t* pBuffer, size_t size, const core::u8* data);

			virtual texture_t* createTexture(const texture_attribs_t& attribs, size_t size, const core::u8* data);

			virtual shader_t* createShader(const shader_attribs_t& attribs);

			virtual pipeline_state_t* createPipelineState(const pipeline_attribs_t& attribs);

			virtual void setPipelineState(pipeline_state_t* pPipeline);

			virtual void commitShaderResources(const shader_resource_t& resources);

			virtual void setVertexBuffers(buffer_t* pBuffer);

			virtual void setIndexBuffer(buffer_t* pBuffer);

			virtual void setRenderTarget(const texture_t& renderTarget, const texture_t& depthStencil);

			virtual void draw(const draw_attribs_t& attribs);
		};
	}
}