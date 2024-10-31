#pragma once
#include "NonPlayableCharacter.h"
#include "PlayableCharacter.h"

class Enemy : public NonPlayableCharacter {
public:
    Enemy(Vector2f position, float speed);
    virtual void update(float elapsedTime, const PlayableCharacter& player) = 0;
};
