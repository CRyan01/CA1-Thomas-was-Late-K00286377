#include "Engine.h"

bool Engine::detectCollisions(PlayableCharacter& character)
{
	bool reachedGoal = false;
	// Make a rect for all his parts
	FloatRect detectionZone = character.getPosition();

	// Make a FloatRect to test each block
	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around thomas to detect collisions
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;

	// Thomas is quite tall so check a few tiles vertically
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	if (startX < 0)startX = 0;
	if (startY < 0)startY = 0;
	if (endX >= m_LM.getLevelSize().x)
		endX = m_LM.getLevelSize().x;
	if (endY >= m_LM.getLevelSize().y)
		endY = m_LM.getLevelSize().y;

	// Has the character fallen out of the map?
	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);
	if (!character.getPosition().intersects(level))
	{
		// respawn the character
		character.spawn(m_LM.getStartPosition(), GRAVITY);
	}

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Initialize the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

			// Has character been burnt or drowned?
			// Use head as this allows him to sink a bit
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);
					// Which sound should be played?
					if (m_ArrayLevel[y][x] == 2)// Fire, ouch!
					{
						// Play a sound
						m_SM.playFallInFire();

					}
					else // Water
					{
						// Play a sound
						m_SM.playFallInWater();
					}
				}
			}


			// Is character colliding with a regular block
			if (m_ArrayLevel[y][x] == 1)
			{

				if (character.getRight().intersects(block))
				{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))
				{
					character.stopLeft(block.left);
				}


				if (character.getFeet().intersects(block))
				{
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))
				{
					character.stopJump();
				}
			}

			// Enemy collision check
			for (const auto& enemy : m_ChaserEnemies) {
				if (character.getPosition().intersects(enemy.getSprite().getGlobalBounds())) {
					if (!character.isInvincible()) {
						character.spawn(m_LM.getStartPosition(), GRAVITY);
						m_SM.playFallInFire();
						return reachedGoal;
					}
				}
			}

			for (const auto& enemy : m_PatrollerEnemies) {
				if (character.getPosition().intersects(enemy.getSprite().getGlobalBounds())) {
					if (!character.isInvincible()) {
						character.spawn(m_LM.getStartPosition(), GRAVITY);
						m_SM.playFallInFire();
						return reachedGoal;
					}
				}
			}

			for (const auto& enemy : m_JumpingEnemies) {
				if (character.getPosition().intersects(enemy.getSprite().getGlobalBounds())) {
					if (!character.isInvincible()) {
						character.spawn(m_LM.getStartPosition(), GRAVITY);
						m_SM.playFallInFire();
						return reachedGoal;
					}
				}
			}

			// Key collision detection
			for (auto& key : m_Keys) {
				if (key.checkCollision(character.getPosition())) {
					character.collectKey();
				}
			}

			// Speed boost collision detection
			for (auto& speedBoost : m_SpeedBoosts) {
				if (speedBoost.checkCollision(character.getPosition())) {
					character.activateSpeedBoost();
				}
			}

			// Coin collision detection
			for (auto& coin : m_Coins) {
				if (coin.checkCollision(character.getPosition())) {
					character.collectCoin();

					// Update the number of coins collected
					int currentCoins = m_LM.getCoinsCollected();
					m_LM.setCoinsCollected(currentCoins + 1);
				}
			}
			
			// More collision detection here once we have learned about particle effects
			// Has the characters' feet touched fire or water?
			// If so, start a particle effect
			// Make sure this is the first time we have detected this
			// by seeing if an effect is already running			
			if (!m_PS.running()) {
				if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
				{
					if (character.getFeet().intersects(block))
					{
						// position and start the particle system
						m_PS.emitParticles(character.getCenter());

					}
				}
			}

			// Check if the character reached the exit with the key item
			if (m_ArrayLevel[y][x] == 4 && character.hasKey())
			{
				// Reset hasKey for the next level
				character.removeKey();

				// Character has reached the goal
				reachedGoal = true;
			}

		}

	}

	// All done, return, wheteher or not a new level might be required
	return reachedGoal;
}