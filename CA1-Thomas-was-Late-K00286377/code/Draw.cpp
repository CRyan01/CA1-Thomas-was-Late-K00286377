#include "Engine.h"

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);
	
	// Update the shader parameters
	m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());

	// Switch to background view
	m_Window.setView(m_BGMainView);

	// Draw the background
	m_Window.draw(m_BackgroundSprite);

	// Draw the background, complete with shader effect
	m_Window.draw(m_BackgroundSprite, &m_RippleShader);

	// Switch to m_MainView
	m_Window.setView(m_MainView);		

	// Draw the Level
	m_Window.draw(m_VALevel, &m_TextureTiles);

	// Draw thomas
	m_Window.draw(m_Thomas.getSprite());

	// Draw the chaser enemies
	for (const auto& enemy : m_ChaserEnemies) {
		m_Window.draw(enemy.getSprite());
	}

	// Draw the patroller enemies
	for (const auto& enemy : m_PatrollerEnemies) {
		m_Window.draw(enemy.getSprite());
	}

	// Draw the jumping enemies
	for (const auto& enemy : m_JumpingEnemies) {
		m_Window.draw(enemy.getSprite());
	}

	// Draw each item if not collected
	for (const auto& key : m_Keys) key.draw(m_Window);
	for (const auto& speedBoost : m_SpeedBoosts) speedBoost.draw(m_Window);
	for (const auto& coin : m_Coins) coin.draw(m_Window);

	// Draw the particle system
	if (m_PS.running())
	{
		m_Window.draw(m_PS);
	}
	
	// Display the scoreboard after the end of level 3
	if (!m_Playing && m_LM.getCurrentLevel() == 3) {
		m_Window.setView(m_HudView);
		m_Window.draw(m_Hud.getScoreboard());
	} else {
		// Otherwise draw the HUD
		// Switch to m_HudView
		m_Window.setView(m_HudView);
		m_Window.draw(m_Hud.getLevel());
		m_Window.draw(m_Hud.getTime());
		m_Window.draw(m_Hud.getScore());
		m_Window.draw(m_Hud.getCoins());
	}
	if (!m_Playing)
	{
		m_Window.draw(m_Hud.getMessage());
	}
	
	// Show everything we have just drawn
	m_Window.display();
}