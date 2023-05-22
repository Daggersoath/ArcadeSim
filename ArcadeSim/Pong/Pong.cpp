//
// Created by Daggersoath on 18/05/2023.
//

#include "Pong.hpp"

#include <SFML/Graphics.hpp>

#include "Globals.hpp"

enum RectPoints {
	TopLeft,
	BottomLeft,
	TopRight,
	BottomRight
};

using Rect = sf::Vertex[4];

void SetRectPositionSize(Rect& rect, sf::Vector2f pos, sf::Vector2f size)
{
	rect[RectPoints::TopLeft].position = pos;
	rect[RectPoints::TopRight].position = pos + sf::Vector2f(size.x, 0);
	rect[RectPoints::BottomRight].position = pos + size;
	rect[RectPoints::BottomLeft].position = pos + sf::Vector2f(0.f, size.y);
}

void Pong::Start()
{
	sf::RenderWindow window(sf::VideoMode({800, 600}), "ArcadeSim");

	window.setTitle("Pong");

	sf::Font font;
	if (!font.loadFromFile(GLOBALS::DATA_DIR + "/bit5x3.ttf"))
	{
		return;
	}
	sf::Text scoreText[2]{{font, "0", 74}, {font, "0", 74}};

	float xOffset = (float)window.getSize().x * .2f;
	scoreText[0].setPosition({xOffset, 25.f});
	scoreText[1].setPosition({xOffset * 4.f - 74.f, 25.f});

	Rect gameObjects[3];

	sf::Clock clock;
	sf::Clock gameTime;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float time = clock.restart().asSeconds();
		scores[0] = (int)gameTime.getElapsedTime().asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			position[0] += time * paddleSpeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			position[0] -= time * paddleSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			position[1] += time * paddleSpeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			position[1] -= time * paddleSpeed;
		}

		ballPosition[0] += time * ballspeed * ballDirection[0];
		ballPosition[1] += time * ballspeed * ballDirection[1];

		SetRectPositionSize(gameObjects[0], {ballPosition[0], ballPosition[1]}, sf::Vector2f(30.f, 30.f));
		SetRectPositionSize(gameObjects[1], {50.f, position[0]}, sf::Vector2f(30.f, 90.f));
		SetRectPositionSize(gameObjects[2], {(float)window.getSize().x - 80.f, position[1]}, sf::Vector2f(30.f, 90.f));

		scoreText[0].setString(std::to_string(scores[0]));
		scoreText[1].setString(std::to_string(scores[1]));

		window.clear();
		window.draw(scoreText[0]);
		window.draw(scoreText[1]);
		for (auto& gameObject : gameObjects)
		{
			window.draw(gameObject, 4, sf::PrimitiveType::TriangleStrip);
		}

		window.display();
	}
}