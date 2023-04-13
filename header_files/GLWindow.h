// GLWindow.h
#pragma once
#include "Window.h"
#include <SDL.h>

using namespace std;

class GLWindow : public Window {
public:
    GLWindow(SDL_Window* sdlWindow);
    ~GLWindow();

    SDL_Window* GetSDLWindow() const;
    virtual bool Create() override;
    virtual bool ProcessEvents() override;
    virtual void Close() override;
    virtual void SQLEvent(Window* window) override;
    virtual void SwapBuffers() override;
    virtual void* GetNativeWindowHandle() const override;
    virtual void GetWindowSize(int* width, int* height) const override;
    virtual void OnResize(int width, int height);
    virtual void SetWidth(unsigned int width) { m_width = width; }
    virtual void SetHeight(unsigned int height) { m_height = height; }

    static GLWindow& GetInstance();

private:
    SDL_Window* m_sdlWindow = nullptr;
    SDL_GLContext m_glContext = nullptr;
    unsigned int width_;
    unsigned int height_;
    bool isCreated_;
};