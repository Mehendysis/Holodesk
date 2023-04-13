// Window.h
#pragma once

#include <string>
#include <SDL.h>

using namespace std;

class GLWindow;

class Window {
public:
    Window(unsigned int width = 800, unsigned int height = 600, const std::wstring& title = L"Holodesk");
    void SetWindowSize(unsigned int width, unsigned int height);
    virtual ~Window() {}

    void CleanUp();
    virtual bool Create() = 0;
    virtual bool ProcessEvents() = 0;
    virtual void Close() = 0;
    virtual void SQLEvent(Window* window) = 0;
    virtual void SwapBuffers() = 0;
    virtual void* GetNativeWindowHandle() const = 0;
    virtual void GetWindowSize(int* width, int* height) const = 0;

    unsigned int GetWidth() const { return m_width; }
    unsigned int GetHeight() const { return m_height; }


    void Quit() { m_running = false; }
    bool IsRunning() const { return m_running; }

protected:
    bool m_running = true;
    unsigned int m_width;
    unsigned int m_height;
    wstring title_;
    SDL_Window* m_sdlWindow = nullptr;

    // Declare SetWidth and SetHeight as protected functions
    void SetWidth(unsigned int width);
    void SetHeight(unsigned int height);

    friend class GLWindow; // Allow GLWindow to access protected functions

};