#include "Key.h"
#include "TextureHolder.h" // Assuming a TextureHolder class for loading textures

Key::Key(Vector2f position) : Item(position) {
    m_Sprite.setTexture(TextureHolder::GetTexture("graphics/key_item.png"));
}