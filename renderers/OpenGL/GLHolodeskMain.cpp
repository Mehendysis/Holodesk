// GLHolodeskMain.cpp

#include <iostream>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include "GLMemoryWrapper.h"

#include "Window.h"
#include "Debug.h"
#include "GLHolodeskMain.h"
#include "TypeConversion.h"
#include "GLWindow.h"
#include "GLUI.h"
#include "Renderer.h"



void InitalizeHolodeskOpenGL(int argc, char* argv[])
{

    InitalizeSDL();

    // Call SDL_main
    int sdl_result = SDL_main(argc, argv);

    // Clean up SDL
    SDL_Quit();
}

int SDL_main(int argc, char* argv[])
{
    Window initialWindow;
    unsigned short int windowWidth = initialWindow.GetInitialWidth();
    unsigned short int windowHeight = initialWindow.GetInitialHeight();
    std::wstring windowTitle = initialWindow.GetHoloWinTitle();

    GLWindow* glWindow = new GLWindow(windowWidth, windowHeight, windowTitle);
    SDL_Window* sdlWindow = glWindow->GetSDLWindow();

    IsSDLInitialized(sdlWindow);

    SDL_GLContext glContext = CreateSDLGLContext(sdlWindow);

    InitializeGlad();

    // Create shader program
    GLuint shaderProgram = glCreateProgram();

    // Link shader program
    glLinkProgram(shaderProgram);

    // Initialize camera
    GLCamera* glCamera = new GLCamera();

    // Initialize renderer
    GLRenderer glRenderer(glWindow, glCamera, shaderProgram);

    // Initialize UI
    GLUI ui(glWindow, &glContext, &glRenderer);

    // Game loop
    bool quit = false;
    while (!quit) 
    {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
        }

        // Render UI
        ui.Render(sdlWindow);

        // Set OpenGL viewport to the size of the viewport window
        int display_w, display_h;
        SDL_GL_GetDrawableSize(sdlWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        // Set up the camera and render the scene
        glRenderer.SetCamera(glCamera);
        glRenderer.RenderScene();

        // Swap buffers
        SDL_GL_SwapWindow(sdlWindow);
    }

    ui.CallPrivateClean();
    glWindow->CallPrivateClean();

    return 0;
}

void InitalizeSDL()
{
	// Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
		DEBUG_MSG("¢RGLHolodeskMain.cpp : InitalizeSDL() : Failed to initialize SDL : ");
		std::cerr << SDL_GetError() << std::endl;
		throw std::runtime_error("Failed to initialize SDL.");
        exit(EXIT_FAILURE);
		return;
	}
    else
    {
        DEBUG_MSG("¢YGLHolodeskMain.cpp : InitalizeSDL() : SDL initialized.");
        return;
    }
}

void IsSDLInitialized(SDL_Window* sdlWindow)
{
    if (sdlWindow == NULL)
    {
        DEBUG_MSG("¢RGLHolodeskMain.cpp : IsSDLInitialized() : Failed to create SDL window : ");
        std::cerr << SDL_GetError() << std::endl;
        return;
    }
    else
    {
        DEBUG_MSG("¢YGLHolodeskMain.cpp : IsSDLInitialized() : SDL window created.");
        return;
    }
}

SDL_GLContext CreateSDLGLContext(SDL_Window* sdlWindow)
{
    // Create SDL GL context
    SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);
    if (glContext == NULL)
    {
        DEBUG_MSG("¢RGLHolodeskMain.cpp : CreateSDLGLContext() :Failed to create SDL GL context : ");
        std::cerr << SDL_GetError() << std::endl;
        return nullptr;
    }
    else
    {
		DEBUG_MSG("¢YGLHolodeskMain.cpp : CreateSDLGLContext() : SDL GL context created.");
		return glContext;
	}
}

void InitializeGlad()
{
    // Initialize GLAD
    if (!gladLoadGL())
    {
        DEBUG_MSG("¢RGLHolodeskMain.cpp : InitializeGlad() : Failed to initialize GLAD : ");
        std::cerr << std::endl;
        return;
    }
    else
    {
		DEBUG_MSG("¢YGLHolodeskMain.cpp : InitializeGlad() : GLAD initialized.");
		return;
    }
}

//bool IsGLInitialized()
//{
//    //// Check if the renderer was successfully initialized
//    //if (!glRendererPtr)
//    //{
//    //    DEBUG_MSG("¢RMain.cpp : main() : Failed to initialize renderer.");
//    //    return 1;
//    //}
//
//    //if (!uiPtr)
//    //{
//    //    DEBUG_MSG("¢RMain.cpp : main() : Failed to initialize UI.");
//    //    return 1;
//    //}
//
//    //DEBUG_MSG("¢BMain.cpp : main() : rendererPtr: ");
//    //cout << glRendererPtr << endl;
//    //DEBUG_MSG("¢BWindow: ");
//    //cout << glWindowPtr->GetSDLWindow() << endl;
//    return true;
//}

//void InitOpenGL(unsigned short int windowWidth, unsigned short int windowHeight, std::wstring windowTitle)
//{
//    //SystemDetection::CheckOpenGLVersionAdvaced();
//    //if (!SystemDetection::CheckOpenglVersion())
//    //{
//    //    cout << endl;
//    //    DEBUG_MSG("¢RMain.cpp : main() : Exit if OpenGL version check fails.");
//    //    return 1;
//    //}
//    //cout << endl;
//
//    //const GLubyte* glVersion = glGetString(GL_VERSION);
//    //std::cout << "OpenGL Version: " << glVersion << std::endl;
//    //std::cout << "GLSL version supported by the hardware: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
//
//    // Initialize SDL and create a window
//    DEBUG_MSG("Main.cpp : InitOpenGL() : Initialize SDL and create a window.");
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//
//    if (!isSDLInitialized())
//    {
//        DEBUG_MSG("¢RErrorCheck.cpp : InitOpenGL() : Error below.");
//    }
//
//    // Create the GLCamera object
//    DEBUG_MSG("Main.cpp : InitOpenGL() : Create the GLCamera object.");
//    // Create the GL objects as shared pointers
//    auto glWindow = std::make_shared<GLWindow>(windowWidth, windowHeight, windowTitle);
//    auto glCamera = std::make_shared<GLCamera>();
//
//    if (!glWindow->Create())
//    {
//        DEBUG_MSG("¢RMain.cpp : InitOpenGL() : Exit if the initialization fails.");
//        return;
//    }
//
//    // Create shared pointer for SDL window
//    auto sdlWindow = std::shared_ptr<SDL_Window>(glWindow->GetSDLWindow(), SDL_DestroyWindow);
//
//    if (!isSDLWindowInitialized(sdlWindow.get()))
//    {
//		DEBUG_MSG("¢RMain.cpp: InitOpenGL() : SDLWindow not initialized.");
//        return;
//	}
//
//    // Create const shared pointer for SDL window
//    const auto constSdlWindow = std::shared_ptr<const SDL_Window>(sdlWindow.get(), [](const SDL_Window*) {});
//
//    // Create shared pointer for GL context
//    auto glContext = std::shared_ptr<SDL_GLContext>(new SDL_GLContext(SDL_GL_CreateContext(sdlWindow.get())), SDL_GL_DeleteContext);
//
//    if (!isGLContextCurrent(sdlWindow.get(), glContext.get()))
//    {
//		DEBUG_MSG("¢RMain.cpp : InitOpenGL() : GLContext not current.");
//        return;
//	}
//
//    if (!isSDLGLContextInitialized(glContext.get()))
//    {
//        DEBUG_MSG("¢RMain.cpp : InitOpenGL() : GLContext not initialized.");
//        return;
//    }
//
//    auto sdlRenderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(sdlWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);
//
//    ImGui_ImplSDL2_InitForSDLRenderer(sdlWindow.get(), sdlRenderer.get());
//
//    // Create the GLRenderer and GLWindow objects
//    DEBUG_MSG("Main.cpp : InitOpenGL() : Create the GLRenderer and GLWindow objects.");
//    auto glRenderer = std::make_shared<GLRenderer>(windowWidth, windowHeight, *glCamera, *glWindow, glContext);
//
//    // Create the UI object and assign it to uiPtr
//    DEBUG_MSG("Main.cpp : InitOpenGL() : Create the UI object and assign it to uiPtr.");
//    //auto uiPtr = std::make_shared<GLUI>(constSdlWindow, *glWindow, glRenderer.get(), glCamera.get(), glContext.get());
//    auto uiPtr = std::make_shared<GLUI>(sdlWindow, *glWindow, glRenderer, glCamera, glContext);
//
//    // Load and compile the shader program
//    DEBUG_MSG("Main.cpp : InitOpenGL() : Load and compile the shader program.");
//    auto shaderProgram = std::make_shared<GLShaderProgram>(glRenderer);
//
//    if (shaderProgram->LoadShader(shaderProgram->GetVertexShaderFile(), shaderProgram->GetFragmentShaderFile()))
//    {
//        if (ShadersCompiled(*shaderProgram))
//        {
//            DEBUG_MSG("¢YMain.cpp : InitOpenGL() : Shaders compiled successfully.");
//            GLuint shaderProgramId = shaderProgram->GetProgramId();
//            if (shaderProgramId != 0)
//            {
//                DEBUG_MSG("¢GMain.cpp : InitOpenGL() : shaderProgramId is not 0.");
//                // Use the shader program
//                shaderProgram->Use(shaderProgramId);
//
//                // Enters main loop
//                DEBUG_MSG("Main.cpp : InitOpenGL() : Enters main loop.");
//                SDL_Event event;
//                bool quit = false;
//
//                while (!quit)
//                {
//                    // Handle events
//                    while (SDL_PollEvent(&event) != 0)
//                    {
//                        // Quit event
//                        if (event.type == SDL_QUIT)
//                        {
//                            quit = true;
//                        }
//                    }
//
//                    // Render the scene
//                    glRenderer->Render();
//
//                    // Render the UI
//                    uiPtr->Render();
//
//                    // Swap the front and back buffers
//                    SDL_GL_SwapWindow(glWindow->GetSDLWindow());
//                }
//            }
//        }
//
//    }
//
//    // Clean up and exit
//    uiPtr->CallPrivateClean();
//    glRenderer->CallPrivateClean();
//    glWindow->CallPrivateClean();
//    shaderProgram->CallPrivateClean();
//    SDL_Quit();
//}