#include <SFML/Graphics.hpp>

using namespace sf;

#include <iostream>

using namespace std;



void drawQuad(RenderWindow& win, Color col, int x1, int y1, int w1, int x2, int y2, int w2) {
	ConvexShape shape(4);
	shape.setFillColor(col);
	shape.setPoint(0, Vector2f(x1 - w1, y1));
	shape.setPoint(1, Vector2f(x2 - w2, y2));
	shape.setPoint(2, Vector2f(x2 + w2, y2));
	shape.setPoint(3, Vector2f(x1 + w1, y1));
	win.draw(shape);
}

int main()
{
	const int vHeight = 1080;
	const int vWidth = 1920;
	const int roadWidth = 2000;
	const int segL = 200; //segment
	const float camD = 0.84; //CameraDepth


	// Create a video mode object 
	VideoMode vm(vWidth, vHeight);

	// Create and open a window for the game 
	RenderWindow window(vm, "Drift Race !!!", Style::Titlebar | Style::Close);

	// Create a texture to hold a graphic on the GPU   
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("images/bgg.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	//spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);



	//Creating player 
	RectangleShape player(Vector2f(50.0f, 50.0f));
	player.setOrigin(-125, -125);

	while (window.isOpen()) {

		Event evnt;
		while (window.pollEvent(evnt)) {

			switch (evnt.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				std::cout << "New heigth: " << evnt.size.height << "New Width: " << evnt.size.width << std::endl;
				break;
			case Event::TextEntered:
				if (evnt.text.unicode < 130) {
					printf("%c", evnt.text.unicode);
				}
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
			player.move(0.0f, -2.5f);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {

			//Vector2i playerPos = player::getPosition();
			player.move(2.5f, 0.0f);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
			player.move(-2.5f, 0.0f);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
			player.move(0.0f, 2.5f);
		}


		//Clearing canvas
		window.clear();

		// Draw our game scene here 
		window.draw(spriteBackground);
		//Draw Quad Road
		drawQuad(window, Color::Green, 1040, 800, 400, 1040, 400, 200);

		//Draw Actor
		window.draw(player);

		// Show everything we just drew 
		window.display();

	}

	return 0;
}