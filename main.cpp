//main.cpp
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "GLRenderer.h"
#include "GLWindow.h"
#include "Renderer.h"
#include "Debug.h"
#include "Window.h"
#include "UI.h"


using namespace std;

int main(int argc, char* argv[])
{
    SDL_SetMainReady();
    DEBUG_MSG("Main.cpp : main() : starts.");

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
        ui.Render();

        window->SwapBuffers();
	}
	// Clean up
	DEBUG_MSG("Main.cpp : main() : Out of while loop for Clean up.");
	delete renderer;
	delete window;

	DEBUG_MSG("Main.cpp : main() : End of Clean up.");
    return 0;
}