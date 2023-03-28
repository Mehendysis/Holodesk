//main.cpp
#include <OpenGLRenderer.h>
#include <OpenGLWindow.h>
#include <Renderer.h>
#include <Debug.h>
#include <Window.h>
#include <imgui.h>
#include <UI.h>

using namespace std;

void RenderUI()
{
    // Start a new ImGui frame
    ImGui::Begin("My UI");

    // Add UI elements here
    ImGui::Text("Hello, world!");

    // End the ImGui frame
    ImGui::End();
}

int SDL_main(int argc, char* argv[])
{
    DEBUG_MSG("Main.cpp : main() : starts.");


    // Create a Window and Renderer pointer
    DEBUG_MSG("Main.cpp : main() : Create a Window and Renderer pointer.");
    Window* window = new OpenGLWindow();
    Renderer* renderer = new OpenGLRenderer(*window);

    // Initialize UI and set display
    DEBUG_MSG("Main.cpp : main() : Initialize UI and set display.");
    UI ui(window, renderer);
    ui.Initialize();
    ui.SetDisplay(window);

    renderer->Initialize();

    DEBUG_MSG("Main.cpp : main() : Enters main loop.");
    while (window->ProcessEvents())
    {
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