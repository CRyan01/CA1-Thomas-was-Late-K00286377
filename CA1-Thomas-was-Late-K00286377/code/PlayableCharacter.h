#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:
	// Of course we will need a sprite
	Sprite m_Sprite;

	// How long does a jump last
	float m_JumpDuration;

	// Is character currently jumping or falling
	bool m_IsJumping;
	bool m_IsFalling;

	// Which directions is the character currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;

	// How long has this jump lasted so far
	float m_TimeThisJump;

	// Has the player just initialted a jump
	bool m_JustJumped = false;

	// How long the player has left in invincibility mode
	float m_InvincibilityTimer = 0.0f;

	// How long invincibility mode lasts
	const float INVINCIBILITY_DURATION = 1.0f;

	// Private variables and functions come next
private:
	// What is the gravity
	float m_Gravity;

	// How fast is the character
	float m_Speed = 400;

	// Where is the player
	Vector2f m_Position;

	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	// And a texture
	Texture m_Texture;

	// Does the thomas have the key
	bool m_HasKey = false;

	// Speed boost effect
	float m_SpeedBoostTimer = 0.0f;
	float m_SpeedMultiplier = 1.0f;

	// Score multiplier effect
	int m_ScoreMultiplier = 1;
	float m_ScoreMultiplierTimer = 0.0f;

	// If the speed boost is active
	bool m_isSpeedBoostActive = false;
	bool m_isScoreMultiplierActive = false;

	// All our public functions will come next
public:

	void spawn(Vector2f startPosition, float gravity);

	// This is a pure virtual function
	bool virtual handleInput() = 0;
	// This class is now abstract and cannot be instanciated

	// Returns true if the player is invincible
	bool isInvincible() const;

	// Where is the player
	FloatRect getPosition();

	// A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Make the character stand firm
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	// Where is the center of the character
	Vector2f getCenter() const;

	// We will call this function once every frame
	void update(float elapsedTime);

	// Collection functions
	void collectKey();
	void activateSpeedBoost();
	void collectCoin();

	// Update active effects
	void updateEffects(float dtAsSeconds);

	// Check if player has collected the key
	bool hasKey() const;

	// Reset the hasKey flag
	void removeKey();
};
