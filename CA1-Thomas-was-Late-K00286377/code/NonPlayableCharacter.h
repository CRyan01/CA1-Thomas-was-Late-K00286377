#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class NonPlayableCharacter {
protected:
    Sprite m_Sprite; // sprite
    Vector2f m_Position; // position
    float m_Speed; // speed

public:
    // Constructor
    NonPlayableCharacter(Vector2f position, float speed);

    // Virtual method
    virtual ~NonPlayableCharacter() = default;

    // Virtual update method
    virtual void update(float elapsedTime) = 0;

    // Returns a characters sprite
    Sprite getSprite() const { return m_Sprite; }
};