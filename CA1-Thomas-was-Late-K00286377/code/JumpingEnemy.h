#pragma once
#include "Enemy.h"

class JumpingEnemy : public Enemy {
private:
    float m_PatrolDistance;
    float m_StartingX;
    float m_StartingY;
    bool m_MovingRight;

    float m_JumpCooldown;        // time between jumps
    float m_TimeSinceLastJump;   // time since last jump
    float m_JumpSpeed;           // jump speed
    float m_VerticalVelocity;    // current vertical velocity
    bool m_IsJumping;            // if the enemy is currently jumping

    const float m_Gravity = 300.0f; // gravity effect for the jump

public:
    JumpingEnemy(Vector2f position, float speed, float patrolDistance, float jumpCooldown = 4.0f, float jumpSpeed = 300.0f);
    void update(float elapsedTime, const PlayableCharacter& player) override;
};
