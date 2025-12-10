#include "Engine.h"
#include <iostream>

int main()
{
    Engine engine(800, 600, "Frame Rate Test");
    if (!engine.isInitialized())
        return -1;

    std::cout << "=== Testing 60 FPS ===\n";
    engine.setTargetFPS(60);

    int frameCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (engine.isRunning() && frameCount < 180)
    {
        engine.updateDeltaTime();
        engine.pollEvents();

        engine.clear();
        engine.drawRect(350, 250, 100, 100);
        engine.present();

        engine.limitFrameRate();

        frameCount++;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    float totalTime = std::chrono::duration<float>(endTime - startTime).count();

    std::cout << "60 FPS: " << frameCount << " frames in " << totalTime << "s = " << (frameCount / totalTime)
              << " FPS\n\n";

    std::cout << "=== Testing 30 FPS ===\n";
    engine.setTargetFPS(30);

    frameCount = 0;
    startTime = std::chrono::high_resolution_clock::now();

    while (engine.isRunning() && frameCount < 90)
    {
        engine.updateDeltaTime();
        engine.pollEvents();

        engine.clear();
        engine.drawRect(350, 250, 100, 100);
        engine.present();

        engine.limitFrameRate();

        frameCount++;
    }

    endTime = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration<float>(endTime - startTime).count();

    std::cout << "30 FPS: " << frameCount << " frames in " << totalTime << "s = " << (frameCount / totalTime)
              << " FPS\n";

    return 0;
}
