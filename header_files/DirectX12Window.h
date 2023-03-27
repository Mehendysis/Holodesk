// DirectX12Window.h
#pragma once
#include <Windows.h>
#include "Window.h"

using namespace std;

class DirectX12Window : public Window {
public:
    DirectX12Window(unsigned int width, unsigned int height, const std::wstring& title);
    ~DirectX12Window();

    virtual void Initialize(HWND hwnd) = 0;

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

    int m_width;
    int m_height;
    wstring m_title;
};