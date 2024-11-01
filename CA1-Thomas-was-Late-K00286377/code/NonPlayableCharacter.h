#pragma once
#include <SFML/Graphics.hpp>
#include "PlayableCharacter.h"

using namespace sf;

class NonPlayableCharacter {
protected:
    Sprite m_Sprite; // sprite
    Vector2f m_Position; // position
    float m_Speed; // speed
    float m_Gravity; // gravity

public:
    // Constructor
    NonPlayableCharacter(Vector2f position, float speed);

    // Virtual destructor
    virtual ~NonPlayableCharacter() = default;

    // Virtual update method
    virtual void update(float elapsedTime, const PlayableCharacter& player) = 0;

    // Returns a characters sprite
    Sprite getSprite() const { return m_Sprite; }
};