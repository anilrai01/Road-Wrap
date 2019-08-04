#include <SFML/Graphics.hpp>
using namespace sf;

#include<iostream>
using namespace std;

#include<sstream>

#include "Player.h"

#include "Enemy.h"

#include "Explosion.h"


//Creat random Number for game loop
int getRandomNumber(int a, int b, char ch);
string getRandomImage();

int main() {

	//In Game variables for game loop
	float maxSpeed = 10.0f;
	float speed = 0;
	float bgAcc = 0.005f;
	float BackgroundY1 = 0;
	float BackgroundY2 = -1080.0f;
	float BackgroundY3 = -2160.0f;
	float borderRight = 0;
	float borderLeft = 705.0f;


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

	if (bgCover.loadFromFile("images/bgCover.png")) 
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
	
	//Player Object
	Player racer("images/Car.png", 985, 900);

	//Enemies Objects
	Enemy en1(getRandomImage(), getRandomNumber(705, 805, 'e'), getRandomNumber(-1500, -1700, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en2(getRandomImage(), getRandomNumber(815, 915, 'e'), getRandomNumber(-1800, -2000, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en3("images/obs3.png", getRandomNumber(925, 1025, 'e'), getRandomNumber(-2200, -2400, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en4("images/obs4.png", getRandomNumber(1035, 1135, 'e'), getRandomNumber(-2500, -2700, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en5("images/obs1.png", getRandomNumber(1145, 1245, 'e'), getRandomNumber(-2800, -3000, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en6("images/obs3.png", getRandomNumber(1255, 1285, 'e'), getRandomNumber(-3100, -3300, 'e'), getRandomNumber(3, 8, 's'));


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


		// Regeneration of Enemy
		//cout << en1.getPosY() << endl;
		if (en1.getPosY() > 1080) {
			en1.setPosY(getRandomNumber(-1500, -1700, 'e'));
			en1.setNewTexture(getRandomImage());
			en1.setSpeed(getRandomNumber(3, 8, 's'));
		}
		if (en2.getPosY() > 1080) {
			en2.setPosY(getRandomNumber(-1800, -2000, 'e'));
			en2.setNewTexture(getRandomImage());
			en2.setSpeed(getRandomNumber(3, 8, 's'));
		}
		if (en3.getPosY() > 1080) {
			en3.setPosY(getRandomNumber(-2100, -2300, 'e'));
			en3.setNewTexture(getRandomImage());
			en3.setSpeed(getRandomNumber(3, 8, 's'));
		}
		if (en4.getPosY() > 1080) {
			en4.setPosY(getRandomNumber(-2400, -2600, 'e'));
			en4.setNewTexture(getRandomImage());
			en4.setSpeed(getRandomNumber(3, 8, 's'));
		}
		if (en5.getPosY() > 1080) {
			en5.setPosY(getRandomNumber(-2700, -2900, 'e'));
			en5.setNewTexture(getRandomImage());
			en5.setSpeed(getRandomNumber(3, 8, 's'));
		}
		if (en6.getPosY() > 1080) {
			en6.setPosY(getRandomNumber(-3000, -3200, 'e'));
			en6.setNewTexture(getRandomImage());
			en6.setSpeed(getRandomNumber(3, 8, 's'));
		}
		/*
		if (en7.getPosY() > 1080) {
			en7.setPosY(getRandomNumber(-3300, -3500, 'e'));
			en7.setNewTexture(getRandomImage());
			en7.setSpeed(getRandomNumber(3, 6, 's'));
		}
		if (en8.getPosY() > 1080) {
			en8.setPosY(getRandomNumber(-3600, -3800, 'e'));
			en8.setNewTexture(getRandomImage());
			en8.setSpeed(getRandomNumber(3, 6, 's'));
		}
		*/

		//Clearing and creating windows
		window.clear();

		window.draw(mainCover);
		window.draw(mainBG);
		window.draw(mainBG2);
		window.draw(mainBG3);
		
		//Render Player Object
		racer.drawPlayer(window);

		//Render Enemies
		en1.drawEnemy(window);
		en2.drawEnemy(window);
		en3.drawEnemy(window);
		en4.drawEnemy(window);
		en5.drawEnemy(window);
		en6.drawEnemy(window);
		//en7.drawEnemy(window);
		//en8.drawEnemy(window);
	
		//Draw explosion
		explode.drawExplosion(window);
	
		window.display();
	}
}

int getRandomNumber(int a, int b, char ch)
{
	static bool first = true; if (first) { srand(time(NULL)); first = false; }
	int result = a + rand() % ((b + 1) - a);
	if (ch == 'e') {
		result = (result / 10) * 10;
		return result;
	}
	else if (ch == 'i' || ch == 's') {
		return result;
	}
	return result;
}

string getRandomImage() {
	stringstream ss;
	ss << getRandomNumber(1, 4, 'i');
	string imgTag = ss.str();

	string imgDir = "images/obs" + imgTag + ".png";
	//cout << imgDir;

	return imgDir;
}