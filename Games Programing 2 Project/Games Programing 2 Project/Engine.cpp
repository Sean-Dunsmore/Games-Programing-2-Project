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

	//TODO: probably put this in the specific scenes
	//toonShader.init("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag"); //new shader
	//what.init("..\\res\\what.vert", "..\\res\\what.frag");

	//Init Camera
	myCamera.initCamera(glm::vec3(2, 0, -4), 70.0f, (float)gameDisplay.getWidth() / gameDisplay.getHeight(), 0.01f, 1000.0f);

	//Set starting scene
	scene = Default;
	changeScene();

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

	//Camera movement
	if (GetKeyState('W') & 0x8000)
	{
		myCamera.MoveForward(0.001 * deltatime);
	}
	if (GetKeyState('S') & 0x8000)
	{
		myCamera.MoveForward(-0.001 * deltatime);
	}
	if (GetKeyState('D') & 0x8000)
	{
		myCamera.MoveRight(-0.001 * deltatime);
	}
	if (GetKeyState('A') & 0x8000)
	{
		myCamera.MoveRight(0.001 * deltatime);
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		myCamera.RotateY(0.001 * deltatime);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		myCamera.RotateY(-0.001 * deltatime);
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		myCamera.Pitch(0.001 * deltatime);
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		myCamera.Pitch(-0.001 * deltatime);
	}

	//Change Scene
	//Quick fix to prevent multiple inputs in a frame
	if (inputTimer < 0)
	{
		if (GetKeyState('J') & 0x8000)
		{
			lastScene(); //last Scene
			inputTimer = 500;
		}
		else if (GetKeyState('K') & 0x8000)
		{
			nextScene(); //Next Scene
			inputTimer = 500;
		}
	}
	else
	{
		inputTimer = inputTimer - 1 * deltatime;
	}

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

void Engine::nextScene() //Next Scene
{

	switch (scene)
	{
	case Default:
		scene = Bump;
		break;
	case Bump:
		scene = Fog;
		break;
	case Fog:
		scene = Ambient;
		break;
	case Ambient:
		scene = Fade;
		break;
	case Fade:
		scene = NormalTex;
		break;
	case NormalTex:
		scene = PointLight;
		break;
	case PointLight:
		scene = SpotLight;
		break;
	case SpotLight:
		scene = Toon;
		break;
	case Toon:
		scene = Water;
		break;
	case Water:
		scene = Default;
		break;
	}

	changeScene();
}

void Engine::lastScene() //Next Scene
{

	switch (scene)
	{
	case Default:
		scene = Water;
		break;
	case Bump:
		scene = Default;
		break;
	case Fog:
		scene = Bump;
		break;
	case Ambient:
		scene = Fog;
		break;
	case Fade:
		scene = Ambient;
		break;
	case NormalTex:
		scene = Fade;
		break;
	case PointLight:
		scene = NormalTex;
		break;
	case SpotLight:
		scene = PointLight;
		break;
	case Toon:
		scene = SpotLight;
		break;
	case Water:
		scene = Toon;
		break;
	}

	changeScene();
}

void Engine::changeScene() //Change Scene
{

	delete scenePointer;
	scenePointer = nullptr;

	switch (scene)
	{
	case Default:
			scenePointer = new DefaultScene;
			scenePointer->initaliseScene(myCamera);
		break;
	case Bump:
			scenePointer = new BumpScene;
			scenePointer->initaliseScene(myCamera);
		break;
	case Fog:
			scenePointer = new RimScene;
			scenePointer->initaliseScene(myCamera);
		break;
	case Ambient:
			scenePointer = new AmbientLightScene;
			scenePointer->initaliseScene(myCamera);
		break;
	case Fade:
			scenePointer = new FadeScene;
			scenePointer->initaliseScene(myCamera);
		break;
	case NormalTex:
			scenePointer = new NormalTextureScene;
			scenePointer->initaliseScene(myCamera);
		break;
	case PointLight:
			scenePointer = new PointLightScene;
			scenePointer->initaliseScene(myCamera);
		break;
	case SpotLight:
			scenePointer = new SpotLightScene;
			scenePointer->initaliseScene(myCamera);
		break;
	case Toon:
			scenePointer = new ToonScene;
			scenePointer->initaliseScene(myCamera);
		break;
	case Water:
			scenePointer = new WaterScene;
			scenePointer->initaliseScene(myCamera);
		break;
	}

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