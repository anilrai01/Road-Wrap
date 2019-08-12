#include <SFML/Graphics.hpp>
using namespace sf;

#include <SFML/Audio.hpp>

#include <iostream>
using namespace std;

#include <cmath>

#include <sstream>

#include <vector>

#include "Player.h"

#include "Enemy.h"

#include "Explosion.h"

#include "Bullet.h"

//Creat random Number for game loop
int getRandomNumber(int a, int b, char ch);
string getRandomImage();

//Measures distance between any two points in the vertices
float getDistance(float, float, int, int);

//regenerate
void setNewPosition(Enemy& enem, int num, int speed);

int main() {
	//In Game variables for game loop
	float maxSpeed = 5.0f;
	float speed = 0;
	float bgAcc = 0.01f;
	float bgDcc = 0.03f;
	float BackgroundY1 = 0;
	float BackgroundY2 = -1080.0f;
	float BackgroundY3 = -2160.0f;
	float borderRight = 0;
	float borderLeft = 705.0f;
	float score = 0;
	//Enemy max lim
	int oppMaxSpeed = 5;
	//player Collision stats
	bool collided = false;
	//Bullet stats
	bool fire = false;
	//Enemy collision stat
	bool bulletCollide = false;

	//Explosion vector
	vector<Explosion> explode;
	//Bullet Vector
	vector<Bullet> bullet;
	//EnemyExplode Vector
	vector<Explosion> enemyExplode;

	//Sound Buffer
	SoundBuffer fireBuffer;

	//Sound 
	Sound fireSound;

	RenderWindow window(VideoMode(1920, 1080), "Drift Race", sf::Style::Close | sf::Style::Titlebar);
	//window.setFramerateLimit(90);

	Texture bg1, bg2, bg3, bgCover, bombTxt, bulletTxt;

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
		cout << "File 2 Loaded Successfully" << endl;
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
	if (bombTxt.loadFromFile("images/type_C.png"))
	{
		cout << "Bomb Cover loaded Successfully";
		bombTxt.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}
	if (bulletTxt.loadFromFile("images/fire_red.png"))
	{
		cout << "Bomb Cover loaded Successfully";
		bulletTxt.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}



	/// Testing Sound
	if (!fireBuffer.loadFromFile("sounds/bulletShot.wav")) {
		cout << "Error Loading Sound" << endl;
	}

	//Setting Sounds
	fireSound.setBuffer(fireBuffer);

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
	Enemy en2(getRandomImage(), getRandomNumber(855, 955, 'e'), getRandomNumber(-1800, -2000, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en3(getRandomImage(), getRandomNumber(1005, 1055, 'e'), getRandomNumber(-2200, -2400, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en4(getRandomImage(), getRandomNumber(1105, 1155, 'e'), getRandomNumber(-2500, -2700, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en5(getRandomImage(), getRandomNumber(1205, 1255, 'e'), getRandomNumber(-2800, -3000, 'e'), getRandomNumber(3, 8, 's'));
	/*
	enemVect.push_back(Enemy(getRandomImage(), getRandomNumber(705, 805, 'e'), getRandomNumber(-1500, -1700, 'e'), getRandomNumber(3, 8, 's')));
	enemVect.push_back(Enemy(getRandomImage(), getRandomNumber(815, 915, 'e'), getRandomNumber(-1800, -2000, 'e'), getRandomNumber(3, 8, 's')));
	enemVect.push_back(Enemy(getRandomImage(), getRandomNumber(925, 1025, 'e'), getRandomNumber(-2200, -2400, 'e'), getRandomNumber(3, 8, 's')));
	*/



	//Loading Window  main Game LOOP
	while (window.isOpen()) {
		Event evnt;

		while (window.pollEvent(evnt)) {

			switch (evnt.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (evnt.key.code == Keyboard::Space) 
				{
					cout << "Fired";
					fire = true;
					bullet.push_back(Bullet(bulletTxt, (int)racer.getPosX(), (int)racer.getPosY(), 32, 64, 16, 0.25));
					fireSound.play();
				}
				break;
			}

			
		}

		if (!collided) {
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
			setNewPosition(en1, 1, oppMaxSpeed);
			score++;
		}
		if (en2.getPosY() > 1080) {
			setNewPosition(en2, 2, oppMaxSpeed);
			score++;
		}
		if (en3.getPosY() > 1080) {
			setNewPosition(en3, 3, oppMaxSpeed);
			score++;
		}
		if (en4.getPosY() > 1080) {
			setNewPosition(en4, 4, oppMaxSpeed);
			score++;
		}
		if (en5.getPosY() > 1080) {
			setNewPosition(en5, 5, oppMaxSpeed);
			score++;
		}

		// Game Level
		if (score > 25 && score < 150) { cout << "Level Up";  maxSpeed = 7; oppMaxSpeed = 7; };
		if (score > 150 && score < 200) { cout << "Level Up";  maxSpeed = 9; oppMaxSpeed = 9; };
		if (score > 200 && score < 250) { cout << "Level Up";  maxSpeed = 11; oppMaxSpeed = 11; };


		//Check collission of player and enemy
		if (!collided) {
			if (getDistance(racer.getPosX(), racer.getPosY(), en1.getPosX(), en1.getPosY()) < 60 ||
				getDistance(racer.getPosX(), racer.getPosY(), en2.getPosX(), en2.getPosY()) < 60 ||
				getDistance(racer.getPosX(), racer.getPosY(), en3.getPosX(), en3.getPosY()) < 60 ||
				getDistance(racer.getPosX(), racer.getPosY(), en4.getPosX(), en4.getPosY()) < 60 ||
				getDistance(racer.getPosX(), racer.getPosY(), en5.getPosX(), en5.getPosY()) < 60)
			{
				collided = true;
				cout << "Collided";
				explode.push_back(Explosion(bombTxt, (int)racer.getPosX() - 170, (int)racer.getPosY() - 150, 256, 256, 48, 0.25));
				racer.setLife(racer.getLife() - 1);
			}
		}

		// Check collission of bullet and enemy
		//if (!enemyExplode.empty()) {
			for (int i = 0; i < bullet.size(); i++) {
				if (getDistance(bullet[i].getPosX(), bullet[i].getPosY(), en1.getPosX(), en1.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en1.getPosX() - 170, (int)en1.getPosY() - 150, 256, 256, 48, 0.25));
					setNewPosition(en1, 1, oppMaxSpeed);
				}
				if (getDistance(bullet[i].getPosX(), bullet[i].getPosY(), en2.getPosX(), en2.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en2.getPosX() - 170, (int)en2.getPosY() - 150, 256, 256, 48, 0.25));
					setNewPosition(en2, 2, oppMaxSpeed);
				}
				if (getDistance(bullet[i].getPosX(), bullet[i].getPosY(), en3.getPosX(), en3.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en3.getPosX() - 170, (int)en3.getPosY() - 150, 256, 256, 48, 0.25));
					setNewPosition(en3, 3, oppMaxSpeed);
				}
				if(getDistance(bullet[i].getPosX(), bullet[i].getPosY(), en4.getPosX(), en4.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en4.getPosX() - 170, (int)en4.getPosY() - 150, 256, 256, 48, 0.25));
					setNewPosition(en4, 4, oppMaxSpeed);
				}
				if (getDistance(bullet[i].getPosX(), bullet[i].getPosY(), en5.getPosX(), en5.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en5.getPosX() - 170, (int)en5.getPosY() - 150, 256, 256, 48, 0.25));
					setNewPosition(en5, 5, oppMaxSpeed);
				}
			}
		//}

		/// Player Collided
		if (collided) {
			// Slow start simulation
			if (speed > 0) {
				speed -= bgDcc;
			}

			BackgroundY1 += speed;
			BackgroundY2 += speed;
			BackgroundY3 += speed;
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
		en3.drawEnemy(window);
		en4.drawEnemy(window);
		en5.drawEnemy(window);

		//en6.drawEnemy(window);

		//Explosion
		if (collided) {

			for (int i = 0; i < explode.size(); i++) {
				explode[i].update();
				window.draw(explode[i].sprite);
				if (explode[i].isEnd()) {
					/*if (explode.size() > 1) {
						swap(explode.front(), explode.end());
					}*/
					explode.pop_back(); collided = false;
				};
			}
		}

		if (fire) {
			for (int i = 0; i < bullet.size(); i++) {
				bullet[i].update();
				window.draw(bullet[i].sprite);
				bullet[i].updateBullet();

				if (bullet[i].getPosY() < 0) {
					bullet.erase(bullet.begin() + 0);
				}
			}

			if (bullet.empty()) {
				fire = false;
			}
		}

		if (bulletCollide) {
			for (int i = 0; i < enemyExplode.size(); i++) {
				enemyExplode[i].update();
				window.draw(enemyExplode[i].sprite);

				if (enemyExplode[i].isEnd()) {
					enemyExplode.erase(enemyExplode.begin() + 0);
				}
			}
			if (enemyExplode.empty()) {
				bulletCollide = false;
			}
		}

		// Checking Player LifeSpan 
		if (racer.getLife() <= 0) {
			cout << "You Died !";
			window.close();
		}


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

void setNewPosition(Enemy &enem, int num, int speed) {
	if (num == 1) {
		enem.setPosY(getRandomNumber(-1500, -1700, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 2) {
		enem.setPosY(getRandomNumber(-1800, -2000, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 3) {
		enem.setPosY(getRandomNumber(-2100, -2300, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 4) {
		enem.setPosY(getRandomNumber(-2400, -2600, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 5) {
		enem.setPosY(getRandomNumber(-2700, -2900, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}

}