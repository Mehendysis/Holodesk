// GLFramebuffer.h

#pragma once

//#include "GLMemoryWrapper.h"
#include <imgui_impl_opengl3_loader.h>

class GLFramebuffer
{
public:
	GLFramebuffer();
	~GLFramebuffer();
	void CreateFramebuffer();

private:
	void CreateFramebufferObject();
	void CreateOpenGLTexture();
	void BindTextureToFrambuffer(GLuint* texture, unsigned short int* width, unsigned short int* height);
	bool isFramebufferComplete();
	void RenderToFramebufferObject();
	void BindFramebufferObject();

};