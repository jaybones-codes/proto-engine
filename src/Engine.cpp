#include "Engine.h"
#include <iostream>

Engine::Engine(int width, int height, const char *title)
{
    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        error("SDL Init failed: ");
        m_initialized = false;
        return;
    }
    // Create the window
    m_window = SDL_CreateWindow(title, width, height, 0);

    if (!m_window)
    {
        error("Window Failed to create :");
        SDL_Quit();
        return;
    }
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer)
    {
        error("Failed to create Renderer: ");
        m_initialized = false;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
    }

    m_initialized = true;
    std::cout << "Engine initialized: " << width << "x" << height << '\n';
}
Engine::~Engine()
{
    // Clean up in reverse order
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
    }
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
    }
    SDL_Quit();

    std::cout << "Engine shut down\n";
}
void clear();   // clear screen
void present(); // show what is drawn
void drawRect(float x, float y, float w, float h);
// Game Loop

void pollEvents();

int error(std::string errorMsg)
{
    std::cerr << errorMsg << SDL_GetError() << '\n';
    return -1;
}
