// GLWindow.h
#pragma once

#include <string>
#include <SDL.h>


class GLWindow {
public:
    GLWindow(unsigned short int width, unsigned short int height, std::wstring title);
    ~GLWindow();

    void GetInitialWindowValues() {
        int width = getWidth();
        int height = getHeight();
        std::wstring title = getTitle();
        // do something with width, height, and title
    }

    void GetWindowSize(unsigned short int width, unsigned short int height) const;

    int getWidth() const;
    int getHeight() const;
    void SetWidth(unsigned short int width);
    void SetHeight(unsigned short int height);

    const std::wstring getTitle() const;
    SDL_Window* GetSDLWindow() const;

    bool Create();
    bool ProcessEvents();
    void Close();
    void SQLEvent();
    void SwapBuffers();
    void* GetNativeWindowHandle() const;
    void OnResize(unsigned short int width, unsigned short int height);
    void Resize(unsigned short int width, unsigned short int height);
    void Minimize();
    void Maximize();
    SDL_Window* GetWindowHandle() const;

    static GLWindow& GetInstance();

private:
    SDL_Window* m_sdlWindow;
    unsigned short int m_CurrentWidth;
    unsigned short int m_CurrentHeight;
    std::wstring m_WindowTitle;
};