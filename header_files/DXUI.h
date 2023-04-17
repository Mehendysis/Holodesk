//	DXUI.h
#pragma once
#include "UI.h"
#include "DX11Window.h"
#include "DX11Renderer.h"

class DXUI
{
public:
	DXUI(DX11Window* window, DX11Renderer* renderer, Camera* camera)
		: m_window(window),
		m_renderer(renderer),
		m_camera(camera)
	{}

private:
	DX11Window* m_window;
	DX11Renderer* m_renderer;
	Camera* m_camera;
	UniqueIDGenerator m_idGenerator;
	ImFont* m_font;
	int m_leftPanelID;
	int m_sceneTreeID;
	int m_projectExplorerID;
	int m_viewportID;
	int m_folderContentID;
	int m_inspectorID;
};