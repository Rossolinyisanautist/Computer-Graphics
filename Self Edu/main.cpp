#include<stdio.h>

#include<SDL2/SDL.h>
#include<OpenGL/gl3.h>

int main(int argc, char **argv)
{
	SDL_init(SDL_INIT_VIDEO);	
	SDL_window *window = SDL_CreateWindow(
		"SDL Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1920,
		1080,
		SDL_WINDOW_OPENGL
		);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext main_context = DSL_GL_CreateCOntext(window);

	

}