//main.cpp

#define SDL_MAIN_HANDLED

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
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include <SDL.h>
#include <iostream>
#include <utility>


//unsigned short int windowWidth = initialWindow.GetInitialWidth();
//unsigned short int windowHeight = initialWindow.GetInitialHeight();
//std::wstring

//SDL_Window* initialize_sdl_and_opengl();

void InitOpenGL(unsigned short int windowWidth, unsigned short int windowHeight, std::wstring windowTitle);
bool IsGLInitialized();
void InitDirectX();
void CleanUp();

using namespace std;

int main(int argc, char* argv[])
{
    DEBUG_MSG("¢BMain.cpp : main() : starts.");

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
    return true;
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
    DEBUG_MSG("Main.cpp : InitOpenGL() : Initialize SDL and create a window.");
    //SDL_Window* sdlWindow = nullptr;
    //SDL_GLContext glContext = nullptr;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create the GLCamera object
    DEBUG_MSG("Main.cpp : InitOpenGL() : Create the GLCamera object.");
    //GLCamera* glCamera;
    //GLWindow glWindow(windowWidth, windowHeight, windowTitle);
    
    // Create the GL objects as unique pointers
    std::unique_ptr<GLWindow> glWindow = std::make_unique<GLWindow>(windowWidth, windowHeight, windowTitle);
    
    std::unique_ptr<GLCamera> glCamera = std::make_unique<GLCamera>();

    if (!glWindow->Create())
    {
        DEBUG_MSG("¢RMain.cpp : InitOpenGL() : Exit if the initialization fails.");
        return;
    }

    // Create unique pointer for SDL window
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sdlWindow(glWindow->GetSDLWindow(), SDL_DestroyWindow);

    // Create unique pointer for GL context
    std::unique_ptr<SDL_GLContext, decltype(&SDL_GL_DeleteContext)> glContext(new SDL_GLContext(SDL_GL_CreateContext(sdlWindow.get())), SDL_GL_DeleteContext);

    //SDL_Window* sdlWindow = glWindow->GetSDLWindow();
    //SDL_GLContext* glContext = new SDL_GLContext(SDL_GL_CreateContext(sdlWindow));

    // Initialize ImGui
    //SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> sdlRenderer(SDL_CreateRenderer(std::move(sdlWindow), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);
    // Create a unique_ptr object to manage the SDL window
    //std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> sdlWindow(SDL_CreateWindow(WCharToChar(windowTitle), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN), SDL_DestroyWindow);

    // Create a unique_ptr object to manage the SDL renderer
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> sdlRenderer(SDL_CreateRenderer(sdlWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);


    ImGui_ImplSDL2_InitForSDLRenderer(sdlWindow.get(), sdlRenderer.get());

    // Create the GLRenderer and GLWindow objects
    DEBUG_MSG("Main.cpp : InitOpenGL() : Create the GLRenderer and GLWindow objects.");
    std::unique_ptr<GLRenderer> glRenderer = std::make_unique<GLRenderer>(windowWidth, windowHeight, *glCamera, *glWindow, glContext);
    //GLRenderer glRenderer(windowWidth, windowHeight, *glCamera, *glWindow, glContext);
    //GLWindow* glWindowPtr = &glWindow;

    // Create the UI object and assign it to uiPtr
    DEBUG_MSG("Main.cpp : InitOpenGL() : Create the UI object and assign it to uiPtr.");
    //GLUI* uiPtr = new GLUI(sdlWindow, &glWindow, &glRenderer, &glcamera, &glContext);
    //GLUI* uiPtr = new GLUI(sdlWindow, glWindow.get(), &glRenderer, &glCamera, glContext.get());
    std::unique_ptr<GLUI> uiPtr = std::make_unique<GLUI>(sdlWindow, glWindow, glRenderer, glCamera, &glContext);

    // Load and compile the shader program
    DEBUG_MSG("Main.cpp : InitOpenGL() : Load and compile the shader program.");
    //GLShaderProgram shaderProgram(&glRenderer);
    std::unique_ptr<GLShaderProgram> shaderProgram = std::make_unique<GLShaderProgram>(&glRenderer);

    if (shaderProgram->LoadShader(shaderProgram->GetVertexShaderFile(), shaderProgram->GetFragmentShaderFile()))
    {
        if (ShadersCompiled(*shaderProgram))
        {
            DEBUG_MSG("¢YMain.cpp : InitOpenGL() : Shaders compiled successfully.");
            GLuint shaderProgramId = shaderProgram->GetProgramId();
            if (shaderProgramId != 0)
            {
                DEBUG_MSG("¢GMain.cpp : InitOpenGL() : shaderProgramId is not 0.");
                // Use the shader program
                shaderProgram->Use(shaderProgramId);

                // Enters main loop
                DEBUG_MSG("Main.cpp : InitOpenGL() : Enters main loop.");
                SDL_Event event;
                bool quit = false;

                while (!quit)
                {
                    // Handle events
                    while (SDL_PollEvent(&event) != 0)
                    {
                        // Quit event
                        if (event.type == SDL_QUIT)
                        {
                            quit = true;
                        }
                    }

                    // Render the scene
                    glRenderer->Render();

                    // Render the UI
                    uiPtr->Render();

                    // Swap the front and back buffers
                    SDL_GL_SwapWindow(glWindow->GetSDLWindow());
                }
            }
        }

    }

    // Clean up and exit
    uiPtr->CallPrivateClean();
    glRenderer->CallPrivateClean();
    glWindow->CallPrivateClean();
    shaderProgram->CallPrivateClean();
    SDL_Quit();
}

void InitDirectX()
{
    //// Initialize DirectX and create a window
    //DX11Camera dxcamera;
    //Renderer<DX11Renderer>* dxRendererPtr = nullptr;
    //DX11Window dxwindow(windowWidth, windowHeight, WCharToChar(windowTitle));
    //HWND hwnd = reinterpret_cast<HWND>(dxwindow.GetNativeWindowHandle());
    //DX11Renderer dxRenderer(hwnd);

    //if (dxRenderer.DX11Initialize(hwnd, windowWidth, windowHeight, dxcamera))
    //{
    //    dxRendererPtr = new Renderer<DX11Renderer>(windowWidth, windowHeight, dxcamera);
    //}
    //else
    //{
    //    DEBUG_MSG("¢RMain.cpp : main() : failed to initialize DirectX.");
    //}

    //DEBUG_MSG("¢BMain.cpp : main() : DirectX completed.");

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