
#include "Engine.h"
#include <SDL3/SDL.h>

Engine createEngine()
{
    return Engine(800, 600, "Moved Engine");
}

int main()
{
    // Create engine
    Engine engine(800, 600, "My First Engine");

    if (!engine.isInitialized())
    {
        return -1;
    }
    while (engine.isRunning())
    {

        engine.pollEvents();
        engine.clear();
        engine.drawRect(350, 250, 100, 100);
        engine.present();
    }

    return 0;
}
