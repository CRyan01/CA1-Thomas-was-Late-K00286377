#include "Coin.h"
#include "TextureHolder.h"

Coin::Coin(Vector2f position) : Item(position) {
    m_Sprite.setTexture(TextureHolder::GetTexture("graphics/coin_item.png"));
}