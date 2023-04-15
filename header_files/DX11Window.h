// DX11Window.h
#pragma once
#include "Window.h"
#include <Windows.h>

class DX11Window : public Window {
public:
    DX11Window(unsigned int width, unsigned int height, const std::wstring& title);
    virtual ~DX11Window();
    virtual bool ProcessEvents() override;
    virtual void Close() override;
    virtual bool Create() override;
    virtual void* GetNativeWindowHandle() const override;
    virtual HWND GetWindowHandle() const;
private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HINSTANCE m_hInstance;
    HWND m_windowHandle;
    bool m_shouldClose = false;
};
