#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	Font m_Font;
	Text m_StartText;
	Text m_TimeText;
	Text m_LevelText;
	Text m_ScoreText;
	Text m_CoinsText;
	Text m_ScoreboardText;

public:
	Hud();
	Text getMessage();
	Text getLevel();
	Text getTime();
	Text getScore(); // get the score text
	Text getCoins(); // get the coins text
	Text getScoreboard(); // get the scoreboard text

	void setLevel(String text);
	void setTime(String text);
	void setScore(String text); // set the score text
	void setCoins(String text); // set the coins text
	void setScoreboard(String text); // set the scoreboard text
};