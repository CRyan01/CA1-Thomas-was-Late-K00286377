#include "PatrollerEnemy.h"
#include "TextureHolder.h"

PatrollerEnemy::PatrollerEnemy(Vector2f position, float speed, float patrolDistance)
    : Enemy(position, speed), m_PatrolDistance(patrolDistance), m_MovingRight(true) {
    // Store its initial x position
    m_StartingX = position.x;

    // Load the texture
    m_Sprite.setTexture(TextureHolder::GetTexture("graphics/patroller_enemy.png"));

    // Center the sprites origin
    FloatRect bounds = m_Sprite.getLocalBounds();
    m_Sprite.setOrigin(bounds.width / 2, -15);

    // Set its inital position
    m_Sprite.setPosition(position);
}

void PatrollerEnemy::update(float elapsedTime, const PlayableCharacter& player) {
    // Move back and forth within a distance
    if (m_MovingRight) {
        m_Position.x += m_Speed * elapsedTime;
        if (m_Position.x > m_StartingX + m_PatrolDistance)
            m_MovingRight = false;
    } else {
        m_Position.x -= m_Speed * elapsedTime;
        if (m_Position.x < m_StartingX - m_PatrolDistance)
            m_MovingRight = true;
    }

    m_Sprite.setPosition(m_Position);
}