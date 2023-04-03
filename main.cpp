
//main.cpp

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "GLRenderer.h"
#include "GLWindow.h"
#include "Renderer.h"
#include "Debug.h"
#include "Window.h"
#include "UI.h"

bool initialize_sdl_and_opengl(SDL_Window*& window, SDL_GLContext& context);

using namespace std;

int main(int argc, char* argv[])
{
    SDL_SetMainReady();
    DEBUG_MSG("¢R Main.cpp : main() : starts.");

    // Initialize SDL and OpenGL
    SDL_Window* sdlWindow = nullptr;
    SDL_GLContext glContext = nullptr;
    if (!initialize_sdl_and_opengl(sdlWindow, glContext))
    {
        return 1; // Exit if the initialization fails
    }

    // Create a Window and Renderer pointer
    DEBUG_MSG("Main.cpp : main() : Create a Window and Renderer pointer.");
    Window* window = new GLWindow();
    Renderer* renderer = new GLRenderer(*window);

    // Initialize UI and set display
    DEBUG_MSG("Main.cpp : main() : Initialize UI and set display.");
    UI ui(window, renderer);
    ui.Initialize();

    renderer->Initialize();

    DEBUG_MSG("Main.cpp : main() : Enters main loop.");
    while (window->IsRunning())
    {
        window->SQLEvent(window);

        window->ProcessEvents();

        DEBUG_MSG("Main.cpp : main() : Render the scene.");
        // Render the scene
        renderer->Render();

        // Render the UI
        DEBUG_MSG("Main.cpp : main() : Render the UI.");
        ui.Render();

        DEBUG_MSG("Main.cpp : main() : SwapBuffers().");
        window->SwapBuffers();
	}
	// Clean up
	DEBUG_MSG("Main.cpp : main() : Out of while loop for Clean up.");
	delete renderer;
	delete window;

	DEBUG_MSG("Main.cpp : main() : End of Clean up.");
    return 0;
}