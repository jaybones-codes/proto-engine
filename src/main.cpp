#include "Engine.h"
#include <iostream>

int main()
{
    Engine engine(800, 600, "Test");
    if (!engine.isInitialized())
        return -1;

    engine.setTargetFPS(30);
    engine.updateDeltaTime(); // Initialize timing

    while (engine.isRunning())
    {
        float dt = engine.getDeltaTime(); // Use LAST frame's delta

        engine.pollEvents();

        // Game logic using dt

        std::cout << "dt=" << engine.getDeltaTime() << "  timer=" << engine.m_fpsUpdateTimer << "\n";

        engine.clear();
        // engine.drawRect(350, 250, 100, 100);
        engine.present();

        engine.limitFrameRate();
        engine.updateDeltaTime(); // Measure at END (includes sleep)
    }
}
