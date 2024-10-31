#include "NonPlayableCharacter.h"

NonPlayableCharacter::NonPlayableCharacter(Vector2f position, float speed) : m_Position(position), m_Speed(speed) {
    m_Sprite.setPosition(m_Position);
}