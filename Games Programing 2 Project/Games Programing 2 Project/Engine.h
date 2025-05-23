#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Camera.h"
#include "DefaultScene.h"
#include "BumpScene.h"
#include "RimScene.h"
#include "AmbientLightScene.h"
#include "FadeScene.h"
#include "NormalTextureScene.h"
#include "PointLightScene.h"
#include "SpotLightScene.h"
#include "ToonScene.h"
#include "WaterScene.h"
#include <windows.h>

//Enum containing possible scenes
enum CurrentScene
{
	Default,
	Bump,
	Fog,
	Ambient,
	Fade,
	NormalTex,
	PointLight,
	SpotLight,
	Toon,
	Water
};

//The Engine class contains functionality that will be shared between both games
//It contains both the main menu to select a game and the main loop
//It also contains the screenbuffers and draw calls
class Engine
{
public:

	Engine(); //Constructor
	~Engine(); //Deconstructor

private:

	void init(); //Initilise the engine and start the main loop

	void calculateDeltatime(); //Calculate Deltatime

	void processInput(); //Process input

	void update(); //Update game objects

	void draw(); //Draw to screen

	void mainLoop(); //Main loop

	void nextScene(); //Next Scene

	void lastScene(); //last Scene

	void changeScene(); //change Scene

	void cleanup(); //Cleanup all Memory

	//Engine is running
	bool isRunning;

	//Pointer to current Scene
	Scene* scenePointer;
	CurrentScene scene;

	//Deltatime
	time_t deltatime;
	time_t oldTime;

	//Graphics stuff
	//Game display
	Display gameDisplay;

	//Camera
	Camera myCamera;

	//Quick fix to prevent multiple inputs in a frame
	float inputTimer = 0;

};

