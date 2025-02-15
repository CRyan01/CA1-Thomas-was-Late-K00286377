#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"
#include "ChaserEnemy.h"
#include "PatrollerEnemy.h"
#include "JumpingEnemy.h"
#include "Item.h"
#include "Key.h"
#include "SpeedBoost.h"
#include "Coin.h"

using namespace sf;

class Engine
{
private:
	// The texture holder
	TextureHolder th;

	// create a particle system
	ParticleSystem m_PS;

	// Thomas and his friend, Bob
	Thomas m_Thomas;
	Bob m_Bob;

	// A class to manage all the levels
	LevelManager m_LM;

	// Create a SoundManager
	SoundManager m_SM;

	// The Hud
	Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 140;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	// The force pushing the characters down
	const int GRAVITY = 300;

	// A regular RenderWindow
	RenderWindow m_Window;

	// The main Views
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	// Three views for the background
	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;

	View m_HudView;

	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	// Declare a shader for the background
	Shader m_RippleShader;

	// Is the game currently playing?
	bool m_Playing = false;

	// Is character 1 or 2 the current focus?
	bool m_Character1 = true;

	// Start in full screen mode
	bool m_SplitScreen = false;

	// Game time total
	Time m_GameTimeTotal;

	// Is it time for a new/first level?
	bool m_NewLevelRequired = true;

	// The vertex array for the level design
	VertexArray m_VALevel;

	// The 2d array with the map for the level
	// A pointer to a pointer
	int** m_ArrayLevel = NULL;

	// Texture for the background and the level tiles
	Texture m_TextureTiles;

	// Vectors to store enemies of each type
	vector<ChaserEnemy> m_ChaserEnemies;
	vector<PatrollerEnemy> m_PatrollerEnemies;
	vector<JumpingEnemy> m_JumpingEnemies;

	// Vectors to store enemies of each type
	vector<Key> m_Keys;
	vector<SpeedBoost> m_SpeedBoosts;
	vector<Coin> m_Coins;

	// A vector of scores the player acheieved for each level
	vector<int> m_LevelScores;

	// Params for enemy types
	float chaserEnemySpeed = 100.0f;
	float patrollerEnemySpeed = 100.0f;
	float jumpingEnemySpeed = 100.0f;
	float patrolDistance = 100.0f;
	float jumpCooldown = 4.0f;
	float jumpSpeed = 200.0f;

	// Track time passed in level
	float m_ElapsedTime;

	// Calculate the players score based on time elapsed & coins collected
	void calculateScore();
	
	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();	

	// Load a new level
	void loadLevel();

	// Display the scores for each level
	void displayScoreboard();

	// Run will call all the private functions
	bool detectCollisions(PlayableCharacter& character);
	
	// Make a vector of the best places to emit sounds from
	void populateEmitters(vector <Vector2f>& vSoundEmitters,
		int** arrayLevel);

	// A vector of Vector2f for the fire emiiter locations
	vector <Vector2f> m_FireEmitters;
	
public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();
};
