// GLUI.h
#pragma once

#include "GLWindow.h"
#include "GLRenderer.h"

#include <imgui.h>


class GLUI
{
public:
	GLUI(GLWindow* glWindow, SDL_GLContext* glContext);
	~GLUI();
	bool IsBackendInitialized() const;
	void CleanUp();
	void SetRenderer(GLRenderer* glRenderer);
	void Render();
	void Initialize();
	void SetBackendInitialized(bool initialized);
	void CallPrivateClean();

private:
	SDL_GLContext* m_glContext;
	GLWindow* m_glWindow;

	void PrivateClean();
	GLRenderer* m_glRenderer;

};