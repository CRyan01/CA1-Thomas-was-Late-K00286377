#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Item {
protected:
    Vector2f m_Position;
    bool m_IsCollected = false;
    Sprite m_Sprite;

public:
    Item(Vector2f position);
    virtual ~Item() = default;

    // Check if the player collided with an item
    virtual bool checkCollision(const FloatRect& playerBounds);

    // Draw the item if its active
    void draw(RenderWindow& window) const;

    // Mark the item as collected
    void collect();

    // Check if the item is collected
    bool isCollected() const;

    // Returns the items sprite
    const Sprite& getSprite() const;
};