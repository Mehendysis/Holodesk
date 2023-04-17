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

#include <filesystem>
#include <imgui_impl_sdl2.h>


bool initialize_sdl_and_opengl();

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

    if (renderer == "opengl") 
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

        if (!initialize_sdl_and_opengl())
        {
            DEBUG_MSG("¢RMain.cpp : main() : Exit if the initialization fails.");
            return 1; // Exit if the initialization fails
        }

        // Create the GLCamera object
        DEBUG_MSG("Main.cpp : main() : Create the GLCamera object.");
        GLCamera glcamera;

        // Create the GLRenderer and GLWindow objects
        DEBUG_MSG("Main.cpp : main() : Create the GLRenderer and GLWindow objects.");
        Window initialWindow;
        unsigned short int windowWidth = initialWindow.GetInitialWidth();
        unsigned short int windowHeight = initialWindow.GetInitialHeight();
        std::wstring windowTitle = initialWindow.GetHoloWinTitle();
        GLWindow glWindow(windowWidth, windowHeight, windowTitle);

        // Update the constructor call with the correct arguments
        DEBUG_MSG("Main.cpp : main() : Update the constructor call with the correct arguments.");
        GLRenderer glRenderer(windowWidth, windowHeight, glcamera);

        if (!glWindow.Create() || !glRenderer.GLInitialize(windowWidth, windowHeight, glcamera))
        {
            DEBUG_MSG("¢RMain.cpp : main() : Exit if the initialization fails.");
            return 1; // Exit if the initialization fails
        }

        // Create a Renderer pointer
        DEBUG_MSG("Main.cpp : main() : Create a Renderer pointer.");
        rendererPtr = &glRenderer;

        // Cast the rendererPtr to its derived type
        DEBUG_MSG("Main.cpp : main() : Cast the rendererPtr to its derived type.");
        GLRenderer* glRendererPtr = static_cast<GLRenderer*>(rendererPtr);

        // Create the UI object and assign it to uiPtr
        DEBUG_MSG("Main.cpp : main() : Create the UI object and assign it to uiPtr.");
        uiPtr = new GLUI(&glWindow, glRendererPtr, &glcamera);


        // Check if the renderer was successfully initialized
        if (!rendererPtr)
        {
            DEBUG_MSG("¢RMain.cpp : main() : Failed to initialize renderer.");
            return 1;
        }

        if (!uiPtr)
        {
            DEBUG_MSG("¢RMain.cpp : main() : Failed to initialize UI.");
            return 1;
        }

        DEBUG_MSG("¢BMain.cpp : main() : rendererPtr: ");
        cout << rendererPtr << endl;
        DEBUG_MSG("¢BWindow: ");
        cout << rendererPtr->GetWindow() << endl;

    }
    else if (renderer == "directx") 
    {
        // Initialize DirectX and create a window
        // TODO: Implement DirectX window creation
        DEBUG_MSG("¢RMain.cpp : main() : DirectX renderer not implemented yet.");
        return 1;
    }
    else 
    {
        DEBUG_MSG("Main.cpp : main() : Usage: ");
        cout << argv[0] << " [sdl|directx]\n" << endl;
        return 1;
    }

    // Check if the renderer was successfully initialized
    if (!rendererPtr) 
    {
        DEBUG_MSG("¢RMain.cpp : main() : Failed to initialize renderer.");
        return 1;
    }


    if (!uiPtr)
    {
        DEBUG_MSG("¢RMain.cpp : main() : Failed to initialize UI.");
        return 1;
    }

    DEBUG_MSG("¢BMain.cpp : main() : rendererPtr: ");
    cout << rendererPtr << endl;
    DEBUG_MSG("¢BWindow: ");
    cout << rendererPtr->GetWindow() << endl;

    // Enters main loop
    DEBUG_MSG("Main.cpp : main() : Enters main loop.");
    while (rendererPtr->GetWindow()->IsRunning())
    {
        DEBUG_MSG("Main.cpp : main() : Calls SQLEvent.");
        rendererPtr->GetWindow()->SQLEvent();

        DEBUG_MSG("Main.cpp : main() : Calls ProcessEvents.");
        rendererPtr->GetWindow()->ProcessEvents();

        // Render the UI
        DEBUG_MSG("Main.cpp : main() : Render the UI.");
        uiPtr->Render();

        // Render the scene
        DEBUG_MSG("Main.cpp : main() : Render the scene.");
        rendererPtr->Render();

        DEBUG_MSG("Main.cpp : main() : SwapBuffers.");
        rendererPtr->GetWindow()->SwapBuffers();
    }

    // Clean up
    DEBUG_MSG("Main.cpp : main() : Clean up.");
    ImGui_ImplSDL2_NewFrame(rendererPtr->GetWindow()->GetSDLWindow());
}
