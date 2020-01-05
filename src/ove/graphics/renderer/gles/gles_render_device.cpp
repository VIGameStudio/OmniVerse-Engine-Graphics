#include "gles_render_device.hpp"

#include <iostream>

#include <GLES2/gl2.h>
//#include <glad/glad.h>

#include <ove/graphics/renderer/gles/gles_buffer.hpp>
#include <ove/graphics/renderer/gles/gles_shader.hpp>
#include <ove/graphics/renderer/gles/gles_texture.hpp>
#include <ove/graphics/renderer/gles/gles_util.hpp>

using namespace ove::core;
using namespace ove::graphics;

void gles_render_device_t::setViewport(i32 x, i32 y, i32 width, i32 height)
{
	glViewport(x, y, width, height);
}

void gles_render_device_t::clearRenderTarget(f32 r, f32 g, f32 b, f32 a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void gles_render_device_t::clearDepthStencil(clear_flags flags, f32 depth, i32 stencil)
{
	GLint mask = 0;

	mask |= ((u32)flags & (u32)clear_flags::DEPTH_FLAG) != 0 ? GL_DEPTH_BUFFER_BIT : 0;
	mask |= ((u32)flags & (u32)clear_flags::STENCIL_FLAG) != 0 ? GL_STENCIL_BUFFER_BIT : 0;

	//glClearDepth(depth);
	glClearStencil(stencil);
	glClear(mask);
}

buffer_t* gles_render_device_t::createBuffer(const buffer_attribs_t& attribs, size_t size, const u8* data)
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

	gles_buffer_t* pBuffer = new gles_buffer_t();

	glGenBuffers(1, &pBuffer->handle);
	gles_util::checkForErrors();

	pBuffer->target = target;

	glBindBuffer(target, pBuffer->handle);
	glBufferData(target, size, data, usage);

	gles_util::checkForErrors();
	return pBuffer;
}

void gles_render_device_t::updateBuffer(buffer_t* pBuffer, size_t size, const u8* data)
{
	gles_buffer_t* pGlBuffer = static_cast<gles_buffer_t*>(pBuffer);
	gles_util::checkForErrors();

	//GL.BindBuffer(glesBuffer.Target, glesBuffer.Handle);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->handle);
	glBufferSubData(pGlBuffer->target, 0, size, data);

	gles_util::checkForErrors();
}

texture_t* gles_render_device_t::createTexture(const texture_attribs_t& attribs, size_t size, const u8* data)
{
	gles_texture_t* pTexture = new gles_texture_t();
	return pTexture;
}

shader_t* gles_render_device_t::createShader(const shader_attribs_t& attribs)
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

	default: throw "Unsupported shader target!";
	}

	gles_shader_t* pShader = new gles_shader_t();
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

	gles_util::checkForErrors();
	return pShader;
}

pipeline_state_t* gles_render_device_t::createPipelineState(const pipeline_attribs_t& attribs)
{
	gles_util::checkForErrors();

	// Create the shader program, attach the vertex and fragment shaders and link the program.
	pipeline_state_t* pPipeline = new pipeline_state_t();
	pPipeline->attribs = attribs;

	gles_shader_t* pProgram = new gles_shader_t();
	pPipeline->pProgram = pProgram;

	pProgram->handle = glCreateProgram();
	gles_util::checkForErrors();

	gles_shader_t* shaders[3];
	shaders[0] = static_cast<gles_shader_t*>(attribs.pVertexShader);
	shaders[1] = static_cast<gles_shader_t*>(attribs.pPixelShader);
	shaders[2] = static_cast<gles_shader_t*>(attribs.pGeometryShader);

	for (u8 i = 0; i < 3; ++i)
	{
		if (shaders[i] != nullptr)
		{
			glAttachShader(pProgram->handle, shaders[i]->handle);
			gles_util::checkForErrors();
		}
	}

	for (size_t i = 0; i < attribs.inputLayout.size(); ++i)
	{
		const layout_elem_t& elem = attribs.inputLayout[i];
		glBindAttribLocation(pProgram->handle, elem.location, elem.name.c_str());
	}
	gles_util::checkForErrors();

	glLinkProgram(pProgram->handle);
	gles_util::checkForErrors();

	for (u8 i = 0; i < 3; ++i)
	{
		if (shaders[i] != nullptr)
		{
			glDeleteShader(shaders[i]->handle);
			gles_util::checkForErrors();
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

	gles_util::checkForErrors();
	return pPipeline;
}

void gles_render_device_t::setPipelineState(pipeline_state_t* pPipeline)
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

	gles_util::checkForErrors();

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

	gles_util::checkForErrors();

	// Face culling.
	if (m_pCurrentPipeline->attribs.enableFaceCull)
	{
		glEnable(GL_CULL_FACE);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	gles_util::checkForErrors();

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

	gles_util::checkForErrors();

	// Front-face winding.
	if (m_pCurrentPipeline->attribs.frontFaceCCW)
	{
		glFrontFace(GL_CCW);
	}
	else
	{
		glFrontFace(GL_CW);
	}

	gles_util::checkForErrors();
}

void gles_render_device_t::commitShaderResources(const shader_resource_t& resources)
{
	gles_shader_t* pProgram = static_cast<gles_shader_t*>(m_pCurrentPipeline->pProgram);
	glUseProgram(pProgram->handle);

	//int samplers = 0;
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

		default:
			throw "Shader variable type not supported!";
		}

		gles_util::checkForErrors();
	}
}

void gles_render_device_t::setVertexBuffers(buffer_t* pBuffer)
{
	gles_buffer_t* pVertexBuffer = static_cast<gles_buffer_t*>(pBuffer);
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

	gles_util::checkForErrors();
}

void gles_render_device_t::setIndexBuffer(buffer_t* pBuffer)
{
	gles_buffer_t* pIndexBuffer = static_cast<gles_buffer_t*>(pBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->handle);

	gles_util::checkForErrors();
}

void gles_render_device_t::setRenderTarget(const texture_t& renderTarget, const texture_t& depthStencil)
{
}

void gles_render_device_t::draw(const draw_attribs_t& attribs)
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