#include "SDL.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow
	("An Test SDL2 window", // window's title
		0, 0, // coordinates on the screen, in pixels, of the window's upper left corner
		1920, 1080, // window's length and height in pixels  
		SDL_WINDOW_FULLSCREEN_DESKTOP);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, 1920, 1080);
	


	bool quit = false;
	SDL_Event event;

	unsigned char* pixelArr = new unsigned char[1920 * 1080 * 4];
	
	for (int i = 0; i < 1920 * 1080; i++) {
		pixelArr[i*4 + 0] = 0xCC;// Red
		pixelArr[i*4 + 1] = 0x00;// Green
		pixelArr[i*4 + 2] = 0x66;// Blue
		pixelArr[i*4 + 3] = 0xFF;// Alpha
	}

	void* pixelPtr = &pixelArr[0];

	while (!quit)
	{
		SDL_UpdateTexture(texture, NULL, pixelPtr, 1920 * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	}


	delete pixelArr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}