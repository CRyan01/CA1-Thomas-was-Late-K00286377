#pragma once
#include "Enemy.h"

class PatrollerEnemy : public Enemy {
private:
    float m_PatrolDistance;
    float m_StartingX;
    bool m_MovingRight;

public:
    PatrollerEnemy(Vector2f position, float speed, float patrolDistance);
    void update(float elapsedTime, const PlayableCharacter& player) override;
};