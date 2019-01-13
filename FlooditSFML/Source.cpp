#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Audio.hpp>
#include "menu.h"
#include "game.h"

using namespace std;


int main() {
	Music music;
	if (!music.openFromFile("Resources/bg_m.ogg"))
		return -1;
	music.play();
	menu mainmenu;
	mainmenu.intilize_main_menu();
	return 0;
}