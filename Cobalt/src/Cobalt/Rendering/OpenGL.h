#pragma once

#include <glad/glad.h>

#include "Cobalt/Core/Core.h"

///////////////////////////////////////////////////////////////////////////////
// MAIN INCLUDE FILE FOR OPENGL FUNCTIONAILTY
///////////////////////////////////////////////////////////////////////////////

// Wrap this around each OpenGL function call to catch any errors
#define GLCall(x) GLClearError();\
				x;\
				CB_CORE_ASSERT(GLLogCall(), #x);

// Clear all OpenGL errors
static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

// Check for any OpenGL errors
static bool GLLogCall()
{
	while (GLenum error = glGetError())
	{
		CB_CORE_FATAL("OpenGL Error ({0})", error);
		return false;
	}
	return true;
}