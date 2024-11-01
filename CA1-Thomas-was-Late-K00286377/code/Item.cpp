#include "Item.h"

// Constructor
Item::Item(Vector2f position) : m_Position(position) {
    m_Sprite.setPosition(m_Position);
}

// Check for collision with the player
bool Item::checkCollision(const FloatRect& player) {
    if (!m_IsCollected && m_Sprite.getGlobalBounds().intersects(player)) {
        m_IsCollected = true;
        return true;
    }
    return false;
}

// Draw the item if its active
void Item::draw(RenderWindow& window) const {
    if (!m_IsCollected) {
        window.draw(m_Sprite);
    }
}

// Mark the item as collected
void Item::collect() {
    m_IsCollected = true;
}

// Returns true if the item is marked as collected
bool Item::isCollected() const {
    return m_IsCollected;
}

// Returns the sprite of an item
const Sprite& Item::getSprite() const {
    return m_Sprite;
}
