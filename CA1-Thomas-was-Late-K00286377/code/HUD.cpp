#include "Hud.h"

Hud::Hud()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	m_Font.loadFromFile("fonts/Roboto-Light.ttf");

	// Paused
	m_StartText.setFont(m_Font);
	m_StartText.setCharacterSize(100);
	m_StartText.setFillColor(Color::White);
	m_StartText.setString("Press Enter when ready!");

	// Position the text
	FloatRect textRect = m_StartText.getLocalBounds();

	m_StartText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	m_StartText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);

	// Time
	m_TimeText.setFont(m_Font);
	m_TimeText.setCharacterSize(75);
	m_TimeText.setFillColor(Color::White);
	m_TimeText.setPosition(resolution.x - 400, 0);
	m_TimeText.setString("------");

	// Level
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(75);
	m_LevelText.setFillColor(Color::White);
	m_LevelText.setPosition(25, 0);
	m_LevelText.setString("1");

	// Score
	m_ScoreText.setFont(m_Font);
	m_ScoreText.setCharacterSize(75);
	m_ScoreText.setFillColor(Color::White);
	m_ScoreText.setPosition(resolution.x - 800, 0);
	m_ScoreText.setString("----");

	// Coins
	m_CoinsText.setFont(m_Font);
	m_CoinsText.setCharacterSize(75);
	m_CoinsText.setFillColor(Color::White);
	m_CoinsText.setPosition(resolution.x - 1100, 0);
	m_CoinsText.setString("--");

	// Scoreboard text
	m_ScoreboardText.setFont(m_Font);
	m_ScoreboardText.setCharacterSize(75);
	m_ScoreboardText.setFillColor(Color::Yellow);
	m_ScoreboardText.setString("Scoreboard");

	// Center scoreboard on the screen
	FloatRect scoreboard = m_ScoreboardText.getLocalBounds();
	m_ScoreboardText.setOrigin(scoreboard.left + scoreboard.width / 2.0f, scoreboard.top + scoreboard.height / 2.0f - 200);
	m_ScoreboardText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);
}

Text Hud::getMessage()
{
	return m_StartText;
}

Text Hud::getLevel()
{
	return m_LevelText;
}

// get the score text
Text Hud::getScore() {
	return m_ScoreText;
}

// get the coins text
Text Hud::getCoins() {
	return m_CoinsText;
}
// set the score text
void Hud::setScore(String text) {
	m_ScoreText.setString(text);
}

// set the coins text
void Hud::setCoins(String text) {
	m_CoinsText.setString(text);
}

Text Hud::getScoreboard() {
	return m_ScoreboardText;
}

void Hud::setScoreboard(String summaryText) {
	m_ScoreboardText.setString(summaryText);
}

Text Hud::getTime()
{
	return m_TimeText;
}

void Hud::setLevel(String text)
{
	m_LevelText.setString(text);
}

void Hud::setTime(String text)
{
	m_TimeText.setString(text);
}