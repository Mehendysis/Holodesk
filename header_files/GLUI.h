// GLUI.h
#pragma once
#include "UniqueIDGenerator.h"
#include <imgui.h>

class GLUI
{
public:
	GLUI(std::unique_ptr<SDL_Window> sdlWindow, GLWindow& glWindow, 
		std::unique_ptr<GLRenderer> renderer, std::unique_ptr<GLCamera> camera,
		std::unique_ptr<SDL_GLContext> glContext);

	~GLUI();
	bool IsBackendInitialized() const;
	void CleanUp();
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
	std::unique_ptr<SDL_Window> m_sdlWindow;
	std::unique_ptr<GLRenderer> m_glRenderer;
	//std::unique_ptr<GLRenderer> m_renderer;
	std::unique_ptr<GLCamera> m_glCamera;
	std::unique_ptr<SDL_GLContext> m_glContext;
	GLWindow& m_glWindow;

	void PrivateClean();
	mutable bool m_backendInitialized = false;
	//SDL_GLContext* m_glContext;

	//GLWindow m_glWindow;
	//GLCamera* m_glCamera;
	UniqueIDGenerator m_uniqueIDGenerator;
	UniqueIDGenerator m_idGenerator;
	ImFont* m_font;
	int m_leftPanelID;
	int m_sceneTreeID;
	int m_projectExplorerID;
	int m_viewportID;
	int m_folderContentID;
	int m_inspectorID;
};