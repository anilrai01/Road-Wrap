#include <SFML/Graphics.hpp>
using namespace sf;

#include<iostream>
using namespace std;

#include "Player.h";

#include "Explosion.h";

int main() {
	RenderWindow window(VideoMode(1920, 1080), "Drift Race", sf::Style::Close | sf::Style::Titlebar);
	//window.setFramerateLimit(90);

	Texture bg1, bg2, bg3, bgCover;

	if (bg1.loadFromFile("images/Group1.png"))
	{
		cout << "File 1 Loaded Successfully" << endl;
		bg1.setSmooth(true);
	}
	else {
		cout << "Error Loading File 1" << endl;
	}
	
	if (bg2.loadFromFile("images/Group2.png"))
	{
		cout << "File 2 Loaded Successfully"<<endl;
		bg2.setSmooth(true);
	}
	else {
		cout << "Error Loading File 2" << endl;
	}
	if (bg3.loadFromFile("images/Group3.png"))
	{
		cout << "File 3 Loaded Successfully" << endl;
		bg3.setSmooth(true);
	}
	else {
		cout << "Error Loading File 3" << endl;
	}

	if (bgCover.loadFromFile("images/testBG.png")) 
	{
		cout << "Files Cover loaded Successfully";
		bgCover.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}


	//Setting up a sprite
	Sprite mainBG, mainBG2, mainBG3, mainCover, explodeSpr;
	mainBG.setTexture(bg1);
	mainBG2.setTexture(bg2);
	mainBG3.setTexture(bg3);
	mainCover.setTexture(bgCover);

	
	float maxSpeed = 10.0f;
	float speed = 0;
	float bgAcc = 0.005f;
	float BackgroundY1 = 0;
	float BackgroundY2 = -1080.0f;
	float BackgroundY3 = -2160.0f;
	
	//Player Object
	Player racer("images/Car.png", 705.0f, 900.0f);
	//Explosion Object
	Explosion explode(800, 500);

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
	
		//player movement

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			racer.movePlayer('u');
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			racer.movePlayer('r');
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			racer.movePlayer('d');
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			racer.movePlayer('l');
		}

		//Create scrolling background
		mainBG.setPosition(Vector2f(320.0f, BackgroundY1));
		mainBG2.setPosition(Vector2f(320.0f, BackgroundY2));
		mainBG3.setPosition(Vector2f(320.0f, BackgroundY3));
		//Cover up
		mainCover.setPosition(Vector2f(320.0f, 0));

		if (mainBG.getPosition().y >= 1080)
		{
			BackgroundY1 = -2160.0f;
		}
		if (mainBG2.getPosition().y >= 1080) {
			BackgroundY2 = -2160.0f;
		}
		if (mainBG3.getPosition().y >= 1080) {
			BackgroundY3 = -2160.0f;
		}

		if (speed <= maxSpeed) {
			//cout << "True";
			speed += bgAcc;
		}
		
		BackgroundY1 += speed;
		BackgroundY2 += speed;
		BackgroundY3 += speed;

		//Clearing and creating windows
		window.clear();

		window.draw(mainCover);
		window.draw(mainBG);
		window.draw(mainBG2);
		window.draw(mainBG3);
		
		//Render Player Object
		racer.drawPlayer(window);

		//Draw explosion
		explode.drawExplosion(window);
	
		window.display();
	}
}
