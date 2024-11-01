#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class LevelManager
{
private:
	Vector2i m_LevelSize;
	Vector2f m_StartPosition;
	float m_TimeModifier = 1;
	float m_BaseTimeLimit = 0;
	int m_CurrentLevel = 0;
	const int NUM_LEVELS = 3;

	// Store enemy objects
	vector<Vector2f> m_ChaserEnemiesPositions;
	vector<Vector2f> m_PatrollerEnemiesPositions;
	vector<Vector2f> m_JumpingEnemiesPositions;

	vector<Vector2f> m_KeyPositions;
	vector<Vector2f> m_CoinPositions;
	vector<Vector2f> m_SpeedBoostPositions;

	// The players score
	int m_Score;
	// The number of coins collected by the player
	int m_CoinsCollected;

public:

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	float getTimeLimit();

	Vector2f getStartPosition();

	int** nextLevel(VertexArray& rVaLevel);

	Vector2i getLevelSize();

	int getCurrentLevel();

	// Gets the tile type based on the number in the input file
	int getTileType(char tile);

	// Returns the current score
	int getScore();

	// Sets the current score
	void setScore(int score);

	// Returns the amount of coins collected
	int getCoinsCollected();
	
	// Sets the amount of coins collected
	void setCoinsCollected(int coins);

	// Return positions of enemies
	const vector<Vector2f> getChaserEnemiesPositions();
	const vector<Vector2f> getPatrollerEnemiesPositions();
	const vector<Vector2f> getJumpingEnemiesPositions();

	// Returns positions of items
	const vector<Vector2f> getKeyPositions();
	const vector<Vector2f> getSpeedBoostPositions();
	const vector<Vector2f> getCoinPositions();

};
