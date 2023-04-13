//main.cpp

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "GLRenderer.h"
#include "GLWindow.h"
#include "Renderer.h"
#include "Debug.h"
#include "Window.h"
#include "UI.h"
#include "ErrorCheck.h"
#include "SystemDetection.h"
#include <filesystem>


bool initialize_sdl_and_opengl(SDL_Window*& window, SDL_GLContext& context);

using namespace std;

int main(int argc, char* argv[])
{
    DEBUG_MSG("¢GMain.cpp : main() : starts.");

    SDL_SetMainReady();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Initialize SDL and OpenGL
    DEBUG_MSG("Main.cpp : main() : Initialize SDL and OpenGL.");
    SDL_Window* sdlWindow = nullptr;
    SDL_GLContext glContext = nullptr;
    
    if (!initialize_sdl_and_opengl(sdlWindow, glContext))
    {
        DEBUG_MSG("¢RMain.cpp : main() : Exit if the initialization fails.");
        return 1; // Exit if the initialization fails
    }

    // Check if the window and context are not null
    if (!sdlWindow || !glContext)
    {
        DEBUG_MSG("¢RMain.cpp : main() : Error below.");
        std::cerr << "SDL window or OpenGL context is null" << std::endl;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return 1;
    }

    CheckOpenGLVersionAdvaced();
    if (!CheckOpenglVersion())
    {
        cout << endl;
        DEBUG_MSG("¢RMain.cpp : main() : Exit if OpenGL version check fails.");
        return 1;
    }

    cout << endl;
    // Change the name of the SDL_Renderer variable to avoid conflict
    DEBUG_MSG("Main.cpp : main() : Change the name of the SDL_Renderer variable to avoid conflict.");
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!sdlRenderer)
    {
        DEBUG_MSG("¢RMain.cpp : main() : Failed to create SDL renderer.");
        SDL_Quit();
        return 1;
    }

    const GLubyte* glVersion = glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << glVersion << std::endl;

    // Create the GLCamera object
    GLCamera camera;

    // Create the GLRenderer and GLWindow objects
    DEBUG_MSG("Main.cpp : main() : Create the GLRenderer and GLWindow objects.");
    unsigned int windowWidth = 1280;
    unsigned int windowHeight = 720;
    GLWindow glWindow(sdlWindow);

    // Update the constructor call with the correct arguments
    GLRenderer glRenderer(glWindow, windowWidth, windowHeight, camera);
    //glRenderer.Initialize(glWindow, sdlRenderer, windowWidth, windowHeight, camera); // Pass sdlRenderer instead of renderer
    if (!glRenderer.Initialize(glWindow, sdlRenderer, windowWidth, windowHeight, camera) || !glWindow.Create())
    {
        DEBUG_MSG("¢RMain.cpp : main() : Exit if the initialization fails.");
        return 1; // Exit if the initialization fails
    }

    GLWindow& glWindowRef = glWindow;
    glWindow.SetWidth(windowWidth);
    glWindow.SetHeight(windowHeight);

    // Enable OpenGL debug output
    DEBUG_MSG("Main.cpp : main() : Enable OpenGL debug output.");
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    // Register the debug message callback function
    DEBUG_MSG("Main.cpp : main() : Register the debug message callback function.");
    glDebugMessageCallback(debugCallback, nullptr);

    // Create a Window and Renderer pointer
    DEBUG_MSG("Main.cpp : main() : Create a Window and Renderer pointer.");
    Window* window = &glWindowRef;
    Renderer* rendererPtr = &glRenderer;

    // Initialize UI and set display
    DEBUG_MSG("Main.cpp : main() : Initialize UI and set display.");
    UI ui(&glWindow, &glRenderer, &camera);
    ui.Initialize();

    DEBUG_MSG("Main.cpp : main() : Enters main loop.");
    while (window->IsRunning())
    {
        window->SQLEvent(window);

        window->ProcessEvents();

        DEBUG_MSG("Main.cpp : main() : Render the scene.");
        // Render the scene
        rendererPtr->Render();

        // Render the UI
        DEBUG_MSG("Main.cpp : main() : Render the UI.");
        ui.Render();

        DEBUG_MSG("Main.cpp : main() : SwapBuffers().");
        window->SwapBuffers();
	}
	// Clean up
	DEBUG_MSG("Main.cpp : main() : Out of while loop for Clean up.");

    ui.CleanUp();
    window->CleanUp();
    rendererPtr->CleanUp();

    delete rendererPtr;
    delete window;

    glWindow.CleanUp();
    glRenderer.CleanUp();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();

	DEBUG_MSG("Main.cpp : main() : End of Clean up.");
    return 0;
}