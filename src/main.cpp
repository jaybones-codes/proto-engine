
#include <SDL3/SDL.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Test", 800, 600, 0);
    if (!window)
    {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        return 1;
    }

    int running = 1;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
                running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
