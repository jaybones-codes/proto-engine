#pragma once
#include <SDL3/SDL.h>
#include <iostream>

class Engine
{

  public:
    Engine(int width, int height, const char *title);
    ~Engine();

    // Stop anything from copying an Engine
    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;
    // Allow moving, changing ownership
    Engine(Engine &&) noexcept;
    Engine &operator=(Engine &&) noexcept;

    // Check if initialized
    bool isInitialized() const
    {
        return m_initialized;
    }
    // Rendering methods
    void clear();   // clear screen
    void present(); // show what is drawn
    void drawRect(float x, float y, float w, float h);

    // Game Loop
    bool isRunning() const
    {
        return m_running;
    };
    void pollEvents();

  private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    bool m_initialized = false;
    bool m_running = true;
};
// Helpers
int error(std::string errorMsg);
