#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureHolder.h"
#include <sstream>
#include <fstream>
#include "LevelManager.h"

using namespace sf;
using namespace std;

int** LevelManager::nextLevel(VertexArray& rVaLevel)
{
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	// Clear enemy positions from previous levels
	m_ChaserEnemiesPositions.clear();
	m_PatrollerEnemiesPositions.clear();
	m_JumpingEnemiesPositions.clear();

	// Clear item positions from previous levels
	m_KeyPositions.clear();
	m_SpeedBoostPositions.clear();
	m_CoinPositions.clear();

	// Get the next level
	m_CurrentLevel++;
	if (m_CurrentLevel > NUM_LEVELS)
	{
		m_CurrentLevel = 1;
		m_TimeModifier -= .1f;
	}

	// Load the appropriate level from a text file
	string levelToLoad;
	switch (m_CurrentLevel)
	{
	case 1:
		levelToLoad = "levels/level1.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 800;
		m_BaseTimeLimit = 30.0f;
		break;

	case 2:
		levelToLoad = "levels/level2.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 800;
		m_BaseTimeLimit = 100.0f;
		break;

	case 3:
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 800; 
		m_BaseTimeLimit = 30.0f;
		break;
	}

	ifstream inputFile(levelToLoad);
	string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}

	// Store the length of the rows
	m_LevelSize.x = s.length();

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Prepare the 2d array to hold the int values from the file
	int** arrayLevel = new int*[m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		// Add a new array into each array element
		arrayLevel[i] = new int[m_LevelSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (inputFile >> row)
	{
		for (int x = 0; x < row.length(); x++) {

			const char val = row[x];
			arrayLevel[y][x] = atoi(&val);

			// Populate the level with enemies & items based on placement in text file
			int tileType = getTileType(row[x]);
			if (tileType == 5) {
				m_ChaserEnemiesPositions.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));
				arrayLevel[y][x] = 0;
			} else if (tileType == 6) {
				m_PatrollerEnemiesPositions.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));
				arrayLevel[y][x] = 0;
			} else if (tileType == 7) {
				m_JumpingEnemiesPositions.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));
				arrayLevel[y][x] = 0;
			} else if (tileType == 8) {
				m_KeyPositions.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));
				arrayLevel[y][x] = 0;
			} else if (tileType == 9) {
				m_SpeedBoostPositions.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));
				arrayLevel[y][x] = 0;
			} else if (tileType == 10) {
				m_CoinPositions.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));
				arrayLevel[y][x] = 0;
			}
		}
		y++;
	}

	// close the file
	inputFile.close();

	// What type of primitive are we using?
	rVaLevel.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			// Position each vertex in the current quad
			rVaLevel[currentVertex + 0].position = 
				Vector2f(x * TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 1].position = 
				Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 2].position = 
				Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			rVaLevel[currentVertex + 3].position = 
				Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);

			// Which tile from the sprite sheet should we use
			int verticalOffset = arrayLevel[y][x] * TILE_SIZE;

			rVaLevel[currentVertex + 0].texCoords = 
				Vector2f(0, 0 + verticalOffset);

			rVaLevel[currentVertex + 1].texCoords = 
				Vector2f(TILE_SIZE, 0 + verticalOffset);

			rVaLevel[currentVertex + 2].texCoords = 
				Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

			rVaLevel[currentVertex + 3].texCoords = 
				Vector2f(0, TILE_SIZE + verticalOffset);

			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return arrayLevel;
}

Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;
}

int LevelManager::getCurrentLevel()
{
	return m_CurrentLevel;
}

// Returns positions of chaser enemies
const vector<Vector2f> LevelManager::getChaserEnemiesPositions()
{
	return m_ChaserEnemiesPositions;
}
// Returns positions patroller of chaser enemies
const vector<Vector2f> LevelManager::getPatrollerEnemiesPositions()
{
	return m_PatrollerEnemiesPositions;
}
// Returns positions jumping of chaser enemies
const vector<Vector2f> LevelManager::getJumpingEnemiesPositions()
{
	return m_JumpingEnemiesPositions;
}

// Returns positions of chaser enemies
const vector<Vector2f> LevelManager::getKeyPositions()
{
	return m_KeyPositions;
}
// Returns positions patroller of chaser enemies
const vector<Vector2f> LevelManager::getSpeedBoostPositions()
{
	return m_SpeedBoostPositions;
}
// Returns positions jumping of chaser enemies
const vector<Vector2f> LevelManager::getCoinPositions()
{
	return m_CoinPositions;
}

float LevelManager::getTimeLimit()
{
	return m_BaseTimeLimit * m_TimeModifier;

}
Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}

// Returns the current score
int LevelManager::getScore() {
	return  m_Score;
}

// Sets the current score
void LevelManager::setScore(int score) {
	m_Score = score;
}

// Returns the amount of coins collected
int LevelManager::getCoinsCollected() {
	return m_CoinsCollected;
}

// Sets the amount of coins collected
void LevelManager::setCoinsCollected(int coins) {
	m_CoinsCollected = coins;
}

int LevelManager::getTileType(char tile) {
	switch (tile) {
	case '5': return 5;  // Chaser Enemy
	case '6': return 6;  // Patroller Enemy
	case '7': return 7;  // Jumping Enemy
	case '8': return 8;  // Key
	case '9': return 9;  // Speed Boost
	case 'C': return 10; // Coin
	}
}