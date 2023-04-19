// GLUI.h
#pragma once
#include "UniqueIDGenerator.h"
#include <imgui.h>

class GLUI
{
public:
	GLUI(GLWindow* glWindow, GLRenderer* glRenderer, GLCamera* glCamera);
	~GLUI();
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

	bool IsBackendInitialized() const ;
	void SetBackendInitialized(bool initialized);

	void CallPrivateClean();

private:
	mutable bool m_backendInitialized = false;
	GLWindow* m_glWindow;
	GLRenderer* m_glRenderer;
	GLCamera* m_glCamera;
	UniqueIDGenerator m_idGenerator;
	ImFont* m_font;
	int m_leftPanelID;
	int m_sceneTreeID;
	int m_projectExplorerID;
	int m_viewportID;
	int m_folderContentID;
	int m_inspectorID;

	UniqueIDGenerator m_uniqueIDGenerator;
};