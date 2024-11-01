#include "SpeedBoost.h"
#include "TextureHolder.h"

SpeedBoost::SpeedBoost(Vector2f position) : Item(position) {
    m_Sprite.setTexture(TextureHolder::GetTexture("graphics/speed_boost_item.png"));
}