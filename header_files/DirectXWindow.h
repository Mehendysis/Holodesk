// DirectXWindow.h
#pragma once
#include <Windows.h>
#include "Window.h"

using namespace std;

class DirectXWindow : public Window {
public:
    DirectXWindow(unsigned int width, unsigned int height, const wstring& title);
    ~DirectXWindow();

    void Create() override;
    bool ProcessEvents() override;
    void Close() override;

    void* GetNativeWindowHandle() const override;
    HWND GetWindowHandle() const override;

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND m_windowHandle;
    HINSTANCE m_hInstance;
    bool m_shouldClose;
};