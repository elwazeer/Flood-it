#include "game.h"
#include "menu.h"

menu::menu()
{
}

void menu::intilize_main_menu() {
	Texture t_bg, b1, b2, b3;
	t_bg.loadFromFile("Resources/bg.jpg");
	b1.loadFromFile("Resources/btn1.png");
	b2.loadFromFile("Resources/btn4.png");
	b3.loadFromFile("Resources/btn3.png");

	Sprite bg, _b1, _b2, _b3;
	bg.setTexture(t_bg);
	bg.setPosition(0, 0);
	_b1.setTexture(b1);
	_b1.setPosition(150, 100);
	_b2.setTexture(b2);
	_b2.setPosition(150, 400);
	_b3.setTexture(b3);
	_b3.setPosition(150, 250);
	
	RenderWindow window1(VideoMode(800, 600), "Flood it! - Main Menu", Style::Titlebar);
	while (window1.isOpen())
	{
		Event event;
		while (window1.pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window1.close();
			if (event.type == Event::Closed) window1.close();
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left) {
					int x = event.mouseButton.x;
					int y = event.mouseButton.y;
					if (x > 150 && x < 650 && y > 100 && y < 180) {
						window1.clear();
						window1.close();
						game newgame;
						newgame.intilize_game_window();
					}
					else if (x > 150 && x < 650 && y > 250 && y < 380) {
						window1.clear();
						//	newgame.score();//High Score
					}
					else if (x > 150 && x < 650 && y > 400 && y < 480) {
						exit(1);
					}
				}
			}
		}
		window1.clear();
		window1.draw(bg);
		window1.draw(_b1);
		window1.draw(_b2);
		window1.draw(_b3);
		window1.display();
	}
}

menu::~menu()
{
}
