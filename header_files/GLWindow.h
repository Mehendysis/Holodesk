// GLWindow.h
#pragma once
#include "Window.h"
#include <SDL.h>

using namespace std;

class GLWindow : public Window {
public:
    GLWindow(unsigned int width = 800, unsigned int height = 600, const std::wstring& title = L"Window Title");
    ~GLWindow();

    void GetWindowSize(int* width, int* height) const;

    void SQLEvent(Window* window);

    void Create() override;
    void Close() override;

    void* GetNativeWindowHandle() const override;

    bool ProcessEvents() override;
    GLWindow& GetInstance();
    void SwapBuffers() override;
};