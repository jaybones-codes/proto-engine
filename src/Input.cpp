#include "Input.h"

void Input::update()
{
    // Transition Pressed -> Down, Released -> Up
    for (auto &[scancode, state] : m_keyStates)
    {
        if (state == ButtonState::Pressed)
        {
            state = ButtonState::Down;
        }
        else if (state == ButtonState::Released)
        {
            state = ButtonState::Up;
        }
    }

    for (auto &state : m_mouseButtons)
    {
        if (state == ButtonState::Pressed)
        {
            state = ButtonState::Down;
        }
        else if (state == ButtonState::Released)
        {
            state = ButtonState::Up;
        }
    }
}

void Input::processEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        SDL_Scancode key = event.key.scancode;
        // Only set to Pressed if not already Down (prevents key repeat)
        if (getKeyState(key) != ButtonState::Down)
        {
            setKeyState(key, ButtonState::Pressed);
        }
    }
    else if (event.type == SDL_EVENT_KEY_UP)
    {
        SDL_Scancode key = event.key.scancode;
        setKeyState(key, ButtonState::Released);
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        int button = event.button.button - 1; // SDL uses 1-5, we use 0-4
        if (button >= 0 && button < 5)
        {
            if (m_mouseButtons[button] != ButtonState::Down)
            {
                m_mouseButtons[button] = ButtonState::Pressed;
            }
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        int button = event.button.button - 1;
        if (button >= 0 && button < 5)
        {
            m_mouseButtons[button] = ButtonState::Released;
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_MOTION)
    {
        m_mouseX = static_cast<int>(event.motion.x);
        m_mouseY = static_cast<int>(event.motion.y);
    }
}

bool Input::isKeyDown(SDL_Scancode key) const
{
    ButtonState state = getKeyState(key);
    return state == ButtonState::Down || state == ButtonState::Pressed;
}

bool Input::isKeyPressed(SDL_Scancode key) const
{
    return getKeyState(key) == ButtonState::Pressed;
}

bool Input::isKeyReleased(SDL_Scancode key) const
{
    return getKeyState(key) == ButtonState::Released;
}

bool Input::isMouseButtonDown(int button) const
{
    if (button < 0 || button >= 5)
        return false;
    return m_mouseButtons[button] == ButtonState::Down || m_mouseButtons[button] == ButtonState::Pressed;
}

bool Input::isMouseButtonPressed(int button) const
{
    if (button < 0 || button >= 5)
        return false;
    return m_mouseButtons[button] == ButtonState::Pressed;
}

bool Input::isMouseButtonReleased(int button) const
{
    if (button < 0 || button >= 5)
        return false;
    return m_mouseButtons[button] == ButtonState::Released;
}

float Input::getAxis(SDL_Scancode negative, SDL_Scancode positive) const
{
    float value = 0.0f;
    if (isKeyDown(positive))
        value += 1.0f;
    if (isKeyDown(negative))
        value -= 1.0f;
    return value;
}

ButtonState Input::getKeyState(SDL_Scancode key) const
{
    auto it = m_keyStates.find(key);
    if (it != m_keyStates.end())
    {
        return it->second;
    }
    return ButtonState::Up;
}

void Input::setKeyState(SDL_Scancode key, ButtonState state)
{
    m_keyStates[key] = state;
}
