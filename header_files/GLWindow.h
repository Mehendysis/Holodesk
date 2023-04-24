// GLWindow.h
#pragma once
//#include "GLMemoryWrapper.h"
#include <string>
#include <SDL.h>


class GLWindow {
public:
    GLWindow(unsigned short int width, unsigned short int height, std::wstring title);
    GLWindow();
    ~GLWindow();

    //void GetInitialWindowValues() {
    //    int width = GetCurrentWidth();
    //    int height = GetCurrentHeight();
    //    std::wstring title = getTitle();
    //    // do something with width, height, and title
    //}

    void GetCurrentWindowSize(unsigned short int* pWidth, unsigned short int* pHeight) const;
    unsigned short int GetCurrentWidth() const;
    unsigned short int GetCurrentHeight() const;
    void SetWidth(unsigned short int width);
    void SetHeight(unsigned short int height);

    const std::wstring getTitle() const;
    SDL_Window* GetSDLWindow() const;
    float GetAspectRatio() const;

    bool Create();
    bool ProcessEvents();
    void Close();
    void Quit();
    void SDLEvent();
    void SwapBuffers();
    void OnResize(unsigned short int width, unsigned short int height);
    void Resize(unsigned short int width, unsigned short int height);
    void Minimize();
    void Maximize();

    static GLWindow& GetInstance();
    void CallPrivateClean();

private:
    void  PrivateClean();
    SDL_Window* m_sdlWindow;
    unsigned short int m_CurrentWidth;
    unsigned short int m_CurrentHeight;
    std::wstring m_WindowTitle;
    bool m_IsClosed;
    SDL_GLContext m_glContext;
};