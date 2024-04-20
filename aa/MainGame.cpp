#include "MainGame.h"
#include <ctime>

MainGame::MainGame()
{
	window = nullptr;
	width = 800;
	height = 600;
	lspawnt = 0.0f;
	interval = 1.0f; // intervalo para crear cada 1 seg un nuevo sprite
	gameState = GameState::PLAY;
}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("AA al inicio demora un poco, espere", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//validar si hubieron errores
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//validar estado de glew
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	initShaders();
}
void MainGame::newSprites()
{
	float timeac = SDL_GetTicks() / 1000.0f; 
	if (timeac - lspawnt >= interval) {
		//creo mis sprites x y de 0 a -1
		float x = -1.0f + static_cast<float>(rand()) / (RAND_MAX / 1.0f);
		float y = -1.0f + static_cast<float>(rand()) / (RAND_MAX / 1.0f);
		sprite.init(x, y, 1, 1);
		sprites.push_back(sprite); //los guardo en un vector definido en MainGame.h
		std::cout << sprites.size() <<" ";
		// actualizo el tiempo que me sirve para crear nuevos sprites
		lspawnt = timeac;
	}
}
void MainGame::draw() 
{
	glClearDepth(1.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); , si lo borro solo aparece UN sprite sin sobreponerse
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.0002;
	for (auto& s : sprites) {
		s.draw();
	}
	program.unuse();
	SDL_GL_SwapWindow(window);
}

void MainGame::run()
{
	init();
	update();
}
void MainGame::update()
{
	newSprites();
	while (gameState != GameState::EXIT) {
		processInput(); 
		draw();
		newSprites(); //mando a crear sprites
	}
}
MainGame::~MainGame()
{
}
void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		/*case SDL_MOUSEMOTION:
			cout << "Posicion en X"<<event.motion.x<<"Posicion Y"<<event.motion.y<<endl;
			break;*/
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.linkShader();
}
