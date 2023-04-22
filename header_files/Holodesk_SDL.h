//Holodesk_SDL.h

#pragma once

//#include "GLMemoryWrapper.h"

#include <SDL.h>
#include <utility>


bool checkSDLError();

SDL_Window* createSDLWindow(const char* title, int width, int height);

SDL_GLContext createSDLGLContext(SDL_Window* window);

SDL_Surface* loadSDLImage(const char* filepath);

bool isSDLInitialized();

bool isGLContextCurrent(SDL_Window* window, SDL_GLContext context);

bool isSDLWindowInitialized(SDL_Window* window);

bool isSDLGLContextInitialized(SDL_GLContext context);