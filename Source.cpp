#include <sstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "LTimer.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	TTF_Init();
	SDL_Window* window = SDL_CreateWindow
	("A Test SDL2 window", // window's title
		0, 0, // coordinates on the screen, in pixels, of the window's upper left corner
		1920, 1080, // window's length and height in pixels  
		SDL_WINDOW_BORDERLESS);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	TTF_Font* font = TTF_OpenFont("arial.ttf", 25);

	//Fps counter surface and using that create a texture

	SDL_Color text_color = { 0, 0, 0 };
	SDL_Surface* fps_surface = TTF_RenderText_Solid(font,
		"LAMEEEEE", text_color);
	SDL_Texture* fps_texture = SDL_CreateTextureFromSurface(renderer, fps_surface);


	//Create character texture using a surface

	SDL_Surface* image = SDL_LoadBMP("character.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,
		image);
	SDL_FreeSurface(image); // Destroy surface since already converted to texture.

	// Background color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	

	//Load Main Music Wav file

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	SDL_LoadWAV("main.wav", &wavSpec, &wavBuffer, &wavLength);
	//Open audio device
	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	//Logic
	bool quit = false;
	SDL_Event event;

	int x = 288;
	int y = 208;

	int texW = 0;
	int texH = 0;
	bool boo = false;

	// Play loaded audio
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);

	while (!quit)
	{
		SDL_Delay(10);
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:  x--; break;
			case SDLK_RIGHT: x++; break;
			case SDLK_UP:    y--; break;
			case SDLK_DOWN:  y++; break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			int mouseX = event.motion.x;
			int mouseY = event.motion.y;

			std::stringstream ss;
			ss << "X: " << mouseX << " Y: " << mouseY;

			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				SDL_ShowSimpleMessageBox(0, "Mouse", ss.str().c_str(), window);
				break;
			case SDL_BUTTON_RIGHT:
				SDL_ShowSimpleMessageBox(0, "Mouse", "Right button was pressed!", window);
				break;
			default:
				SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", window);
				break;
			}
		
			break;
		}
		SDL_RenderClear(renderer);
		
		if (!boo) {
			SDL_DestroyTexture(fps_texture);
			SDL_FreeSurface(fps_surface);
			 fps_surface = TTF_RenderText_Solid(font,
				"NOOOOOOOOOOOO", text_color);
			 fps_texture = SDL_CreateTextureFromSurface(renderer, fps_surface);
			boo = true;
		}
		else {
			SDL_DestroyTexture(fps_texture);
			SDL_FreeSurface(fps_surface);
			 fps_surface = TTF_RenderText_Solid(font,
				"LAMEEEEE", text_color);
			 fps_texture = SDL_CreateTextureFromSurface(renderer, fps_surface);
			 boo = false;
		}

		SDL_QueryTexture(fps_texture, NULL, NULL, &texW, &texH);
		SDL_Rect dstrect = { x, y, 64, 64 };
		SDL_Rect fps_dstrect = { 0, 0, texW, texH };
		SDL_RenderCopy(renderer, fps_texture, NULL, &fps_dstrect);
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);

	}


	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
	SDL_Quit();

	TTF_CloseFont(font);
	SDL_DestroyTexture(fps_texture);
	SDL_FreeSurface(fps_surface);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}