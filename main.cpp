#include <SFML/Graphics.hpp>
using namespace sf;

#include <SFML/Audio.hpp>

#include <iostream>
using namespace std;

#include <string>

#include <fstream>

#include <cmath>

#include <sstream>

#include <vector>

#include <algorithm>

#include "Animation.h"

#include "Player.h"

#include "Enemy.h"

#include "Explosion.h"

#include "Bullet.h"

#include "Coin.h"

#include "Obstacle.h"

#include "PowerUP.h"

//Creat random Number for game loop
int getRandomNumber(int a, int b, char ch);

string getRandomImage();

//Measures distance between any two points in the vertices
float getDistance(float, float, int, int);

//regenerate enemy
void setEnemNewPosition(Enemy& enem, int num, int speed);

//respawn coin
void setCoinNewPosition(Coin& , int );

// DISTANCE BETWEEN COIN AND PLAYER
float getCPdistance(Coin& , Player& );

//Distance between obstacle and player
int getOPDistance(Obstacle&, Player&);

//Distance between powerup and player
float getPPdistance(PowerUP& pp, Player& p);

int main() {
	//In Game variables for game loop
	string lineFile;
	string currentHighScore;
	float maxSpeed = 5.0f;
	float speed = 0;
	float bgAcc = 0.01f;
	float bgDcc = 0.03f;
	float BackgroundY1 = 0;
	float BackgroundY2 = -1080.0f;
	float BackgroundY3 = -2160.0f;
	float BackgroundY4 = -3240.0f;
	float BackgroundY5 = -4320.0f;
	float borderRight = 0;
	float borderLeft = 705.0f;
	float score = 0;
	int bulletCount = 10;

	Clock clock;
	float beginTime = clock.getElapsedTime().asSeconds();
	
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
	//Coin vector
	vector<Coin> coinVect;
	//Obstacle Vector
	vector<Obstacle> obsVect;

	///////Sound Buffer
	SoundBuffer fireBuffer, coinPick, carBuffer, carCrashBuffer, powerDown, powerUPSoundBuffer;
	//Sound 
	Sound fireSound, coinSound, carSound, carCrash, powerDownSound, powerUPSound;
	/// Testing Sound
	if (!fireBuffer.loadFromFile("sounds/NFF-laser.wav")) {
		cout << "Error Loading Sound" << endl;
	}
	if (!coinPick.loadFromFile("sounds/Pickup_Coin.wav")) {
		cout << "Error Loading Sound" << endl;
	}
	if (!carBuffer.loadFromFile("sounds/Car-Theft-101.wav")) {
		cout << "Error loading Car Sound";
	}
	else {
		cout << "Car sound loaded successfully" << endl;
	}
	if (!carCrashBuffer.loadFromFile("sounds/EXPLOSION Bang 04.wav")) {
		cout << "Error loading Car start Sound";
	}
	if (!powerDown.loadFromFile("sounds/NEGATIVE Failure Descending Chime 05.wav")) {
		cout << "Error loading Car start Sound";
	}
	if (!powerUPSoundBuffer.loadFromFile("sounds/SUCCESS PICKUP Collect Chime 01.wav")) {
		cout << "Error loading powerup sound";
	}
	//Setting Sounds
	fireSound.setBuffer(fireBuffer);
	coinSound.setBuffer(coinPick);
	carSound.setBuffer(carBuffer);
	carCrash.setBuffer(carCrashBuffer);
	powerDownSound.setBuffer(powerDown);
	powerUPSound.setBuffer(powerUPSoundBuffer);

	/// Play main Sound
	carSound.play();
	carSound.setVolume(0);
	carSound.setLoop(true);
	/*
	carStart.play();
	carStart.setVolume(0);
	carStart.setLoop(true);
	*/

	/////////Fonts
	Font normalFont;
	if (!normalFont.loadFromFile("fonts/PaladinsCondensed-rB77.otf")) {
		cout << "Error loading Score Font";
	}

	//Text
	Text scoreText, highScoreText, lifeText, bulletText;
	scoreText.setFont(normalFont);
	highScoreText.setFont(normalFont);
	lifeText.setFont(normalFont);
	bulletText.setFont(normalFont);

	scoreText.setPosition(Vector2f(1250.0f, 100.0f));
	scoreText.setFillColor(Color::Black);
	highScoreText.setPosition(Vector2f(640.0f, 100.0f));
	highScoreText.setFillColor(Color::Black);
	lifeText.setPosition(Vector2f(880.0f, 100.0f));
	lifeText.setFillColor(Color::Black);
	bulletText.setPosition(Vector2f(980.0f, 100.0f));
	bulletText.setFillColor(Color::Black);

	//stringstream scores;
	ifstream file;
	file.open("highScore.txt");
	if (!file) {
		cout << "Error loading Record";
	}
	//Set life String

	///////////Texture
	Texture bg1, bg2, bg3, bg4, bg5, bgCover, bombTxt, bulletTxt, scoreBoardTxt, coinTexture, obs1Txt, obs2Txt, powerUP;

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
	if (bg4.loadFromFile("images/new4.png"))
	{
		cout << "File 4 Loaded Successfully" << endl;
		bg4.setSmooth(true);
	}
	else {
		cout << "Error Loading File 4" << endl;
	}
	if (bg5.loadFromFile("images/new5.png"))
	{
		cout << "File 5 Loaded Successfully" << endl;
		bg5.setSmooth(true);
	}
	else {
		cout << "Error Loading File 5" << endl;
	}

	if (bgCover.loadFromFile("images/backupBG.png"))
	{
		cout << "BackgroundCover loaded Successfully" << endl;
		bgCover.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}
	if (bombTxt.loadFromFile("images/type_C.png"))
	{
		cout << "Bomb Cover loaded Successfully" <<endl;
		bombTxt.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}
	if (bulletTxt.loadFromFile("images/fire_red.png"))
	{
		cout << "Gun Fire loaded Successfully" <<endl;
		bulletTxt.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}
	if (scoreBoardTxt.loadFromFile("images/scoreBoard.png"))
	{
		cout << "Score Board Loaded Successfully" << endl;
		bulletTxt.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}

	if (coinTexture.loadFromFile("images/coins.png"))
	{
		cout << "Coins Loaded Successfully" << endl;
		coinTexture.setSmooth(true);
	}
	else {
		cout << "Error loading Coiin";
	}
	/////OBSTACLES
	if (obs1Txt.loadFromFile("images/barrel.png"))
	{
		cout << "Barrel Loaded Successfully" << endl;
		coinTexture.setSmooth(true);
	}
	else {
		cout << "Error loading Barrel";
	}
	if (obs2Txt.loadFromFile("images/block.png"))
	{
		cout << "Block Loaded Successfully" << endl;
		coinTexture.setSmooth(true);
	}
	else {
		cout << "Error loading Block";
	}
	if (powerUP.loadFromFile("images/HP_Bonus.png"))
	{
		cout << "Bonus Loaded Successfully" << endl;
		coinTexture.setSmooth(true);
	}
	else {
		cout << "Error loading Bonus";
	}
	

	//Setting up a sprite
	Sprite mainBG, mainBG2, mainBG3, mainBG4, mainBG5, mainCover, scoreBoard;
	mainBG.setTexture(bg1);
	mainBG2.setTexture(bg2);
	mainBG3.setTexture(bg3);
	mainBG4.setTexture(bg4);
	mainBG5.setTexture(bg5);
	mainCover.setTexture(bgCover);
	scoreBoard.setTexture(scoreBoardTxt);

	//bombSpr.setTexture(bombTxt);

	///////////////////////////////////
	//Player Object
	Player racer("images/audi.png", 925.0f, 900.0f);

	///////////////////////////////////
	//Coin Objects
	coinVect.push_back(Coin(coinTexture, getRandomNumber(705, 805, 'c'), getRandomNumber(-1000, -1500, 'c'), 60, 60, 10, 0.1));
	coinVect.push_back(Coin(coinTexture, getRandomNumber(855, 955, 'c'), getRandomNumber(-2000, -2500, 'c'), 60, 60, 10, 0.1));
	coinVect.push_back(Coin(coinTexture, getRandomNumber(1005, 1055, 'c'), getRandomNumber(-3000, -3500, 'c'), 60, 60, 10, 0.1));
	coinVect.push_back(Coin(coinTexture, getRandomNumber(1105, 1155, 'c'), getRandomNumber(-4000, -4500, 'c'), 60, 60, 10, 0.1));
	coinVect.push_back(Coin(coinTexture, getRandomNumber(1205, 1255, 'c'), getRandomNumber(-5000, -5500, 'c'), 60, 60, 10, 0.1));
	
	//ScoreBoard
	scoreBoard.setPosition(Vector2f(501.0f,0));

	///////////////////////////////////
	//Enemies Objects
	Enemy en1(getRandomImage(), getRandomNumber(705, 805, 'e'), getRandomNumber(-1000, -1500, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en2(getRandomImage(), getRandomNumber(855, 955, 'e'), getRandomNumber(-2000, -2500, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en3(getRandomImage(), getRandomNumber(1005, 1105, 'e'), getRandomNumber(-2200, -2400, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en4(getRandomImage(), getRandomNumber(1155, 1200, 'e'), getRandomNumber(-2500, -2700, 'e'), getRandomNumber(3, 8, 's'));

	///////////////////////////////////
	//Obstacles

	obsVect.push_back(Obstacle(obs1Txt, getRandomNumber(650, 750, 'e'), getRandomNumber(-1000, -2000, 'e')));
	obsVect.push_back(Obstacle(obs2Txt, getRandomNumber(950, 1050, 'e'), getRandomNumber(-2500, -3500, 'e')));
	obsVect.push_back(Obstacle(obs1Txt, getRandomNumber(850, 950, 'e'), getRandomNumber(-4000, -5000, 'e')));
	obsVect.push_back(Obstacle(obs2Txt, getRandomNumber(1100, 1150, 'e'), getRandomNumber(-5500, -6500, 'e')));
	
	//Powerup
	//Obstacle obs4(obs2Txt, getRandomNumber(1205, 1255, 'e'), getRandomNumber(-8000, -9000, 'e'), 0.5);
	PowerUP power(powerUP, getRandomNumber(600, 1150, 'e'), getRandomNumber(-10000, -20000, 'e'));
	power.setScale();

	RenderWindow window(VideoMode(1920, 1080), "Drift Race", sf::Style::Close | sf::Style::Titlebar);
	//window.setFramerateLimit(90);

	//Loading Window  main Game LOOP
	while (window.isOpen()) {
		Event evnt;

		//Delay Game Sound
		float currentTime = clock.getElapsedTime().asSeconds();
		if (currentTime - beginTime >= 3)
		{
				carSound.setVolume(20);
		}

		while (window.pollEvent(evnt)) {

			switch (evnt.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (evnt.key.code == Keyboard::Space) 
				{
					//cout << "Fired";
					if (bulletCount > 0) {
						fire = true;
						bullet.push_back(Bullet(bulletTxt, (int)racer.getPosX(), (int)racer.getPosY(), 32, 64, 16, 0.25));
						fireSound.play();
						bulletCount--;
					}
					else {

					}
				}
				break;
			}

			
		}
		//Showing High Score from file
		while (file >> lineFile) {
			highScoreText.setString(lineFile);

			//Store score from file
			currentHighScore = lineFile;
			//cout << lineFile << endl;
		}
//		file.close();
		//Showing life
		scoreText.setString(to_string((int)score));
		lifeText.setString(to_string(racer.getLife()));
		bulletText.setString(to_string(bulletCount));

		if (!collided) {
			//player movement
			/*
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				racer.movePlayer('u');
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				racer.movePlayer('d');
			}
			*/
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				racer.movePlayer('r');
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				racer.movePlayer('l');
			}
		}

		//Create scrolling background
		mainBG.setPosition(Vector2f(0, BackgroundY1));
		mainBG2.setPosition(Vector2f(0, BackgroundY2));
		mainBG3.setPosition(Vector2f(0, BackgroundY3));
		mainBG4.setPosition(Vector2f(0, BackgroundY4));
		mainBG5.setPosition(Vector2f(0, BackgroundY5));
		//Cover up
		mainCover.setPosition(Vector2f(0, 0));

		if (mainBG.getPosition().y >= 1080)
		{
			BackgroundY1 = -4315.0f;
		}
		if (mainBG2.getPosition().y >= 1080) {
			BackgroundY2 = -4315.0f;
		}
		if (mainBG3.getPosition().y >= 1080) {
			BackgroundY3 = -4315.0f;
		}
		if (mainBG4.getPosition().y >= 1080) {
			BackgroundY4 = -4315.0f;
		}
		if (mainBG5.getPosition().y >= 1080) {
			BackgroundY5 = -4315.0f;
		}
		/////////////////////////////////////////////////
		///////////////// PLAYER COLLISION /////////////
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
			BackgroundY4 += speed;
			BackgroundY5 += speed;
		}
		/////////////////////////////////////////////////
		///////////////// PLAYER COLLISION /////////////
		/// Player Collided
		if (collided) {
			// Slow start simulation
			if (maxSpeed <= 5) {
				if (speed > 0) {
					speed -= 0.05f;
				}
			}
			else if (maxSpeed > 5 && maxSpeed <= 7) {
				if (speed > 0) {
					speed -= 0.05f;
				}
			}
			else if (maxSpeed > 7 && maxSpeed <= 9) {
				if (speed > 0) {
					speed -= 0.07f;
				}
			}
			else if (maxSpeed > 9 && maxSpeed <= 11) {
				if (speed > 0) {
					speed -= 0.09f;
				}
			}
			else if (maxSpeed > 11 && maxSpeed <= 15) {
				if (speed > 0) {
					speed -= 0.1f;
				}
			}

			BackgroundY1 += speed;
			BackgroundY2 += speed;
			BackgroundY3 += speed;
			BackgroundY4 += speed;
			BackgroundY5 += speed;
		}

		////////////////////////////////////
		// Regeneration of Enemy
		//cout << en1.getPosY() << endl;

		if (en1.getPosY() > 1200) {
			setEnemNewPosition(en1, 1, oppMaxSpeed);
//			score++;
		}
		if (en2.getPosY() > 1200) {
			setEnemNewPosition(en2, 2, oppMaxSpeed);
//			score++;
		}
		if (en3.getPosY() > 1200) {
			setEnemNewPosition(en3, 3, oppMaxSpeed);
//			score++;
		}
		if (en4.getPosY() > 1200) {
			setEnemNewPosition(en4, 4, oppMaxSpeed);
//			score++;
		}


		/////////////////////////////
		// Game Level
		if (score > 25 && score < 75) { maxSpeed = 7; oppMaxSpeed = 7; };
		if (score > 75 && score < 150) { maxSpeed = 9; oppMaxSpeed = 9; };
		if (score > 150 && score < 200) { maxSpeed = 11; oppMaxSpeed = 11; };
		if (score > 200 && score < 250) { maxSpeed = 15; oppMaxSpeed = 15; };


		//////////////////////////////
		//Check collission of player and enemy
		if (!collided) {
			if (getDistance(racer.getPosX(), racer.getPosY(), en1.getPosX(), en1.getPosY()) < 50 ||
				getDistance(racer.getPosX(), racer.getPosY(), en2.getPosX(), en2.getPosY()) < 50 ||
				getDistance(racer.getPosX(), racer.getPosY(), en3.getPosX(), en3.getPosY()) < 50 ||
				getDistance(racer.getPosX(), racer.getPosY(), en4.getPosX(), en4.getPosY()) < 50)
			//	getDistance(racer.getPosX(), racer.getPosY(), en5.getPosX(), en5.getPosY()) < 60)
			{
				collided = true;
				//cout << "Collided";
				explode.push_back(Explosion(bombTxt, (int)racer.getPosX() - 170, (int)racer.getPosY() - 150, 256, 256, 48, 0.25));
				racer.setLife(racer.getLife() - 1);
				if (bulletCount > 0) {
					bulletCount--;
				}
				//carCrash.play();
				powerDownSound.play();
			}
		}

		/////////////////////////////////////////////////
		///////////////// BULLET COLLISION /////////////
		// Check collission of bullet and enemy
		if (fire) {
			for (int i = 0; i < bullet.size(); i++) {
				if (getDistance((float)bullet[i].getPosX(), (float)bullet[i].getPosY(), en1.getPosX(), en1.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en1.getPosX() - 170, (int)en1.getPosY() - 150, 256, 256, 48, 0.25));
//					bullet.erase(find(bullet.begin(), bullet.end(), bullet[i]));

					/// Checking bullet collision an popping it out
					//bullet.erase(remove(bullet.begin(), bullet.end(), bullet[i]), bullet.end());

					setEnemNewPosition(en1, 1, oppMaxSpeed);
					score += 1;

					carCrash.play();
				}
				if (getDistance((float)bullet[i].getPosX(), (float)bullet[i].getPosY(), en2.getPosX(), en2.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en2.getPosX() - 170, (int)en2.getPosY() - 150, 256, 256, 48, 0.25));
					
					setEnemNewPosition(en2, 2, oppMaxSpeed);
					score += 1;

					carCrash.play();
				}
				if (getDistance((float)bullet[i].getPosX(), (float)bullet[i].getPosY(), en3.getPosX(), en3.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en3.getPosX() - 170, (int)en3.getPosY() - 150, 256, 256, 48, 0.25));
					
					setEnemNewPosition(en3, 3, oppMaxSpeed);
					score += 1;

					carCrash.play();
				}
				if(getDistance((float)bullet[i].getPosX(), (float)bullet[i].getPosY(), en4.getPosX(), en4.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en4.getPosX() - 170, (int)en4.getPosY() - 150, 256, 256, 48, 0.25));
					
					setEnemNewPosition(en4, 4, oppMaxSpeed);
					score += 1;

					carCrash.play();
				}/*
				if (getDistance((float)bullet[i].getPosX(), (float)bullet[i].getPosY(), en5.getPosX(), en5.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en5.getPosX() - 170, (int)en5.getPosY() - 150, 256, 256, 48, 0.25));
					
					setEnemNewPosition(en5, 5, oppMaxSpeed);
					score += 1;
				}*/
			}
		}

		
		///////////////////////////////////////////////
		///////////////////////////////////////////////
		/////////////// COIN COLLISION ///////////////
		///////////////////////////////////////////////
		///////////////////////////////////////////////
		for (int i = 0; i < coinVect.size(); i++)
		{
			if (getCPdistance(coinVect[i], racer) < 60) {
				coinSound.play();
				setCoinNewPosition(coinVect[i], i);
				score += 2;
			}
		}


		///////////////////////////////////////////////
		///////////////////////////////////////////////
		/////////////// Obstacle COLLISION ///////////////
		///////////////////////////////////////////////
		///////////////////////////////////////////////
		for (int i = 0; i < obsVect.size(); i++) {
			if (getOPDistance(obsVect[i], racer) < 80) {
				//cout << "Collided";
				//
				collided = true;
				explode.push_back(Explosion(bombTxt, (int)racer.getPosX() - 170, (int)racer.getPosY() - 150, 256, 256, 48, 0.25));
				//
				obsVect[i].setPosY(getRandomNumber(-1000, -5500, 'e'));
				racer.setLife(racer.getLife() - 1);
				if (bulletCount > 0) {
					bulletCount--;
				}
				//carCrash.play();
				powerDownSound.play();
			}
		}


		//////////////////////////////////////////////
		///////////// POWER UPS /////////////
		/////////////////////////////////////////////

		if (getPPdistance(power, racer) <= 60) {
			power.setPosY(getRandomNumber(-10000, -20000, 'e'));
			power.setPosX(getRandomNumber(600, 1150, 'e'));

			if (racer.getLife() < 3) {
				racer.setLife(racer.getLife() + 1);
			}
			if (bulletCount < 10) {
				bulletCount += 5;
			}

			powerUPSound.play();
		}
		if (power.getPosY() > 1080) {
			power.setPosY(getRandomNumber(-5000, -8000, 'e'));
			power.setPosX(getRandomNumber(600, 1150, 'e'));
		}


		//////////////////////////////////////////////
		///////////// RESPAWN OBSTACLES /////////////
		/////////////////////////////////////////////
		//cout << obsVect[0].getPosY() << endl;
		for (int i = 0; i < obsVect.size(); i++) {

			if (obsVect[i].getPosY() > 1200) {
				if (i == 0) {
					obsVect[i].setPosY((float)getRandomNumber(-1500, -2000, 'e'));
				}
				else if (i == 1) {
					obsVect[i].setPosY((float)getRandomNumber(-2500, -3500, 'e'));
				}
				else if (i == 2) {
					obsVect[i].setPosY((float)getRandomNumber(-4000, -5000, 'e'));
				}
				else if (i == 3) {
					obsVect[i].setPosY((float)getRandomNumber(-5500, -6500, 'e'));
				}
				else if (i == 4) {
					obsVect[i].setPosY((float)getRandomNumber(-7000, -8000, 'e'));
				}
				else if (i == 5) {
					obsVect[i].setPosY((float)getRandomNumber(-8500, -9500, 'e'));
				}

			}
		}




		
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		//////////////////////////// Drawing Session ////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		
		//Clearing and creating windows
		window.clear();

		window.draw(mainCover);
		window.draw(mainBG);
		window.draw(mainBG2);
		window.draw(mainBG3);
		window.draw(mainBG4);
		window.draw(mainBG5);

		//Render Player Object
		racer.drawPlayer(window);

		//Render Enemies
		en1.drawEnemy(window);
		en2.drawEnemy(window);
		en3.drawEnemy(window);
		en4.drawEnemy(window);
		//en5.drawEnemy(window);
		//en6.drawEnemy(window);

		//////////////////////////
		//////////////////////////
		///Render Obstacles
		//////////////////////////
		//////////////////////////

		for (int i = 0; i < obsVect.size(); i++) {
			obsVect[i].drawObs(window);
		}


		////////////////////
		/// Render PowerUP //
		/////////////////////
		power.drawObs(window);


		//Render Coin
		for (int i = 0; i < coinVect.size(); i++) {
			coinVect[i].update();
			window.draw(coinVect[i].sprite);
			coinVect[i].updateCoin();
		}


		//////////////////////////
		//////////////////////////
		//Explosion
		//////////////////////////
		//////////////////////////
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

			if (explode.empty()) {
				fire = false;
			}
		}

		if (fire) {
			for (int i = 0; i < bullet.size(); i++) {
				bullet[i].update();
				window.draw(bullet[i].sprite);
				bullet[i].updateBullet();

				if (bullet[i].getPosY() < 300) {
					bullet.erase(bullet.begin());
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


		///////////////////////////
		//Render ScoreBoard
		window.draw(scoreBoard);

		//Render Score
		window.draw(highScoreText);
		window.draw(scoreText);
		window.draw(lifeText);
		window.draw(bulletText);

		//////////////////////////

		// Checking Player LifeSpan 
		if (racer.getLife() <= 0) {

			cout << "---------------------------------------------------------------------------" << endl;
			cout << "---------------------------------------------------------------------------" << endl;
			cout << "----------------------------- You Died ! ----------------------------------" << endl;
			cout << "----------------------- Better Luck Next Time ! ---------------------------" << endl;
			cout << "---------------------------------------------------------------------------" << endl;
			cout << "---------------------------------------------------------------------------" << endl;

			if (score > stoi(currentHighScore)) {
				//Storing HIGH SCORE
				ofstream storeFile;
				storeFile.open("highScore.txt");

				storeFile << score;
				storeFile.close();

				cout << " Congratulation You created a new HighScored with : " << score << "Points" << endl;
			}

				cout << " You Scored : " << score << " Points" << endl;
				cout << " Current High Score : " << currentHighScore << " Points" << endl;

			window.close();
		}


		window.display();
	}
}

//// e = enemy
//// i = image
//// s = speed
//// c = coin
int getRandomNumber(int a, int b, char ch)
{
	static bool first = true; if (first) { srand(time(NULL)); first = false; }
	int result = a + rand() % ((b + 1) - a);
	if (ch == 'e') {
		result = (result / 10) * 10;
		return result;
	}
	else if (ch == 'i' || ch == 's' || ch == 'c') {
		return result;
	}
	return result;
}

string getRandomImage() {
	stringstream ss;
	ss << getRandomNumber(1, 7, 'i');
	string imgTag = ss.str();

	string imgDir = "images/obs" + imgTag + ".png";
	//cout << imgDir;

	return imgDir;
}

float getDistance(float x1, float y1, int x2, int y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void setEnemNewPosition(Enemy &enem, int num, int speed) {
	if (num == 1) {
		enem.setPosY(getRandomNumber(-1000, -2000, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 2) {
		enem.setPosY(getRandomNumber(-1500, -2500, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 3) {
		enem.setPosY(getRandomNumber(-2000, -3000, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 4) {
		enem.setPosY(getRandomNumber(-2500, -3500, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 5) {
		enem.setPosY(getRandomNumber(-3000, -4000, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}

}

float getCPdistance(Coin& c, Player& p) {
	return sqrt(pow((p.getPosX() - c.getPosX()),2) + pow((p.getPosY() - c.getPosY()),2));
}

float getPPdistance(PowerUP& pp, Player& p) {
	return sqrt(pow((p.getPosX() - pp.getPosX()), 2) + pow((p.getPosY() - pp.getPosY()), 2));
}

void setCoinNewPosition(Coin& coin, int num) {
	if (num == 0) {
		coin.setNewPos(getRandomNumber(705, 805, 'c'), getRandomNumber(-1500, -1700, 'c'));
	}
	else if (num == 1) {
		coin.setNewPos(getRandomNumber(855, 955, 'c'), getRandomNumber(-2700, -2900, 'c'));
	}
	else if (num == 2) {
		coin.setNewPos(getRandomNumber(1005, 1055, 'c'), getRandomNumber(-3900, -4100, 'c'));
	}
	else if (num == 3) {
		coin.setNewPos(getRandomNumber(1105, 1155, 'c'), getRandomNumber(-5100, -5300, 'c'));
	}
	else if (num == 4) {
		coin.setNewPos(getRandomNumber(1205, 1255, 'c'), getRandomNumber(-6300, -6500, 'c'));
	}
}

int getOPDistance(Obstacle& obj1, Player& obj2)
{
	return sqrt(pow((obj2.getPosX() - obj1.getPosX()), 2) + pow((obj2.getPosY() - obj1.getPosY()), 2));;
}

