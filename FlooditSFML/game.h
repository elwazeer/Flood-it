#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#define Max_Size 12
using namespace std;
using namespace sf;
#define game_H
#pragma once

class game
{
public:
	game();
	//string score();
	void show_end_msg(String msg);
	void is_loser(RenderWindow& w, int current);
	void intlize_new();
	void recurse(int i, int j, Color co);
	void clean_and_fill(Color col);
	void action(RenderWindow& w, int color);
	void action(RenderWindow& w, Color color);
	void intilize_game_window();
	void intial();
	Color firemouseevent(int x, int y);
	Color get_color_by_int(int num);
	Color getrandomcolor(int num);
	~game();
private:
	RectangleShape shapes[12][12];
	Font globl_font;
	int gamesize = 12;
	int gamecolors = 8;
	int max_steps = 50;
	int current_step = 0;
	int cellsize = 40; //default Game option is 12 * 12 and the dispaly box is Fixed for all sizes = 480px so in default case cellsize is 480 / 12 = 40
	int flooded[Max_Size][Max_Size] = { 0 };
	int recursed[Max_Size][Max_Size] = { 0 };
};