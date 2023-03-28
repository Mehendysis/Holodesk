// OpenGLWindow.h
#pragma once
#include "Window.h"
#include <SDL.h>

using namespace std;

class OpenGLWindow : public Window {
public:
    OpenGLWindow(unsigned int width = 800, unsigned int height = 600, const std::wstring& title = L"Window Title");
    ~OpenGLWindow();

    void GetWindowSize(int* width, int* height) const;

    void Create() override;
    void Close() override;

    void* GetNativeWindowHandle() const override;

    bool ProcessEvents() override;
    void SwapBuffers() override;
};