// GLWindow.h
#pragma once
#include "Window.h"
//#include <SDL.h>

//using namespace std;

class GLWindow : public Window {
public:
    GLWindow(int windowWidth, int windowHeight, const std::wstring& title);
    ~GLWindow();

    SDL_Window* GetSDLWindow() const override;
    virtual bool Create() override;
    virtual bool ProcessEvents() override;
    virtual void Close() override;
    virtual void SQLEvent() override;
    virtual void SwapBuffers() override;
    virtual void* GetNativeWindowHandle() const override;
    virtual void GetWindowSize(int* width, int* height) const override;
    virtual void SetWidth(unsigned int width) override;
    virtual void SetHeight(unsigned int height) override;
    virtual void OnResize(int width, int height);
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