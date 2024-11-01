#pragma once
#include "NonPlayableCharacter.h"
#include "PlayableCharacter.h"

class Enemy : public NonPlayableCharacter {
public:
    // Constructor
    Enemy(Vector2f position, float speed);
    // Update the enemy
    virtual void update(float elapsedTime, const PlayableCharacter& player) = 0;
};
