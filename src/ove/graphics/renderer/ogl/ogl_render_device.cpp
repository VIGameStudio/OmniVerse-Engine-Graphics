#include "ogl_render_device.hpp"

#include <iostream>
//#include <windows.h>

#include <glad/glad.h>

#include <ove/graphics/renderer/ogl/ogl_buffer.hpp>
#include <ove/graphics/renderer/ogl/ogl_shader.hpp>
#include <ove/graphics/renderer/ogl/ogl_texture.hpp>
#include <ove/graphics/renderer/ogl/ogl_util.hpp>

using namespace ove::core;
using namespace ove::graphics;

void ogl_render_device_t::setViewport(i32 x, i32 y, i32 width, i32 height)
{
	glViewport(x, y, width, height);
}

void ogl_render_device_t::clearRenderTarget(f32 r, f32 g, f32 b, f32 a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ogl_render_device_t::clearDepthStencil(clear_flags flags, f32 depth, i32 stencil)
{
	GLint mask = 0;

	mask |= ((u32)flags & (u32)clear_flags::DEPTH_FLAG) != 0 ? GL_DEPTH_BUFFER_BIT : 0;
	mask |= ((u32)flags & (u32)clear_flags::STENCIL_FLAG) != 0 ? GL_STENCIL_BUFFER_BIT : 0;

	glClearDepth(depth);
	glClearStencil(stencil);
	glClear(mask);
}

buffer_t* ogl_render_device_t::createBuffer(const buffer_attribs_t& attribs, size_t size, const u8* data)
{
	GLenum target;
	switch (attribs.target)
	{
	case buffer_target::VERTEX_BUFFER:
		target = GL_ARRAY_BUFFER;
		break;

	case buffer_target::INDEX_BUFFER:
		target = GL_ELEMENT_ARRAY_BUFFER;
		break;

	case buffer_target::UNIFORM_BUFFER:
		target = GL_UNIFORM_BUFFER;
		break;

	default:
		throw "Unsupported buffer target flag!";
	}

	GLenum usage;
	switch (attribs.usage)
	{
	case buffer_usage::STATIC_BUFFER:
		usage = GL_STATIC_DRAW;
		break;

	case buffer_usage::DYNAMIC_BUFFER:
		usage = GL_DYNAMIC_DRAW;
		break;

	default:
		throw "Unsupported buffer usage hint!";
	}

	ogl_buffer_t* pBuffer = new ogl_buffer_t();

	glGenBuffers(1, &pBuffer->handle);
	ogl_util::checkForErrors();

	pBuffer->target = target;

	glBindBuffer(target, pBuffer->handle);
	glBufferData(target, size, data, usage);

	ogl_util::checkForErrors();
	return pBuffer;
}

void ogl_render_device_t::updateBuffer(buffer_t* pBuffer, size_t size, const u8* data)
{
	ogl_buffer_t* pGlBuffer = static_cast<ogl_buffer_t*>(pBuffer);
	ogl_util::checkForErrors();

	//GL.BindBuffer(glesBuffer.Target, glesBuffer.Handle);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->handle);
	glBufferSubData(pGlBuffer->target, 0, size, data);

	ogl_util::checkForErrors();
}

texture_t* ogl_render_device_t::createTexture(const texture_attribs_t& attribs, size_t size, const u8* data)
{
	ogl_texture_t* pTexture = new ogl_texture_t();
	return pTexture;

	/*Gles3Texture texture = new Gles3Texture(GL.GenTexture());

	switch (meta.Type)
	{
		case TextureType.Texture2D:
			GL.BindTexture(TextureTarget.Texture2D, texture.Handle);
			Gles3Utils.CheckForErrors();

			switch (meta.Format)
			{
				case TextureFormat.RGB8:
					GL.PixelStore(PixelStoreParameter.UnpackAlignment, 1);
					GL.PixelStore(PixelStoreParameter.UnpackRowLength, meta.Width);
					GL.TexImage2D(TextureTarget2d.Texture2D, 0, TextureComponentCount.Rgb, meta.Width, meta.Height, 0, PixelFormat.Rgb, PixelType.UnsignedByte, data[0]);
					GL.GenerateMipmap(TextureTarget.Texture2D);
					break;

				case TextureFormat.RGBA8:
					GL.PixelStore(PixelStoreParameter.UnpackAlignment, 1);
					GL.PixelStore(PixelStoreParameter.UnpackRowLength, meta.Width);
					GL.TexImage2D(TextureTarget2d.Texture2D, 0, TextureComponentCount.Rgba, meta.Width, meta.Height, 0, PixelFormat.Rgba, PixelType.UnsignedByte, data[0]);
					GL.GenerateMipmap(TextureTarget.Texture2D);
					break;

				case TextureFormat.FramebufferDepth32f:
					if (data != null)
					{
						throw new InvalidOperationException("Data must be null when creating a depth stencil target texture.");
					}
					GL.TexImage2D(TextureTarget2d.Texture2D, 0, TextureComponentCount.DepthComponent32f, meta.Width, meta.Height, 0, PixelFormat.DepthComponent, PixelType.Float, IntPtr.Zero);
					//GL.TexImage2D(TextureTarget2d.Texture2D, 0, TextureComponentCount.Rgba, meta.Width, meta.Height, 0, PixelFormat.Rgba, PixelType.UnsignedByte, data);

					texture.FrameBuffer = GL.GenFramebuffer();
					//texture.RenderBuffer = GL.GenRenderbuffer();

					GL.BindFramebuffer(FramebufferTarget.Framebuffer, texture.FrameBuffer);
					GL.FramebufferTexture2D(FramebufferTarget.Framebuffer, FramebufferAttachment.DepthAttachment, TextureTarget2d.Texture2D, texture.Handle, 0);

					//GL.BindRenderbuffer(RenderbufferTarget.Renderbuffer, texture.RenderBuffer);
					//GL.RenderbufferStorage(RenderbufferTarget.Renderbuffer, RenderbufferInternalFormat.DepthComponent16, meta.Width, meta.Height);
					//GL.BindFramebuffer(FramebufferTarget.Framebuffer, texture.FrameBuffer);
					//GL.FramebufferRenderbuffer(FramebufferTarget.Framebuffer, FramebufferAttachment.DepthAttachment, RenderbufferTarget.Renderbuffer, texture.RenderBuffer);
					//GL.FramebufferTexture2D(FramebufferTarget.Framebuffer, FramebufferAttachment.ColorAttachment0, TextureTarget2d.Texture2D, texture.Handle, 0);

					var code = GL.CheckFramebufferStatus(FramebufferTarget.Framebuffer);
					if (code != FramebufferErrorCode.FramebufferComplete)
					{
						throw new Exception("Frame buffer is not complete!");
					}
					break;

				default: throw new Exception($"Texture format {meta.Format} is not supported!");
			}
			Gles3Utils.CheckForErrors();

			// set the texture wrapping parameters
			GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int)Gles3Utils.GetWrapMode(meta.WrapS));
			GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int)Gles3Utils.GetWrapMode(meta.WrapT));

			// set texture filtering parameters
			GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)Gles3Utils.GetTextureMinFilter(meta.MinFilter));
			GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)Gles3Utils.GetTextureMagFilter(meta.MagFilter));

			GL.BindTexture(TextureTarget.Texture2D, 0);
			GL.BindFramebuffer(FramebufferTarget.Framebuffer, 0);
			break;

		case TextureType.CubeMap:
			GL.BindTexture(TextureTarget.TextureCubeMap, texture.Handle);
			Gles3Utils.CheckForErrors();

			GL.PixelStore(PixelStoreParameter.UnpackAlignment, 1);
			GL.PixelStore(PixelStoreParameter.UnpackRowLength, meta.Width);

			TextureComponentCount textureComponents;
			PixelFormat pixelFormat;
			switch (meta.Format)
			{
				case TextureFormat.RGB8:
					textureComponents = TextureComponentCount.Rgb;
					pixelFormat = PixelFormat.Rgb;
					break;

				case TextureFormat.RGBA8:
					textureComponents = TextureComponentCount.Rgba;
					pixelFormat = PixelFormat.Rgba;
					break;

				default: throw new NotSupportedException($"Texture format {meta.Format} is not supported for cubemaps!");
			}

			for (int i = 0; i < data.Count; i++)
			{
				GL.TexImage2D(TextureTarget2d.TextureCubeMapPositiveX + i, 0, textureComponents, meta.Width, meta.Height, 0, pixelFormat, PixelType.UnsignedByte, data[i]);
			}

			// set the texture wrapping parameters
			GL.TexParameter(TextureTarget.TextureCubeMap, TextureParameterName.TextureWrapS, (int)Gles3Utils.GetWrapMode(meta.WrapS));
			GL.TexParameter(TextureTarget.TextureCubeMap, TextureParameterName.TextureWrapT, (int)Gles3Utils.GetWrapMode(meta.WrapT));
			GL.TexParameter(TextureTarget.TextureCubeMap, TextureParameterName.TextureWrapR, (int)Gles3Utils.GetWrapMode(meta.WrapR));

			// set texture filtering parameters
			GL.TexParameter(TextureTarget.TextureCubeMap, TextureParameterName.TextureMinFilter, (int)Gles3Utils.GetTextureMinFilter(meta.MinFilter));
			GL.TexParameter(TextureTarget.TextureCubeMap, TextureParameterName.TextureMagFilter, (int)Gles3Utils.GetTextureMagFilter(meta.MagFilter));
			break;

		default: throw new NotSupportedException($"Texture type {meta.Type} is not supported!");
	}

	Gles3Utils.CheckForErrors();
	return texture;*/
}

shader_t* ogl_render_device_t::createShader(const shader_attribs_t& attribs)
{
	GLenum target;
	switch (attribs.target)
	{
	case shader_target::VERTEX_SHADER:
		target = GL_VERTEX_SHADER;
		break;

	case shader_target::PIXEL_SHADER:
		target = GL_FRAGMENT_SHADER;
		break;

	case shader_target::GEOMETRY_SHADER:
		target = GL_GEOMETRY_SHADER;
		break;

	default: throw "Unsupported shader target!";
	}

	ogl_shader_t* pShader = new ogl_shader_t();
	pShader->handle = glCreateShader(target);

	/*if (attribs.source.size() == 0)
	{
		if (attribs.filepath.size() == 0)
		{
			throw "Failed to create shader with no source or filepath!";
		}

		if (!ogl3_util::parseShaderFile(attribs.source, attribs.filepath, m_resourceLoader))
		{
			throw "Failed to parse shader file!";
		}
	}*/

	// Load the source of the vertex shader and compile it.
	const char* src = attribs.source.c_str();
	glShaderSource(pShader->handle, 1, &src, NULL);
	glCompileShader(pShader->handle);

	int success;
	char info[1024];
	glGetShaderiv(pShader->handle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(pShader->handle, 1024, NULL, info);
		std::cerr << "ERROR::SHADER_COMPILATION_ERROR\n" << info << std::endl;
	}

	ogl_util::checkForErrors();
	return pShader;
}

pipeline_state_t* ogl_render_device_t::createPipelineState(const pipeline_attribs_t& attribs)
{
	ogl_util::checkForErrors();

	// Create the shader program, attach the vertex and fragment shaders and link the program.
	pipeline_state_t* pPipeline = new pipeline_state_t();
	pPipeline->attribs = attribs;

	ogl_shader_t* pProgram = new ogl_shader_t();
	pPipeline->pProgram = pProgram;

	pProgram->handle = glCreateProgram();
	ogl_util::checkForErrors();

	ogl_shader_t* shaders[3];
	shaders[0] = static_cast<ogl_shader_t*>(attribs.pVertexShader);
	shaders[1] = static_cast<ogl_shader_t*>(attribs.pPixelShader);
	shaders[2] = static_cast<ogl_shader_t*>(attribs.pGeometryShader);

	for (u8 i = 0; i < 3; ++i)
	{
		if (shaders[i] != nullptr)
		{
			glAttachShader(pProgram->handle, shaders[i]->handle);
			ogl_util::checkForErrors();
		}
	}

	for (size_t i = 0; i < attribs.inputLayout.size(); ++i)
	{
		const layout_elem_t& elem = attribs.inputLayout[i];
		glBindAttribLocation(pProgram->handle, elem.location, elem.name.c_str());
	}
	ogl_util::checkForErrors();

	glLinkProgram(pProgram->handle);
	ogl_util::checkForErrors();

	for (u8 i = 0; i < 3; ++i)
	{
		if (shaders[i] != nullptr)
		{
			glDeleteShader(shaders[i]->handle);
			ogl_util::checkForErrors();
		}
	}

	int success;
	char info[1024];
	glGetProgramiv(pProgram->handle, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(pProgram->handle, 1024, NULL, info);
		std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << info << std::endl;
	}

	ogl_util::checkForErrors();
	return pPipeline;
}

void ogl_render_device_t::setPipelineState(pipeline_state_t* pPipeline)
{
	m_pCurrentPipeline = pPipeline;

	// Depth testing.
	if (m_pCurrentPipeline->attribs.enableDepth)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_FALSE);
	}

	ogl_util::checkForErrors();

	// Blending.
	if (m_pCurrentPipeline->attribs.enableBlend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	ogl_util::checkForErrors();

	// Face culling.
	if (m_pCurrentPipeline->attribs.enableFaceCull)
	{
		glEnable(GL_CULL_FACE);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	ogl_util::checkForErrors();

	switch (m_pCurrentPipeline->attribs.cullMode)
	{
	case cull_mode::CULL_NONE:
		glCullFace(GL_FRONT_AND_BACK);
		break;

	case cull_mode::CULL_BACK:
		glCullFace(GL_BACK);
		break;

	case cull_mode::CULL_FRONT:
		glCullFace(GL_FRONT);
		break;
	}

	ogl_util::checkForErrors();

	// Front-face winding.
	if (m_pCurrentPipeline->attribs.frontFaceCCW)
	{
		glFrontFace(GL_CCW);
	}
	else
	{
		glFrontFace(GL_CW);
	}

	ogl_util::checkForErrors();
}

void ogl_render_device_t::commitShaderResources(const shader_resource_t& resources)
{
	ogl_shader_t* pProgram = static_cast<ogl_shader_t*>(m_pCurrentPipeline->pProgram);
	glUseProgram(pProgram->handle);

	int samplers = 0;
	for (size_t i = 0; i < resources.variables.size(); ++i)
	{
		const shader_var_t& var = resources.variables[i];

		GLint location = glGetUniformLocation(pProgram->handle, var.name.c_str());
		switch (var.type)
		{
		case shader_var::SVAR_I32:
			glUniform1i(location, *static_cast<i32*>(var.pData));
			break;

		case shader_var::SVAR_F32:
			glUniform1f(location, *static_cast<f32*>(var.pData));
			break;

		case shader_var::SVAR_V2F:
			glUniform1fv(location, 2, static_cast<f32*>(var.pData));
			break;

		case shader_var::SVAR_V3F:
			glUniform1fv(location, 3, static_cast<f32*>(var.pData));
			break;

		case shader_var::SVAR_V4F:
			glUniform1fv(location, 4, static_cast<f32*>(var.pData));
			break;

		case shader_var::SVAR_M22:
			glUniformMatrix2fv(location, 1, false, static_cast<f32*>(var.pData));
			break;

		case shader_var::SVAR_M33:
			glUniformMatrix3fv(location, 1, false, static_cast<f32*>(var.pData));
			break;

		case shader_var::SVAR_M44:
			glUniformMatrix4fv(location, 1, false, static_cast<f32*>(var.pData));
			break;

			/*case SVAR_SAMPLER2D:
				switch (data)
				{
					case ITexture texture:
						GL.ActiveTexture(TextureUnit.Texture0 + samplers);
						GL.BindTexture(TextureTarget.Texture2D, ((Gles3Texture)texture).Handle);
						GL.Uniform1(handle, samplers);
						samplers++;
						break;

					case ITexture[] textures:
						//BindMultiSampler2D(textures); break;
						throw new NotSupportedException("TODO - Feature is currently not implemented!");
				}
				break;

			case SVAR_CUBEMAP:
				GL.ActiveTexture(TextureUnit.Texture0 + samplers);
				GL.BindTexture(TextureTarget.TextureCubeMap, ((Gles3Texture)data).Handle);
				GL.Uniform1(handle, samplers);
				samplers++;
				break;*/

		default:
			throw "Shader variable type not supported!";
		}

		ogl_util::checkForErrors();
	}
}

void ogl_render_device_t::setVertexBuffers(buffer_t* pBuffer)
{
	ogl_buffer_t* pVertexBuffer = static_cast<ogl_buffer_t*>(pBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, pVertexBuffer->handle);

	i32 stride = 0;
	for (size_t i = 0; i < m_pCurrentPipeline->attribs.inputLayout.size(); ++i)
	{
		const layout_elem_t& elem = m_pCurrentPipeline->attribs.inputLayout[i];
		stride += elem.count * sizeof(f32);
	}

	i32 offset = 0;
	for (size_t i = 0; i < m_pCurrentPipeline->attribs.inputLayout.size(); ++i)
	{
		const layout_elem_t& elem = m_pCurrentPipeline->attribs.inputLayout[i];
		glVertexAttribPointer(elem.location, elem.count, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(elem.location);

		offset += elem.count * sizeof(f32);
	}

	ogl_util::checkForErrors();
}

void ogl_render_device_t::setIndexBuffer(buffer_t* pBuffer)
{
	ogl_buffer_t* pIndexBuffer = static_cast<ogl_buffer_t*>(pBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->handle);

	ogl_util::checkForErrors();
}

void ogl_render_device_t::setRenderTarget(const texture_t& renderTarget, const texture_t& depthStencil)
{
	/*var glesRenderTarget = (Gles3Texture)renderTarget;
	var glesDepthStencil = (Gles3Texture)depthStencil;

	if (glesRenderTarget != null)
	{
		// TODO: Add support for render target frame buffer.
		throw new NotSupportedException();
	}

	if (glesDepthStencil != null)
	{
		GL.BindFramebuffer(FramebufferTarget.Framebuffer, glesDepthStencil.FrameBuffer);
		GL.ColorMask(true, false, false, false);
	}

	if (glesRenderTarget == null && glesDepthStencil == null)
	{
		GL.BindFramebuffer(FramebufferTarget.Framebuffer, 0);
		GL.ColorMask(true, true, true, true);
	}

	Gles3Utils.CheckForErrors();*/
}

void ogl_render_device_t::draw(const draw_attribs_t& attribs)
{
	GLenum mode;
	switch (m_pCurrentPipeline->attribs.topology)
	{
	case topology_mode::MESH_POINTS:
		mode = GL_POINTS;
		break;

	case topology_mode::MESH_LINES:
		mode = GL_LINES;
		break;

	case topology_mode::MESH_TRIANGLE_LIST:
		mode = GL_TRIANGLES;
		break;

	default:
		throw "Primitive topology mode is not supported!";
	}

	if (attribs.useIndices)
	{
		GLenum drawType;
		switch (attribs.indexVar)
		{
		case shader_var::SVAR_U8:
			drawType = GL_UNSIGNED_BYTE;
			break;

		case shader_var::SVAR_U16:
			drawType = GL_UNSIGNED_SHORT;
			break;

		case shader_var::SVAR_U32:
			drawType = GL_UNSIGNED_INT;
			break;

		default:
			throw "Variable type is not supported as index type!";
		}

		glDrawElements(mode, attribs.numIndices, drawType, 0);
	}
	else
	{
		glDrawArrays(mode, attribs.bufferStartOffset, attribs.numVertices);
	}
}