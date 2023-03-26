// DirectX11Window.h
#pragma once
#include "Window.h"
#include <Windows.h>

class DirectX11Window : public Window {
public:
	DirectX11Window(unsigned int width, unsigned int height, const std::wstring& title);
	virtual ~DirectX11Window();
	virtual bool ProcessEvents() override;
	virtual void Close() override;
	virtual void* GetNativeWindowHandle() const override;
	virtual HWND GetWindowHandle() const override;
private:
	void Create();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HINSTANCE m_hInstance;
	HWND m_windowHandle;
	bool m_shouldClose = false;
};