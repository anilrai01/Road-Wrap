#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
using namespace std;

#include <cmath>

#include <sstream>

#include <vector>

#include "Player.h"

#include "Enemy.h"

#include "Explosion.h"


//Creat random Number for game loop
int getRandomNumber(int a, int b, char ch);
string getRandomImage();

//Measures distance between any two points in the vertices
float getDistance(float, float, int, int);

int main() {
	//In Game variables for game loop
	float maxSpeed = 5.0f;
	float speed = 0;
	float bgAcc = 0.005f;
	float bgDcc = 0.005f;
	float BackgroundY1 = 0;
	float BackgroundY2 = -1080.0f;
	float BackgroundY3 = -2160.0f;
	float borderRight = 0;
	float borderLeft = 705.0f;
	float score = 0;
	//Enemy max lim
	int oppMaxSpeed = 5;
	//Collision stats
	bool collided = false;
	//Explosion vector
	vector<Explosion> exp;

	RenderWindow window(VideoMode(1920, 1080), "Drift Race", sf::Style::Close | sf::Style::Titlebar);
	//window.setFramerateLimit(90);

	Texture bg1, bg2, bg3, bgCover, bombTxt;

	if (bg1.loadFromFile("images/new1.png"))
	{
		cout << "File 1 Loaded Successfully" << endl;
		bg1.setSmooth(true);
	}
	else {
		cout << "Error Loading File 1" << endl;
	}
	
	if (bg2.loadFromFile("images/new2.png"))
	{
		cout << "File 2 Loaded Successfully"<<endl;
		bg2.setSmooth(true);
	}
	else {
		cout << "Error Loading File 2" << endl;
	}
	if (bg3.loadFromFile("images/new3.png"))
	{
		cout << "File 3 Loaded Successfully" << endl;
		bg3.setSmooth(true);
	}
	else {
		cout << "Error Loading File 3" << endl;
	}

	if (bgCover.loadFromFile("images/newBg.png")) 
	{
		cout << "Files Cover loaded Successfully";
		bgCover.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}
	if (bombTxt.loadFromFile("images/type_B.png"))
	{
		cout << "Bomb Cover loaded Successfully";
		bombTxt.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}


	//Setting up a sprite
	Sprite mainBG, mainBG2, mainBG3, mainCover;
	mainBG.setTexture(bg1);
	mainBG2.setTexture(bg2);
	mainBG3.setTexture(bg3);
	mainCover.setTexture(bgCover);
	//bombSpr.setTexture(bombTxt);
	
	//Player Object
	Player racer("images/Car.png", 985, 900);

	//Enemies Objects
	Enemy en1(getRandomImage(), getRandomNumber(705, 805, 'e'), getRandomNumber(-1500, -1700, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en2(getRandomImage(), getRandomNumber(815, 915, 'e'), getRandomNumber(-1800, -2000, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en3(getRandomImage(), getRandomNumber(925, 1025, 'e'), getRandomNumber(-2200, -2400, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en4(getRandomImage(), getRandomNumber(1035, 1135, 'e'), getRandomNumber(-2500, -2700, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en5(getRandomImage(), getRandomNumber(1145, 1245, 'e'), getRandomNumber(-2800, -3000, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en6(getRandomImage(), getRandomNumber(1255, 1285, 'e'), getRandomNumber(-3100, -3300, 'e'), getRandomNumber(3, 8, 's'));
	/*
	enemVect.push_back(Enemy(getRandomImage(), getRandomNumber(705, 805, 'e'), getRandomNumber(-1500, -1700, 'e'), getRandomNumber(3, 8, 's')));
	enemVect.push_back(Enemy(getRandomImage(), getRandomNumber(815, 915, 'e'), getRandomNumber(-1800, -2000, 'e'), getRandomNumber(3, 8, 's')));
	enemVect.push_back(Enemy(getRandomImage(), getRandomNumber(925, 1025, 'e'), getRandomNumber(-2200, -2400, 'e'), getRandomNumber(3, 8, 's')));
	*/

	Explosion explode(bombTxt, 0, 0, 192, 192, 64, 0.25);

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

			//If not collided
			if (!collided) {
				// Slow start simulation
				if (speed <= maxSpeed) {
					//cout << "True";
					speed += bgAcc;
				}

				BackgroundY1 += speed;
				BackgroundY2 += speed;
				BackgroundY3 += speed;
			}

			// Regeneration of Enemy
			//cout << en1.getPosY() << endl;

			if (en1.getPosY() > 1080) {
				en1.setPosY(getRandomNumber(-1500, -1700, 'e'));
				en1.setNewTexture(getRandomImage());
				en1.setSpeed(getRandomNumber(3, oppMaxSpeed, 's'));
				score++;
			}
			if (en2.getPosY() > 1080) {
				en2.setPosY(getRandomNumber(-1800, -2000, 'e'));
				en2.setNewTexture(getRandomImage());
				en2.setSpeed(getRandomNumber(3, oppMaxSpeed, 's'));
				score++;
			}
			if (en3.getPosY() > 1080) {
				en3.setPosY(getRandomNumber(-2100, -2300, 'e'));
				en3.setNewTexture(getRandomImage());
				en3.setSpeed(getRandomNumber(3, oppMaxSpeed, 's'));
				score++;
			}
			if (en4.getPosY() > 1080) {
				en4.setPosY(getRandomNumber(-2400, -2600, 'e'));
				en4.setNewTexture(getRandomImage());
				en4.setSpeed(getRandomNumber(3, oppMaxSpeed, 's'));
				score++;
			}
			if (en5.getPosY() > 1080) {
				en5.setPosY(getRandomNumber(-2700, -2900, 'e'));
				en5.setNewTexture(getRandomImage());
				en5.setSpeed(getRandomNumber(3, oppMaxSpeed, 's'));
				score++;
			}
			if (en6.getPosY() > 1080) {
				en6.setPosY(getRandomNumber(-3000, -3200, 'e'));
				en6.setNewTexture(getRandomImage());
				en6.setSpeed(getRandomNumber(3, oppMaxSpeed, 's'));
				score++;
			}

		// Game Level
			if (score > 50 && score < 150) { cout << "Level Up";  maxSpeed = 7; oppMaxSpeed = 7; };
		if (score > 150 && score < 200) { cout << "Level Up";  maxSpeed = 9; oppMaxSpeed = 9; };
		if (score > 200 && score < 250) { cout << "Level Up";  maxSpeed = 11; oppMaxSpeed = 11; };
	

		//Check collission
		if (!collided) {
			if (getDistance(racer.getPosX(), racer.getPosY(), en1.getPosX(), en1.getPosY()) < 50 ||
				getDistance(racer.getPosX(), racer.getPosY(), en2.getPosX(), en2.getPosY()) < 50 ||
				getDistance(racer.getPosX(), racer.getPosY(), en3.getPosX(), en3.getPosY()) < 50 ||
				getDistance(racer.getPosX(), racer.getPosY(), en4.getPosX(), en4.getPosY()) < 50 ||
				getDistance(racer.getPosX(), racer.getPosY(), en5.getPosX(), en5.getPosY()) < 50 ||
				getDistance(racer.getPosX(), racer.getPosY(), en6.getPosX(), en6.getPosY()) < 50)
			{
				collided = true;
				cout << "Collided";
			}
		}
			/// Player Scratched
			if (collided) {
				// Slow start simulation
				if (speed > 0) {
					//cout << "True";
					speed -= bgAcc;
					explode.sprite.setPosition(racer.getPosX() + 30, racer.getPosY() + 50);
				}
				else {
					collided = false;
					racer.setDeg();
				}

				BackgroundY1 += speed;
				BackgroundY2 += speed;
				BackgroundY3 += speed;
			}
			//playerCollided('right');


			
		//Clearing and creating windows
		window.clear();

		window.draw(mainCover);
		window.draw(mainBG);
		window.draw(mainBG2);
		window.draw(mainBG3);


		

		//Render Player Object
		racer.drawPlayer(window);

		//Explosion
		explode.update();
		
		window.draw(explode.sprite);

		//Render Enemies

		en1.drawEnemy(window);
		en2.drawEnemy(window);
		en3.drawEnemy(window);
		en4.drawEnemy(window);
		en5.drawEnemy(window);
		en6.drawEnemy(window);


		/*
		for (int i = 0; i < enemVect.size(); i++) {
			enemVect[i].drawEnemy(window);
		}
		*/
	
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

float getDistance(float x1, float y1, int x2, int y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
