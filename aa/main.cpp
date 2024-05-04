#include <SDL/SDL.h>
#include "MainGame.h"
int main(int argc, char** argv) {
	MainGame mainGame;
	cout << "sprites creandose...\n"<<"cantidad de sprites creados:\n\n";
	mainGame.run();
	system("pause");
	return 0;
}