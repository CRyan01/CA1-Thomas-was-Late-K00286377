#include "JumpingEnemy.h"
#include "TextureHolder.h"

JumpingEnemy::JumpingEnemy(Vector2f position, float speed, float patrolDistance, float jumpCooldown, float jumpSpeed)
    : Enemy(position, speed), m_PatrolDistance(patrolDistance), m_JumpCooldown(jumpCooldown), m_JumpSpeed(jumpSpeed),
    m_TimeSinceLastJump(0.0f), m_VerticalVelocity(0.0f), m_IsJumping(false), m_MovingRight(true) {
    // Store its initial x position
    m_StartingX = position.x;
    m_StartingY = position.y;

    // Load the texture
    m_Sprite.setTexture(TextureHolder::GetTexture("graphics/jumping_enemy.png"));

    // Center the sprites origin
    FloatRect bounds = m_Sprite.getLocalBounds();
    m_Sprite.setOrigin(bounds.width / 2, -15);

    // Set its inital position
    m_Sprite.setPosition(position);
}

void JumpingEnemy::update(float elapsedTime, const PlayableCharacter& player) {
    // Patrol left and right
    if (m_MovingRight && !m_IsJumping) {
        m_Position.x += m_Speed * elapsedTime;
        if (m_Position.x > m_StartingX + m_PatrolDistance) {
            m_MovingRight = false;
        }
    } else if (!m_IsJumping) {
        m_Position.x -= m_Speed * elapsedTime;
        if (m_Position.x < m_StartingX - m_PatrolDistance) {
            m_MovingRight = true;
        }
    }

    // Check if it can jump
    m_TimeSinceLastJump += elapsedTime;
    if (m_TimeSinceLastJump >= m_JumpCooldown && !m_IsJumping) {
        // Jump
        m_IsJumping = true;
        m_VerticalVelocity = -m_JumpSpeed; // upward velocity
        m_TimeSinceLastJump = 0.0f;
    }

    // Update vertical position when jumping
    if (m_IsJumping) {
        m_VerticalVelocity += m_Gravity * elapsedTime; // apply gravity effect
        m_Position.y += m_VerticalVelocity * elapsedTime;

        // Reset to original position
        if (m_Position.y >= m_StartingY) {
            m_Position.y = m_StartingY;
            m_IsJumping = false; // end the jump
            m_VerticalVelocity = 0.0f; // reset vertical velocity
        }
    }

    m_Sprite.setPosition(m_Position);
}
