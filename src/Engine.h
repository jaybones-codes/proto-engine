#pragma once
#include <SDL3/SDL.h>
#include <chrono>
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
    // Time stuff
    void updateDeltaTime();
    float getDeltaTime() const
    {
        return m_deltaTime;
    }
    float getFPS() const
    {
        return m_fps;
    }
    void setTargetFPS(float fps);

    void limitFrameRate();

  private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    bool m_initialized = false;
    bool m_running = true;

    TimePoint m_lastFrameTime = Clock::now();
    float m_deltaTime = 60.0f;
    float m_fps = 0.0f;
    float m_targetFps = 0.0f;

    int m_frameCount = 0;

  public:
    float m_fpsUpdateTimer = 0.0f;
};
// Helpers
int error(std::string errorMsg);
