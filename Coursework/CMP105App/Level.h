#pragma once

#include "Framework/BaseLevel.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void spawnFood();
	// Default variables for level class.
	bool m_isGameOver = false;
	sf::CircleShape m_player;
	sf::CircleShape m_food;
	float m_speed = 200.f;
	enum class Direction { UP, DOWN, LEFT, RIGHT };
	Direction m_direction;
	int m_points = 0;
	float m_timepassed = 0.f;
};