// UIElements.h

#pragma once

#include <imgui.h>

#include "UniqueIDGenerator.h"

class UIElements
{
public:
	void RenderUIElements();

private:
	
	void MainTopMenu();
	void SceneTree(ImVec2 window_size);
	void ProjectExplorer(ImVec2 window_size);
	void Viewport(ImVec2 window_size);
	void FolderContent(ImVec2 window_size);
	void Inspector(ImVec2 window_size);
	void MainWindowsInterface();
	void DockSetting();
	void MutualResizeWindow();
	void CursorOverMutualWindows();

	UniqueIDGenerator m_uniqueIDGenerator;

	unsigned short int m_sceneTreeID;
	unsigned short int m_projectExplorerID;
	unsigned short int m_viewportID;
	unsigned short int m_folderContentID;
	unsigned short int m_inspectorID;
};