// Window.h
#pragma once

#include <string>
#include <SDL.h>


using namespace std;

class Window {
public:
    Window(unsigned int width = 800, unsigned int height = 600, const std::wstring& title = L"Window Title");
    virtual ~Window() {}

    virtual void Create() = 0;
    virtual bool ProcessEvents() = 0;
    virtual void Close() = 0;
    virtual void SQLEvent(Window* window) = 0;
    virtual void SwapBuffers() = 0;
    virtual void* GetNativeWindowHandle() const = 0;
    virtual void GetWindowSize(int* width, int* height) const = 0;

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    void Quit() { m_running = false; }
    bool IsRunning() const { return m_running; }

private:
    bool m_running = true;

protected:
    unsigned int width_;
    unsigned int height_;
    wstring title_;
    SDL_Window* m_sdlWindow = nullptr;

};