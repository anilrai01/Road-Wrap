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
	Enemy en1(getRandomImage(), getRandomNumber(705, 805, 'e'), getRandomNumber(-1500,-1700, 'e'));
	
	Enemy en2(getRandomImage(), getRandomNumber(810, 905, 'e'), getRandomNumber(-1800, -2000, 'e'));
	/*
	Enemy en3("images/obs3.png", getRandomNumber(915, 1005), getRandomNumber(-2200, -2400));
	Enemy en4("images/obs4.png", getRandomNumber(1015, 1105), getRandomNumber(-2500, -2700));
	Enemy en5("images/obs1.png", getRandomNumber(1115, 1205), getRandomNumber(-2800, -3000));
	Enemy en6("images/obs3.png", getRandomNumber(1215, 1285), getRandomNumber(-3100, -3300));
	*/

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
		}
		if (en2.getPosY() > 1080) {
			en2.setPosY(getRandomNumber(-1800, -2200, 'e'));
			en1.setNewTexture(getRandomImage());
		}

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
		/*
		en3.drawEnemy(window);
		en4.drawEnemy(window);
		en5.drawEnemy(window);
		en6.drawEnemy(window);
		*/
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
	else if (ch == 'i') {
		return result;
	}
	return result;
}

string getRandomImage() {
	stringstream ss;
	ss << getRandomNumber(1, 4, 'i');
	string imgTag = ss.str();

	string imgDir = "images/obs" + imgTag + ".png";
	cout << imgDir;

	return imgDir;
}