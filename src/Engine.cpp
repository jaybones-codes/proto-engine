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
    SDL_SetRenderVSync(m_renderer, SDL_RENDERER_VSYNC_DISABLED);
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

    m_lastFrameTime = Clock::now();

    std::cout << "Engine initialized: " << width << "x" << height << '\n';
}

Engine::Engine(Engine &&other) noexcept
    : m_window(other.m_window), m_renderer(other.m_renderer), m_initialized(other.m_initialized),
      m_running(other.m_running)
{
    // Nullify other's pointers so its destructor doesn't destroy resources
    other.m_window = nullptr;
    other.m_renderer = nullptr;
    other.m_initialized = false;
}
// Engine.cpp

Engine &Engine::operator=(Engine &&other) noexcept
{
    // Check for self-assignment
    if (this != &other)
    {
        // 1. Clean up OUR current resources first
        if (m_renderer)
        {
            SDL_DestroyRenderer(m_renderer);
        }
        if (m_window)
        {
            SDL_DestroyWindow(m_window);
        }
        // Note: We don't call SDL_Quit() here because we're staying alive,
        // just getting new resources

        // 2. Transfer ownership from other
        m_window = other.m_window;
        m_renderer = other.m_renderer;
        m_initialized = other.m_initialized;
        m_running = other.m_running;

        // 3. Nullify other's pointers
        other.m_window = nullptr;
        other.m_renderer = nullptr;
        other.m_initialized = false;
    }

    return *this;
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
void Engine::clear()
{

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

} // clear screen
void Engine::present()
{

    SDL_RenderPresent(m_renderer);
} // show what is drawn

void Engine::drawRect(float x, float y, float w, float h)
{

    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_renderer, &rect);
}
// Game Loop
void Engine::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_running = false;
        }
    }
}
void Engine::setTargetFPS(float fps)
{
    std::cout << "setTargetFPS called with: " << fps << "\n";
    if (fps <= 0.0f)
    {
        std::cerr << "ERROR: Invalid FPS " << fps << ", setting to 60\n";
        m_targetFps = 60.0f;
    }
    else
    {
        m_targetFps = fps;
    }
    std::cout << "m_targetFps is now: " << m_targetFps << "\n";
}
void Engine::updateDeltaTime()
{
    auto currentTime = Clock::now();
    auto duration = currentTime - m_lastFrameTime;
    m_deltaTime = std::chrono::duration<float>(duration).count();
    m_lastFrameTime = currentTime;

    m_frameCount++;
    m_fpsUpdateTimer += m_deltaTime;
    if (m_fpsUpdateTimer >= 1.0)
    {
        m_fps = m_frameCount / m_fpsUpdateTimer;
        std::cout << "FPS = " << m_fps << "\n";
        m_fpsUpdateTimer = 0;
        m_frameCount = 0;
    }
}
void Engine::limitFrameRate()
{
    float targetFrameTime = 1.0f / m_targetFps;
    float frameTimeElapsed = m_deltaTime;
    if (m_targetFps <= 0.0f)
    {
        std::cerr << "ERROR: m_targetFps is " << m_targetFps << "! Returning.\n";
        return; // Don't try to limit with invalid FPS
    }

    if (frameTimeElapsed < targetFrameTime)
    {
        float sleepTime = targetFrameTime - frameTimeElapsed;
        Uint32 delayMs = static_cast<Uint32>(sleepTime * 1000.0f);

        if (delayMs > 0)
        {
            SDL_Delay(delayMs);
        }
    }

    // Update delta time again AFTER sleeping
    auto currentTime = Clock::now();
    auto duration = currentTime - m_lastFrameTime;
    m_deltaTime = std::chrono::duration<float>(duration).count();
    m_lastFrameTime = currentTime;

    std::cout << "  New deltaTime after sleep: " << m_deltaTime << "\n";
}
int error(std::string errorMsg)
{
    std::cerr << errorMsg << SDL_GetError() << '\n';
    return -1;
}
