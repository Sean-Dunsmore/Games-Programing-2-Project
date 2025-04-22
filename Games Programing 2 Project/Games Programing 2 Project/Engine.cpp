#include "Engine.h"

//Constructor
Engine::Engine()
{
	//Initilise engine
	init();
}

//Deconstructor
Engine::~Engine()
{
	//Cleanup all pointers
	cleanup();
}

//Initilise the engine and start the main loop
void Engine::init()
{
	//Init display
	gameDisplay.initDisplay();

	//Seed random function //NOTE: Might not need this?
	std::srand((int)std::time(NULL));

	//Engine is running
	isRunning = true;


	//TODO: Rework all this file loading init stuff
	//TODO: probably put this in the specific scenes
	//mesh1.loadModel("..\\res\\monkey3.obj");
	//mesh2.loadModel("..\\res\\Ball.obj");
	//fogShader.init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag"); //new shader
	//toonShader.init("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag"); //new shader
	//rimShader.init("..\\res\\Rim.vert", "..\\res\\Rim.frag");
	//what.init("..\\res\\what.vert", "..\\res\\what.frag");
	//noBump.init("..\\res\\noBump.vert", "..\\res\\noBump.frag");
	//texture1.load("..\\res\\bricks.jpg"); //load texture

	//Init Camera
	myCamera.initCamera(glm::vec3(2, 0, -4), 70.0f, (float)gameDisplay.getWidth() / gameDisplay.getHeight(), 0.01f, 1000.0f);

	//Set starting scene
	scenePointer = new BumpScene;
	scenePointer->initaliseScene();

	//Start main loop
	mainLoop();

}

//Calculate Deltatime
void Engine::calculateDeltatime()
{

	//Deltatime = milliseconds passed since last frame //TODO
	deltatime = (clock() - oldTime);
	oldTime = clock();
}

//Process input
void Engine::processInput()
{

	//Process scene inputs
	scenePointer->processInput(deltatime);

	//TODO: INPUTS TO CHANGE SCENE
	//Delete scene
	//Init new scene

	//Check for exit game
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

}

//Update game objects
void Engine::update()
{

	//Update the game
	scenePointer->updateScene(deltatime);

}

//Draw to screen
void Engine::draw()
{

	gameDisplay.clearDisplay(0.8f, 0.8f, 0.8f, 1.0f); //sets our background colour
	
	//Pass in display and camera position
	scenePointer->draw(deltatime,myCamera);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameDisplay.swapBuffer();
}

//Main loop
void Engine::mainLoop()
{

	//Until asked to exit
	while (isRunning)
	{
		calculateDeltatime(); //Calculate deltatime

		processInput(); //Process input

		update(); //Update

		draw(); //Draw to screen
	}

	//The engine has been closed
	//Run cleanup
	cleanup();

}

//Cleanup pointers
void Engine::cleanup()
{

	//Cleanup pointers
	//Game pointer
	if (scenePointer != nullptr)
	{
		delete scenePointer;
		scenePointer = nullptr;
	}

}