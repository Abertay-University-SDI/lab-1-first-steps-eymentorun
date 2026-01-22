#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_player.setRadius(10);
	m_player.setFillColor(sf::Color::Red);
	m_player.setPosition({ 300,300 });

	m_food.setRadius(5);
	m_food.setFillColor(sf::Color::Green);
	spawnFood();

}

void Level::spawnFood() 
{
	float rand_x = rand() % m_window.getSize().x;
	float rand_y = rand() % m_window.getSize().y;

	m_food.setPosition({ rand_x, rand_y });
}

// handle user input
void Level::handleInput(float dt)
{
	if (m_input.isLeftMousePressed())
	{
		std::cout << "left mouse pressed" << std::endl;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::D))
	{
		m_direction = Direction::RIGHT;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::A))
	{
		m_direction = Direction::LEFT;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
	{
		m_direction = Direction::UP;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
	{
		m_direction = Direction::DOWN;
	}

}

// Update game objects
void Level::update(float dt)
{
	m_timepassed += dt;
	if (m_isGameOver) { return; }
	sf::Vector2f pos = m_player.getPosition();
	sf::Vector2u win_size = m_window.getSize();
	float radius = m_player.getRadius();
	if (pos.x > win_size.x - radius * 2 || pos.x < 0) 
	{
		m_isGameOver = true;
		std::cout << "GAME  OVER\n" << "Score: " << m_points;
		std::cout << "\nTime: " << m_timepassed;
	}
	if (pos.y > win_size.y - radius * 2 || pos.y < 0)
	{
		m_isGameOver = true;
		std::cout << "GAME  OVER\n" << "Score: " << m_points;
		std::cout << "\nTime: " << m_timepassed;
	}
	switch (m_direction)
	{
	case Direction::UP:
		m_player.move({ 0.f,  -m_speed * dt });
		break;
	case Direction::DOWN:
		m_player.move({ 0.f,  m_speed * dt });
		break;
	case Direction::LEFT:
		m_player.move({ -m_speed * dt, 0.f });
		break;
	case Direction::RIGHT:
		m_player.move({ m_speed * dt, 0.f });
		break;
	}

	float x_dist = (pos.x + radius) - (m_food.getPosition().x + m_food.getRadius());
	float y_dist = (pos.y + radius) - (m_food.getPosition().y + m_food.getRadius());

	float squared_dist = (x_dist * x_dist) + (y_dist * y_dist);
	float radii_sum = radius + m_food.getRadius();
	if (squared_dist < radii_sum * radii_sum)
	{
		m_points += 1;
		spawnFood();
		m_speed *= 1.1f;
	}
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_food);
	m_window.draw(m_player);
	endDraw();
}

