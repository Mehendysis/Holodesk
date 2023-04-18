// GLWindow.h
#pragma once

#include <string>
#include <SDL.h>


class GLWindow {
public:
    GLWindow(unsigned short int width, unsigned short int height, std::wstring title);
    ~GLWindow();

    void GetInitialWindowValues() {
        int width = GetCurrentWidth();
        int height = GetCurrentHeight();
        std::wstring title = getTitle();
        // do something with width, height, and title
    }

    void GetCurrentWindowSize(unsigned short int* pWidth, unsigned short int* pHeight) const;
    unsigned short int GetCurrentWidth() const;
    unsigned short int GetCurrentHeight() const;
    void SetWidth(unsigned short int width);
    void SetHeight(unsigned short int height);

    const std::wstring getTitle() const;
    SDL_Window* GetSDLWindow() const;

    bool Create();
    bool ProcessEvents();
    void Close();
    void Quit();
    void SQLEvent();
    void SwapBuffers();
    void* GetNativeWindowHandle() const;
    SDL_Window* GetWindowHandle() const;

    void OnResize(unsigned short int width, unsigned short int height);
    void Resize(unsigned short int width, unsigned short int height);
    void Minimize();
    void Maximize();
    

    static GLWindow& GetInstance();

private:
    SDL_Window* m_sdlWindow;
    unsigned short int m_CurrentWidth;
    unsigned short int m_CurrentHeight;
    std::wstring m_WindowTitle;
    bool m_IsClosed;
};