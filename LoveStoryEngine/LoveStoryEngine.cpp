#include <SDL.h>
#include <stdio.h>
#include <SDL_mixer.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* image = NULL;
    SDL_Rect imageRect;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // Create window
    window = SDL_CreateWindow("Image Moving", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Get window surface
    screenSurface = SDL_GetWindowSurface(window);

    // Load image
    image = SDL_LoadBMP("image.bmp");
    if (image == NULL)
    {
        printf("Unable to load image! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Set image rect
    imageRect.x = SCREEN_WIDTH / 2 - image->w / 2;
    imageRect.y = SCREEN_HEIGHT / 2 - image->h / 2;
    imageRect.w = image->w;
    imageRect.h = image->h;

    // Event loop
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;

        // Handle events
        while (SDL_PollEvent(&event) != 0)
        {
            // Quit event
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            // Keydown event
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    // Move image left
                case SDLK_LEFT:
                    imageRect.x -= 10;
                    break;
                    // Move image right
                case SDLK_RIGHT:
                    imageRect.x += 10;
                    break;
                    // Move image up
                case SDLK_UP:
                    imageRect.y -= 10;
                    break;
                    // Move image down
                case SDLK_DOWN:
                    imageRect.y += 10;
                    break;
                }
            }
        }

        // Clear screen
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));

        // Draw image
        SDL_BlitSurface(image, NULL, screenSurface, &imageRect);

        // Update screen
        SDL_UpdateWindowSurface(window);
    }

    // Free resources
    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}