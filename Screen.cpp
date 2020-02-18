#include <iostream>
#include "Screen.h"

using namespace std;

Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL){

}

bool Screen::init() {

	//Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Failed to init SDL" << endl;
		return false;
	}

	//Create SDL window object
	m_window = SDL_CreateWindow("Particle Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SW, SH, SDL_WINDOW_SHOWN);
	if (m_window == NULL) {
		cout << "Failed to create an SDL window." << endl;
		return false;
	}

	//Create SDL Renderer object
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == NULL) {
		cout << "Failed to create an SDL renderer" << endl;
		return false;
	}

	//Create SDL Texture object
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
		SW, SH);
	if (m_texture == NULL) {
		cout << "Failed to create a texture object" << endl;
		return false;
	}

	//We need to create a buffer that will hold all the pixels on the screen
	//this will be a pointer, we are allocating this on the heap
	m_buffer = new Uint32[SW * SH];
	if (m_buffer == NULL) {
		cout << "Failed to allocate memory for our pixel buffer" << endl;
		return false;
	}

	//We need to write a value to this buffer, in this case we are writing the value 0xFF
	//This basically means that we are giving each pixel the colour WHITE
	//size will be the # of bytes of the pixels which is => # pixels * (each of each pixel)
	//each pixel is a 4 byte number
//	memset(buffer, 0xFF, SW * SH * sizeof(Uint32));

	memset(m_buffer, 0, SW * SH * sizeof(Uint32));

	//is an array
	//colour is a 4 byte number, 1 byte for R, 1 for G, 1 for B, 1 for A
	//when we write 32 bit number in HEX it goes like this
	//first pair of bytes, R, next G, next B, next A etc
	//buffer[30000] = 0xFF0000FF;

	for (int i = 0; i < SW * SH; i++) {
		m_buffer[i] = 0xFFFF00FF;
	}

	//Update the textures
	//updating the texture area with the pixel data
	//Remarks: NULL ==> entire area
	//pitch ==> # of bytes in one pixel row
	SDL_UpdateTexture(m_texture, NULL, m_buffer, SW * sizeof(Uint32));

	//Clear the renderer
	SDL_RenderClear(m_renderer);

	//Copy the texture to the rendering target
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);

	//Now we simply render to the screen
	SDL_RenderPresent(m_renderer);


	return true;
}

void Screen::close() {

	//deallocate resources
	delete[] m_buffer;

	//Destroy renderer
	SDL_DestroyRenderer(m_renderer);

	//Destroy texture
	SDL_DestroyTexture(m_texture);

	//Destroy window
	SDL_DestroyWindow(m_window);

	//clean up
	SDL_Quit();


}

bool Screen::processEvents() {

	SDL_Event event;

	//poll for any events
	while (SDL_PollEvent(&event)) {

		//if quit event found, exit
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;

}

