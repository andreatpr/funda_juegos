#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include "Sprite.h" 
#include <iostream>
#include <vector>
#include "Window.h"
#include "GLS_Program.h"
using namespace std;

enum class GameState {
	PLAY, EXIT
};

class MainGame
{
private:
	int width;
	int height;
	Window* window;
	Sprite sprite;
	void init();
	void processInput();
	GLS_Program program;
	void initShaders();
	float time = 0;
	float lspawnt;
	float interval;
	std::vector<Sprite> sprites;

public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void draw();
	void update();
	void newSprites();
};

