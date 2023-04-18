//main.cpp

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "GLRenderer.h"
#include "GLWindow.h"
#include "Debug.h"
#include "ErrorCheck.h"
#include "SystemDetection.h"
#include "GLUI.h"
#include "UI.h"
#include "Renderer.h"
#include "Window.h"
#include "DX11Renderer.h"
#include "DX11Camera.h"
#include "DX11Window.h"
#include "TypeConversion.h"

#include <filesystem>
#include <imgui_impl_sdl2.h>

//unsigned short int windowWidth = initialWindow.GetInitialWidth();
//unsigned short int windowHeight = initialWindow.GetInitialHeight();
//std::wstring
bool initialize_sdl_and_opengl();
void InitOpenGL(unsigned short int windowWidth, unsigned short int windowHeight, std::wstring windowTitle);
bool IsGLInitialized();
void InitDirectX();
void CleanUp();

using namespace std;

int main(int argc, char* argv[])
{
    DEBUG_MSG("Main.cpp : main() : starts.");

    ImGui::CreateContext();
    ImGui::SetCurrentContext(ImGui::CreateContext());

    // Check if the user can run DirectX
    //int dxVersion = GetDirectXVersion();
    //bool canRunDirectX = dxVersion >= 11;

    // Parse command-line arguments
    string renderer;
    renderer = "opengl";
    //if (argc >= 2)
    //{
    //    renderer = argv[1];
    //}
    //else
    //{
    //    // Choose the renderer based on the user's system capabilities
    //    renderer = canRunDirectX ? "directx" : "opengl";
    //}

    Window initialWindow;
    unsigned short int windowWidth = initialWindow.GetInitialWidth();
    unsigned short int windowHeight = initialWindow.GetInitialHeight();
    std::wstring windowTitle = initialWindow.GetHoloWinTitle();


    if (renderer == "opengl") 
    {
        InitOpenGL(windowWidth, windowHeight, windowTitle);
    }
    else if (renderer == "directx") 
    {
        InitDirectX();
    }
    else 
    {
        DEBUG_MSG("Main.cpp : main() : Usage: ");
        cout << argv[0] << " [sdl|directx]\n" << endl;
        return 1;
    }

    CleanUp();
}

bool IsGLInitialized()
{
    //// Check if the renderer was successfully initialized
    //if (!glRendererPtr)
    //{
    //    DEBUG_MSG("¢RMain.cpp : main() : Failed to initialize renderer.");
    //    return 1;
    //}

    //if (!uiPtr)
    //{
    //    DEBUG_MSG("¢RMain.cpp : main() : Failed to initialize UI.");
    //    return 1;
    //}

    //DEBUG_MSG("¢BMain.cpp : main() : rendererPtr: ");
    //cout << glRendererPtr << endl;
    //DEBUG_MSG("¢BWindow: ");
    //cout << glWindowPtr->GetSDLWindow() << endl;
}

void InitOpenGL(unsigned short int windowWidth, unsigned short int windowHeight, std::wstring windowTitle)
{
    //SystemDetection::CheckOpenGLVersionAdvaced();
    //if (!SystemDetection::CheckOpenglVersion())
    //{
    //    cout << endl;
    //    DEBUG_MSG("¢RMain.cpp : main() : Exit if OpenGL version check fails.");
    //    return 1;
    //}
    //cout << endl;

    //const GLubyte* glVersion = glGetString(GL_VERSION);
    //std::cout << "OpenGL Version: " << glVersion << std::endl;
    //std::cout << "GLSL version supported by the hardware: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Initialize SDL and create a window
    DEBUG_MSG("Main.cpp : main() : Initialize SDL and create a window.");
    //SDL_Window* sdlWindow = nullptr;
    //SDL_GLContext glContext = nullptr;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create the GLCamera object
    DEBUG_MSG("Main.cpp : main() : Create the GLCamera object.");
    GLCamera glcamera;

    // Create the GLRenderer and GLWindow objects
    DEBUG_MSG("Main.cpp : main() : Create the GLRenderer and GLWindow objects.");
    GLWindow glWindow(windowWidth, windowHeight, windowTitle);
    GLRenderer glRenderer(windowWidth, windowHeight, glcamera, &glWindow);
    //Renderer<GLRenderer>* glRendererPtr = new Renderer<GLRenderer>(windowWidth, windowHeight, glcamera);
    GLUI ui(&glWindow, &glRenderer, &glcamera);

    // Create a Renderer pointer for each renderer
    //Renderer<GLRenderer>* glRendererPtr = new Renderer<GLRenderer>(windowWidth, windowHeight, glcamera);
    //GLRenderer* RendererGLTemplate = &glRenderer;
    

    if (!initialize_sdl_and_opengl())
    {
        DEBUG_MSG("¢RMain.cpp : main() : Exit if the initialization fails.");
    }

    // Create the renderer pointer
    //glRendererPtr = new Renderer<GLRenderer>(windowWidth, windowHeight, glcamera);

    // Update the constructor call with the correct arguments
    DEBUG_MSG("Main.cpp : main() : Update the constructor call with the correct arguments.");
    //Renderer<GLRenderer> renderer(windowWidth, windowHeight, glcamera);

    if (!glWindow.Create() || !glRenderer.GLInitialize(windowWidth, windowHeight, glcamera))
    {
        DEBUG_MSG("¢RMain.cpp : main() : Exit if the initialization fails.");
    }

    GLWindow* glWindowPtr = &glWindow;

    // Create a Renderer pointer
    DEBUG_MSG("Main.cpp : main() : Create a Renderer pointer.");
    //GLRenderer* glRendererPtr = &glRenderer;

    // Create the UI object and assign it to uiPtr
    DEBUG_MSG("Main.cpp : main() : Create the UI object and assign it to uiPtr.");
    GLUI* uiPtr = new GLUI(&glWindow, glRendererPtr, &glcamera);

    //IsGLInitialized();

    // Enters main loop
    DEBUG_MSG("Main.cpp : main() : Enters main loop.");
    while (glWindowPtr->GetSDLWindow()->IsRunning())
    {
        DEBUG_MSG("Main.cpp : main() : Calls SQLEvent.");
        glWindowPtr->GetSDLWindow()->SQLEvent();

        DEBUG_MSG("Main.cpp : main() : Calls ProcessEvents.");
        glWindowPtr->GetSDLWindow()->ProcessEvents();

        // Render the UI
        DEBUG_MSG("Main.cpp : main() : Render the UI.");
        uiPtr->Render();

        // Render the scene
        DEBUG_MSG("Main.cpp : main() : Render the scene.");
        glRendererPtr->Render();

        DEBUG_MSG("Main.cpp : main() : SwapBuffers.");
        glWindowPtr->GetSDLWindow()->SwapBuffers();
    }
}

void InitDirectX()
{
    // Initialize DirectX and create a window
    DX11Camera dxcamera;
    Renderer<DX11Renderer>* dxRendererPtr = nullptr;
    DX11Window dxwindow(windowWidth, windowHeight, WCharToChar(windowTitle));
    HWND hwnd = reinterpret_cast<HWND>(dxwindow.GetNativeWindowHandle());
    DX11Renderer dxRenderer(hwnd);

    if (dxRenderer.DX11Initialize(hwnd, windowWidth, windowHeight, dxcamera))
    {
        dxRendererPtr = new Renderer<DX11Renderer>(windowWidth, windowHeight, dxcamera);
    }
    else
    {
        DEBUG_MSG("¢RMain.cpp : main() : failed to initialize DirectX.");
    }

    DEBUG_MSG("¢GMain.cpp : main() : DirectX completed.");

    //// Enters main loop
    //DEBUG_MSG("Main.cpp : main() : Enters main loop.");
    //while (dxRendererPtr->GetWindow()->IsRunning())
    //{
    //    DEBUG_MSG("Main.cpp : main() : Calls SQLEvent.");
    //    dxRendererPtr->GetWindow()->SQLEvent();

    //    DEBUG_MSG("Main.cpp : main() : Calls ProcessEvents.");
    //    dxRendererPtr->GetWindow()->ProcessEvents();

    //    // Render the UI
    //    DEBUG_MSG("Main.cpp : main() : Render the UI.");
    //    uiPtr->Render();

    //    // Render the scene
    //    DEBUG_MSG("Main.cpp : main() : Render the scene.");
    //    dxRendererPtr->Render();

    //    DEBUG_MSG("Main.cpp : main() : SwapBuffers.");
    //    dxRendererPtr->GetWindow()->SwapBuffers();
    //}
}

void CleanUp()
{
    // Clean up
    DEBUG_MSG("Main.cpp : main() : Clean up.");
    //ImGui_ImplSDL2_NewFrame(glRendererPtr->GetWindow()->GetSDLWindow());
}