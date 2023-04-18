// DX11Window.h
#pragma once

#include <Windows.h>

class DX11Window {
public:
    DX11Window(unsigned short int width, unsigned short int height, char* title);
    ~DX11Window();
    bool ProcessEvents();
    void Close();
    bool Create();
    void* GetNativeWindowHandle() const;
    HWND GetWindowHandle() const;

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HINSTANCE m_hInstance;
    HWND m_windowHandle;
    bool m_shouldClose = false;
};
