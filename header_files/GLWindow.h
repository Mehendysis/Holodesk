// GLWindow.h
#pragma once
#include "Window.h"
//#include <SDL.h>

//using namespace std;

class GLWindow : public Window {
public:
    //GLWindow(SDL_Window* sdlWindow) : Window(1280, 720, L"Holodesk"), m_sdlWindow(sdlWindow) {};
    //GLWindow() : GLWindow(1280, 720, L"Default Title") {}
    GLWindow() : GLWindow(nullptr, 1280, 720, L"Holodesk") {}
    GLWindow(SDL_Window* sdlWindow, unsigned int width, unsigned int height, const std::wstring& title);
    ~GLWindow();

    SDL_Window* GetSDLWindow() const override;
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
    virtual void Resize(int width, int height) override;
    virtual void Minimize() override;
    virtual void Maximize() override;
    virtual HWND GetWindowHandle() const override;

    SDL_GLContext GetOpenGLContext() const;

    static GLWindow& GetInstance();

private:
    SDL_Window* m_sdlWindow = nullptr;
    SDL_GLContext m_glContext = nullptr;
    unsigned int m_width;
    unsigned int m_height;
    bool m_isCreated;
};