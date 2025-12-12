#include "Engine.h"
#include <iostream>

int main()
{
    Engine engine(800, 600, "Input Test");
    if (!engine.isInitialized())
        return -1;

    float x = 400.0f;
    float y = 300.0f;
    float speed = 300.0f;

    while (engine.isRunning())
    {
        engine.updateDeltaTime();
        engine.pollEvents();

        const Input &input = engine.getInput();
        float dt = engine.getDeltaTime();

        // WASD movement using axes
        float horizontal = input.getAxis(SDL_SCANCODE_A, SDL_SCANCODE_D);
        float vertical = input.getAxis(SDL_SCANCODE_W, SDL_SCANCODE_S);

        x += horizontal * speed * dt;
        y += vertical * speed * dt;

        // Test key press detection
        if (input.isKeyPressed(SDL_SCANCODE_SPACE))
        {
            std::cout << "Jump!\n";
        }

        // Test mouse input
        if (input.isMouseButtonPressed(0))
        {
            std::cout << "Click at (" << input.getMouseX() << ", " << input.getMouseY() << ")\n";
        }

        engine.clear();
        engine.drawRect(x - 50, y - 50, 100, 100);
        engine.present();
        engine.limitFrameRate();
    }

    return 0;
}
