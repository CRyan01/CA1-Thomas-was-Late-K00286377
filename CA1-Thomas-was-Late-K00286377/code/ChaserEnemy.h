#pragma once
#include "Enemy.h"

class ChaserEnemy : public Enemy {
public:
    ChaserEnemy(Vector2f position, float speed);
    void update(float elapsedTime, const PlayableCharacter& player) override;
};
