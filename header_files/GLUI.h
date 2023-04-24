// GLUI.h
#pragma once
#include "UniqueIDGenerator.h"
#include "GLWindow.h"
#include "GLRenderer.h"

#include <imgui.h>


class GLUI
{
public:
	//GLUI(const std::shared_ptr<const SDL_Window>& sdlWindow, const GLWindow& glWindow, GLRenderer& glRenderer, GLCamera& glCamera, SDL_GLContext& glContext);
	//GLUI(GLWindow* window, SDL_GLContext* glContext);
	GLUI(GLWindow* glWindow, SDL_GLContext* glContext);
	~GLUI();
	bool IsBackendInitialized() const;
	void CleanUp();
	void SetRenderer(GLRenderer* glRenderer);
	void MainTopMenu();
	void MutualResizeWindow();
	void MainWindowsInterface();
	void RenderUIElements();
	void CursorOverMutualWindows();
	void DockSetting();
	void SceneTree(ImVec2 window_size);
	void ProjectExplorer(ImVec2 window_size);
	void Viewport(ImVec2 window_size);
	void FolderContent(ImVec2 window_size);
	void Inspector(ImVec2 window_size);
	void Render();
	void Initialize();
	void SetBackendInitialized(bool initialized);
	void CallPrivateClean();

private:
	//std::shared_ptr<const SDL_Window> m_sdlWindow;
	
	//GLRenderer& m_glRenderer;
	//GLCamera& m_glCamera;
	//SDL_GLContext m_glContext;
	//SDL_Window* m_sdlWindow;
	SDL_GLContext* m_glContext;
	GLWindow* m_glWindow;

	void PrivateClean();
	//mutable bool m_backendInitialized = false;
	UniqueIDGenerator m_uniqueIDGenerator;
	//UniqueIDGenerator m_idGenerator;
	//ImFont* m_font;
	//int m_leftPanelID;
	GLRenderer* m_glRenderer;
	int m_sceneTreeID;
	int m_projectExplorerID;
	int m_viewportID;
	int m_folderContentID;
	int m_inspectorID;
};