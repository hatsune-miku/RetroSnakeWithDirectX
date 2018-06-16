#include <iostream>
#include "coregame.hpp"
using namespace std;
int main() {

	cout << "Retro Snaker by EGGTART\n";
	cout << "Initializing...";

	coregame game;
	game.game_start();
	return 0;
}
