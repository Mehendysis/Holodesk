// GLHolodeskMain.cpp

#include <SDL.h>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include "GLMemoryWrapper.h"

#include "Debug.h"
#include "GLHolodeskMain.h"


void InitOpenGL(unsigned short int windowWidth, unsigned short int windowHeight, std::wstring windowTitle)
{

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error below.");
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to initialize SDL.");
        return;
    }

    // Create SDL window
    SDL_Window* window = SDL_CreateWindow(
        "My Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        return;
    }

    // Create SDL GL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (glContext == NULL)
    {
        std::cerr << "Failed to create SDL GL context: " << SDL_GetError() << std::endl;
        return;
    }

    // Initialize GLAD
    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Create shader program
    GLuint shaderProgram = glCreateProgram();
    // ...

    // Initialize UI


    // Game loop
    bool quit = false;
    while (!quit) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            // ...
        }

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        // Render ImGui UI
        ImGui::Begin("My Window");
        // ...
        ImGui::End();

        // End ImGui frame
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    // ...

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
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