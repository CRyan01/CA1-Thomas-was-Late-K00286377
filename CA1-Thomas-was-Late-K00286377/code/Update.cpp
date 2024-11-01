#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		// These calls to spawn will be moved to a new
		// LoadLevel function soon
		// Spawn Thomas and Bob
		//m_Thomas.spawn(Vector2f(0,0), GRAVITY);
		//m_Bob.spawn(Vector2f(100, 0), GRAVITY);

		// Make sure spawn is called only once
		//m_TimeRemaining = 10;
		//m_NewLevelRequired = false;

		// Load a level
		loadLevel();
		
	}

	if (m_Playing)
	{
		// Update Thomas
		m_Thomas.update(dtAsSeconds);

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (detectCollisions(m_Thomas))
		{
			// Store the score for the current level
			int currentLevel = m_LM.getCurrentLevel() - 1;
			m_LevelScores[currentLevel] = m_LM.getScore();

			if (m_LM.getCurrentLevel() == 3) {
				// Display the scoreboard
				displayScoreboard();
				m_Playing = false;
			} else {
				// New level required
				m_NewLevelRequired = true;

				// Play the reach goal sound
				m_SM.playReachGoal();
			}
		}

		// Update the chaser enemies
		for (auto& enemy : m_ChaserEnemies) {
			enemy.update(dtAsSeconds, m_Thomas);
		}

		// Update the patroller enemies
		for (auto& enemy : m_PatrollerEnemies) {
			enemy.update(dtAsSeconds, m_Thomas);
		}

		// Update the jumping enemies
		for (auto& enemy : m_JumpingEnemies) {
			enemy.update(dtAsSeconds, m_Thomas);
		}

		// Apply any active effects
		m_Thomas.updateEffects(dtAsSeconds);

		// Update the timer
		m_ElapsedTime += dtAsSeconds;

	}// End if playing

	// Check if a fire sound needs to be played
	vector<Vector2f>::iterator it;

	// Iterate through the vector of Vector2f objects
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		// Where is this emitter?
		// Store the location in pos
		float posX = (*it).x;
		float posY = (*it).y;

		// is the emiter near the player?
		// Make a 500 pixel rectangle around the emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// Is the player inside localRect?
		if (m_Thomas.getPosition().intersects(localRect))
		{
			// Play the sound and pass in the location as well
			m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}
	}
	// Centre full screen around character
	m_MainView.setCenter(m_Thomas.getCenter());

	// Time to update the HUD?
	// Increment the number of frames since the last HUD calculation
	m_FramesSinceLastHUDUpdate++;

	// Update the HUD every m_TargetFramesPerHUDUpdate frames
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{

		// Update the score
		calculateScore();

		// Update game HUD text
		stringstream ssTime;
		stringstream ssLevel;
		stringstream ssCoins;
		stringstream ssScore;

		// Update the time text
		ssTime << "Time:" << (int)m_ElapsedTime;
		m_Hud.setTime(ssTime.str());

		// Update the level text
		ssLevel << "Level:" << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		// Update the score text
		ssScore << "Score:" << m_LM.getScore();
		m_Hud.setScore(ssScore.str());

		// Update the coins text
		ssCoins << "Coins:" << m_LM.getCoinsCollected();
		m_Hud.setCoins(ssCoins.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update the particles
	if (m_PS.running())
	{
		m_PS.update(dtAsSeconds);
	}
}// End of update function

// Calculate the players score based on coins collected
void Engine::calculateScore()
{
	// 100 extra points per coin
	int score = m_LM.getCoinsCollected() * 100;

	// Update the total score
	m_LM.setScore(score);
}

// Display score from each level
void Engine::displayScoreboard()
{
	// Create a string with the scores
	std::stringstream ss;
	ss << "Level Scores:\n";
	for (int i = 0; i < m_LevelScores.size(); ++i) {
		ss << "Level " << (i + 1) << ": " << m_LevelScores[i] << "\n";
	}

	// Display summary in text object
	m_Hud.setScoreboard(ss.str());
}