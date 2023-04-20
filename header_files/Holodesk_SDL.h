//Holodesk_SDL.h

#pragma once

//#include "GLMemoryWrapper.h"

#include <SDL.h>
#include <utility>


bool checkSDLError();

SDL_Window* initialize_sdl_and_opengl();

SDL_Window* createSDLWindow(const char* title, int width, int height);

SDL_GLContext createSDLGLContext(SDL_Window* window);

SDL_Surface* loadSDLImage(const char* filepath);