#include "ChaserEnemy.h"
#include "TextureHolder.h"

ChaserEnemy::ChaserEnemy(Vector2f position, float speed) : Enemy(position, speed) {
    // Load the texture
    m_Sprite.setTexture(TextureHolder::GetTexture("graphics/chaser_enemy.png"));

    // Center the sprites origin
    FloatRect bounds = m_Sprite.getLocalBounds();
    m_Sprite.setOrigin(bounds.width / 2, -15);

    // Set its inital position
    m_Sprite.setPosition(position);
}

void ChaserEnemy::update(float elapsedTime, const PlayableCharacter& player) {
    Vector2f playerPos = player.getCenter();

    // Move toward the players position
    if (playerPos.x > m_Position.x)
        m_Position.x += m_Speed * elapsedTime;
    else if (playerPos.x < m_Position.x)
        m_Position.x -= m_Speed * elapsedTime;

    if (playerPos.y > m_Position.y)
        m_Position.y += m_Speed * elapsedTime;
    else if (playerPos.y < m_Position.y)
        m_Position.y -= m_Speed * elapsedTime;

    m_Sprite.setPosition(m_Position);
}