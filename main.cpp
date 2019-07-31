#include <SFML/Graphics.hpp>
using namespace sf;

#include<iostream>
using namespace std;

int main() {
	RenderWindow window(VideoMode(1920, 1080), "Drift Race", sf::Style::Close | sf::Style::Titlebar);
	RectangleShape player(Vector2f(70, 120));

	Texture tx1, playerText;
	tx1.loadFromFile("images/bgRet.png");
	playerText.loadFromFile("images/Car.png");
	playerText.setSmooth(true);

	//Setting Player
	player.setTexture(&playerText);

	Sprite sp1;
	sp1.setTexture(tx1);
	sp1.setPosition(Vector2f(400, 0));

	float x = 750, y = 900;
	float maxSpeed = 2;
	float speed = 0;
	float acc = 2;

	while (window.isOpen()) {
		Event evnt;

		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case Event::Closed:
				window.close();
				break;
			}
		}

		//bool Up = 0, Right = 0, Down = 0, Left = 0;
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (player.getPosition().y >= 0 + acc) {
				x = x;
				y -= acc;
			}
			
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if ( player.getPosition().x <= 1140 - acc) {
				x += acc;
				y = y;
			}
			
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (player.getPosition().y <= 900 - acc) {
				y += acc;
				x = x;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (player.getPosition().x >= 750 + acc) {
				x -= acc;
				y = y;
			}
		}

		//car movement

		

		window.clear();
		window.draw(sp1);
		player.setPosition(Vector2f(x, y));
		window.draw(player);
		window.display();
	}
}