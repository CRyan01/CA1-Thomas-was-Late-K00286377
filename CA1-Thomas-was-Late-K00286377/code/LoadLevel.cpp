#include "Engine.h"

void Engine::loadLevel()
{
	m_Playing = false;

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];

	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);

	// Prepare the sound emitters
	populateEmitters(m_FireEmitters, m_ArrayLevel);
	
	// Reset the level timer
	m_ElapsedTime = 0.0f;
	// Reset player score
	m_LM.setScore(0);
	// Reset the number of coins collected
	m_LM.setCoinsCollected(0);

	// Spawn Thomas
	m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);

	// Clear existing enemies and pickups
	m_ChaserEnemies.clear();
	m_PatrollerEnemies.clear();
	m_JumpingEnemies.clear();
	m_Keys.clear();
	m_SpeedBoosts.clear();
	m_Coins.clear();

	// Spawn chaser, patrolling and jumping enemy types
	for (const auto& position : m_LM.getChaserEnemiesPositions()) {
		m_ChaserEnemies.emplace_back(position, chaserEnemySpeed);
	}
	for (const auto& position : m_LM.getPatrollerEnemiesPositions()) {
		m_PatrollerEnemies.emplace_back(position, patrollerEnemySpeed, patrolDistance);
	}
	for (const auto& position : m_LM.getJumpingEnemiesPositions()) {
		m_JumpingEnemies.emplace_back(position, jumpingEnemySpeed, patrolDistance);
	}

	// Spawn items
	for (const auto& position : m_LM.getKeyPositions()) {
		m_Keys.emplace_back(position);
	}
	for (const auto& position : m_LM.getSpeedBoostPositions()) {
		m_SpeedBoosts.emplace_back(position);
	}
	for (const auto& position : m_LM.getCoinPositions()) {
		m_Coins.emplace_back(position);
	}

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}