
#include "Engine.h"
#include <SDL3/SDL.h>
int main()
{
    std::cout << "Creating engine...\n";
    Engine engine(800, 600, "Test");

    std::cout << "Checking initialization...\n";
    if (!engine.isInitialized())
    {
        std::cerr << "Engine failed to initialize!\n";
        return -1;
    }

    std::cout << "Engine initialized successfully!\n";
    std::cout << "Waiting 3 seconds...\n";

    SDL_Delay(3000);

    std::cout << "Exiting...\n";
    return 0;
}
