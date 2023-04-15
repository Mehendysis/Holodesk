// GLUI.h
#pragma once
#include "UI.h"

class GLUI : public UI
{
public:
	GLUI(GLWindow* glWindow, GLRenderer* glRenderer, GLCamera* glCamera);
	~GLUI() override;
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
	void Render() override;

	void Initialize();

private:
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