// OpenGLWindow.h
#pragma once
#include "Window.h"

using namespace std;

class OpenGLWindow : public Window {
public:
    OpenGLWindow(unsigned int width, unsigned int height, const wstring& title);
    ~OpenGLWindow();

    void Create() override;
    bool ProcessEvents() override;
    void Close() override;

    void* GetNativeWindowHandle() const override;
    HWND GetWindowHandle() const override;

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND m_windowHandle;
    HINSTANCE m_hInstance;
};
