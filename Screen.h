#include <SDL.h>

#pragma once
class Screen{

public:
	const static int SW = 800;
	const static int SH = 600;

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	Uint32* m_buffer;

public:
	Screen();

	//init function
	bool init();

	bool processEvents();

	//deallocation
	void close();

};

