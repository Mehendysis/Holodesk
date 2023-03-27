// Window.h
#pragma once

#include <string>

#ifdef USE_GLFW
#include <GLFW/glfw3.h>
#define WINDOW_CLASS_NAME "GLFW_Window"
#else
#include <SDL.h>
#define WINDOW_CLASS_NAME "SDL_Window"
#endif

class Window {
public:
    Window(unsigned int width, unsigned int height, const std::wstring& title);
    virtual ~Window() {}

    virtual void Create() = 0;
    virtual bool ProcessEvents() = 0;
    virtual void Close() = 0;

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

    virtual void* GetNativeWindowHandle() const = 0;

private:
#ifdef USE_GLFW
    GLFWwindow* m_glfwWindow = nullptr;
#else
    SDL_Window* m_sdlWindow = nullptr;
#endif

protected:
    unsigned int width_;
    unsigned int height_;
    std::wstring title_;
};
