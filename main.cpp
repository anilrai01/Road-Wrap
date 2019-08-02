#include <SFML/Graphics.hpp>
using namespace sf;

#include<iostream>
using namespace std;

int main() {
	RenderWindow window(VideoMode(1920, 1080), "Drift Race", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(90);
	RectangleShape player(Vector2f(70, 120));

	Texture bg1, bg2, playerText;
	bg1.loadFromFile("images/groupTemp.png");
	bg1.setSmooth(true);
	bg2.loadFromFile("images/groupShip.png");
	bg2.setSmooth(true);
	

	playerText.loadFromFile("images/Car.png");
	playerText.setSmooth(true);

	//Setting Player Car
	//player.setOrigin(Vector2f(0, 0));
	player.setTexture(&playerText);

	//Setting up a sprite
	Sprite mainBG, mainBG2, trackSp;
	mainBG.setTexture(bg1);
	mainBG2.setTexture(bg2);

	float x = 705, y = 900;
	float maxSpeed = 7;
	float speed = 0;
	float acc = 2;
	float startX = 0, startY = 0;
	float BackgroundY1 = 0;
	float BackgroundY2 = -1080;


	//Loading Window
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
//				startY = 2.2f;
			}
			
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			//cout << player.getPosition().x;
			if ( player.getPosition().x < 1270 - acc) {
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
			//cout << player.getPosition().x;
			if (player.getPosition().x >= 705 + acc) {
				x -= acc;
				y = y;
			}
		}

		//car movement
		//Creat scrolling background
		mainBG.setPosition(Vector2f(320.0f, BackgroundY1));
		mainBG2.setPosition(Vector2f(320.0f, BackgroundY2));
		if (mainBG.getPosition().y >= 1080)
		{
			BackgroundY1 = -1080;
		}
		if (mainBG2.getPosition().y >= 1080) {
			BackgroundY2 = -1080;
		}
		BackgroundY1 += 5.0;
		BackgroundY2 += 5.0;
		

		//Clearing and creating windows
		window.clear();

		window.draw(mainBG);
		window.draw(mainBG2);
		
		player.setPosition(Vector2f(x, y));
		window.draw(player);
		
		window.display();
	}
}
