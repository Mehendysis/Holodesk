// Window.h
#pragma once

#include <string>
#include <SDL.h>
#include <Windows.h>

class GLWindow;

class Window {
public:
    Window(unsigned int width = 1280, unsigned int height = 720, const std::wstring& title = L"Holodesk");
    void SetWindowSize(unsigned int width, unsigned int height);
    virtual ~Window() {}

    virtual SDL_Window* GetSDLWindow() const { return nullptr; }
    void CleanUp();
    virtual bool Create() = 0;
    virtual void Resize(int width, int height) = 0;
    virtual void Minimize() = 0;
    virtual void Maximize() = 0;
    virtual void SwapBuffers() = 0;
    virtual bool ProcessEvents() = 0;
    virtual void Close() = 0;
    virtual void SQLEvent(Window* window) = 0;
    virtual void* GetNativeWindowHandle() const = 0;
    virtual HWND GetWindowHandle() const = 0;
    virtual void GetWindowSize(int* width, int* height) const = 0;
    unsigned int GetWidth() const { return m_width; }
    unsigned int GetHeight() const { return m_height; }


    void Quit() { m_running = false; }
    bool IsRunning() const { return m_running; }

protected:
    bool m_running = true;
    unsigned int m_width;
    unsigned int m_height;
    std::wstring title_;
    SDL_Window* m_sdlWindow = nullptr;

    // Declare SetWidth and SetHeight as protected functions
    void SetWidth(unsigned int width);
    void SetHeight(unsigned int height);

    friend class GLWindow; // Allow GLWindow to access protected functions

};