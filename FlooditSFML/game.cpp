#include "game.h"
#include "menu.h"


game::game()
{

}
void game::intial() {
	flooded[0][0] = 1;
	globl_font.loadFromFile("Resources/BAUHS93.TTF");
	srand(time(NULL));
}
void game::intlize_new() {
	for (int i = 0; i < gamesize; i++) {
		for (int j = 0; j < gamesize; j++) {
			shapes[i][j].setSize(Vector2f(cellsize, cellsize));
			shapes[i][j].setFillColor(getrandomcolor(gamecolors));
			shapes[i][j].setPosition(i * cellsize + 52, j * cellsize + 52); //50 Is the margin
		}
	}
}
void game::intilize_game_window() {
	intial();
	intlize_new();
	RenderWindow window2(VideoMode(800, 600), "Flood it! - New Game", Style::Titlebar);
	
	RectangleShape border;
	border.setFillColor(Color::Transparent);
	border.setOutlineThickness(2.0);
	border.setOutlineColor(Color::Yellow);
	border.setSize(Vector2f(484, 484));
	border.setPosition(50, 50);

	Texture t_bg;
	t_bg.loadFromFile("Resources/bg.jpg");
	Sprite bg;
	bg.setTexture(t_bg);
	bg.setPosition(0, 0);

	Text score;
	score.setFont(globl_font);
	score.setPosition(Vector2f(620, 30));
	score.setCharacterSize(24);

	Text bk, sv_ex;
	bk.setFont(globl_font);
	sv_ex.setFont(globl_font);
	bk.setString("Back To Main Menu");
	sv_ex.setString(" Press Here to Exit");
	bk.setCharacterSize(24);
	sv_ex.setCharacterSize(24);
	bk.setPosition(550, 250);
	sv_ex.setPosition(550, 300);

	while (window2.isOpen())
	{
		Event event;
		while (window2.pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window2.close();
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::W) action(window2, 0);
				if (event.key.code == Keyboard::B) action(window2, 1);
				if (event.key.code == Keyboard::L) action(window2, 2);
				if (event.key.code == Keyboard::C) action(window2, 3);
				if (event.key.code == Keyboard::G) action(window2, 4);
				if (event.key.code == Keyboard::M) action(window2, 5);
				if (event.key.code == Keyboard::R) action(window2, 6);
				if (event.key.code == Keyboard::Y) action(window2, 7);
			}
			if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left) {
					int x = event.mouseButton.x;
					int y = event.mouseButton.y;
					if (x > 550 && x < 800 && y > 240 && y < 280) {
						window2.clear();
						window2.close();
						menu newmenu;
						newmenu.intilize_main_menu();
					}
					else if (x > 550 && x < 800 && y > 300 && y < 340) {
						exit(1);
					}
					else if (x > 52 && x < 532 && y > 52 && y < 532) {
						action(window2, firemouseevent(x, y));
					}

				}
			}
		}
		window2.clear();
		window2.draw(bg);
		score.setString(to_string(current_step) + " / " + to_string(max_steps));
		window2.draw(score);
		window2.draw(border);
		window2.draw(bk);
		window2.draw(sv_ex);

		for (int i = 0; i < gamesize; i++) {
			for (int j = 0; j < gamesize; j++) {
				window2.draw(shapes[i][j]);
			}
		}
		window2.display();
	}
}


void game::recurse(int i, int j, Color co) {
	if (i == gamesize || j == gamesize || i < 0 || j < 0) return;
	if (recursed[i][j] == 1) return;
	else recursed[i][j] = 1;

	if (flooded[i][j] == 1) {
		recurse(i, j - 1, co);
		recurse(i, j + 1, co);
		recurse(i + 1, j, co);
		recurse(i - 1, j, co);
	}
	else if (shapes[i][j].getFillColor() == co) {
		flooded[i][j] = 1;
		recurse(i, j - 1, co);
		recurse(i, j + 1, co);
		recurse(i + 1, j, co);
		recurse(i - 1, j, co);
	}
	else return;
}
void game::clean_and_fill(Color col) {
	for (int i = 0; i < gamesize; i++) {
		for (int j = 0; j < gamesize; j++) {
			recursed[i][j] = 0;
			if (flooded[i][j] == 1) {
				shapes[i][j].setFillColor(col);
			}
		}
	}
}
void game::action(RenderWindow& w, int color) { //Function to make the action through KeyBoard
	if (shapes[0][0].getFillColor() == get_color_by_int(color)) return;
	recurse(0, 0, get_color_by_int(color));
	is_loser(w, ++current_step);
	clean_and_fill(get_color_by_int(color));
}
void game::action(RenderWindow& w, Color color) { //Overloaded Function to make the action through mouse Click
	if (shapes[0][0].getFillColor() == color) return;
	recurse(0, 0, color);
	is_loser(w, ++current_step);
	clean_and_fill(color);
}

Color game::getrandomcolor(int num) {
	int product = rand() % num;
	return get_color_by_int(product);
}
Color game::get_color_by_int(int num) {
	switch (num) {
	case 0: return Color::White; break;
	case 1: return Color::Black; break;
	case 2: return Color::Blue; break;
	case 3: return Color::Cyan; break;
	case 4: return Color::Green; break;
	case 5: return Color::Magenta; break;
	case 6: return Color::Red; break;
	case 7: return Color::Yellow; break;
	}
}
Color game::firemouseevent(int x, int y) {
	int i = floor(double(x - 52) / double(cellsize));
	int j = floor(double(y - 52) / double(cellsize));
	return shapes[i][j].getFillColor();
}


void game::show_end_msg(String msg)
{
	RenderWindow window(VideoMode(800, 600), "Game Ended!", Style::Titlebar);
	Texture bg;
	Sprite _bg;
	Text loseing;
	loseing.setFont(globl_font);
	loseing.setString(msg);
	loseing.setPosition(Vector2f(215, 120));
	loseing.setCharacterSize(50);
	bg.loadFromFile("Resources/bg.jpg");
	_bg.setTexture(bg);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
			if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left) {
					int x = event.mouseButton.x;
					int y = event.mouseButton.y;
					if (x > 315 && x < 485 && y > 400 && y < 480) {
						window.clear();
						window.close();
						game newgame;
						newgame.intilize_game_window();
					}
				}
				}
		}
		window.clear();
		window.draw(_bg);
		window.draw(loseing);
		window.display();
	}
}
void game::is_loser(RenderWindow& w, int current) {
	for (int i = 0; i < gamesize; i++) {
		for (int j = 0; j < gamesize; j++) {
			if (flooded[i][j] == 0)
				if (current >= max_steps) {
					show_end_msg("\t You Lost! \n You passed 50 attempts \n\n\n       Replay");
					w.close();
					return;
				}
				else return;
		}
	}
	show_end_msg("\t  You Won! \n You Score is " + to_string(current) + "\n\n\n       Replay");
}
//string game:: score()
//{
//	ofstream OutputFile("Resources/scores.txt");
//	string msg; 
//	OutputFile << current_step;
//	OutputFile.close();
//
//	ifstream InputFile("Resources/scores.txt");
//	if (InputFile.is_open())
//	{
//		int highscore;
//		InputFile >> highscore;
//		if (highscore > current_step)
//		{
//			msg= ( "You did not break your previous highscore of " + highscore) ;
//		}
//		if (highscore < current_step)
//		{
//			msg =  ("You broke your previous highscore of " + highscore ) ;
//		}
//		return (msg); 
//		InputFile.close();
//	}
//}

game::~game()
{
}
