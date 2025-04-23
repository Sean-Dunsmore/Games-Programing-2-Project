#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "BumpScene.h"
#include "Display.h" 
#include "Camera.h"
#include <windows.h>

enum CurrentScene
{
	Bump,
	BumpAgain
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

	//Link shaders
	//TODO: Actually these should be in the individual scenes probably
	//void linkBumpMapping();
	//void linkFogShader();
	//void linkToon();
	//void linkRimShader();
	//void linkWhat();

	//TODO: Implement this stuff i guess
	//Collision
	//bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	//Audio
	//void playAudio(unsigned int Source, glm::vec3 pos);

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

	//Meshes TODO: Rework into list/vector or something
	//Mesh mesh1;
	//Mesh mesh2;

	//Camera
	Camera myCamera;

	//Shaders TODO: Rework into list/vector or something
	//Shader fogShader;
	//Shader toonShader;
	//Shader rimShader;
	//Shader bump;
	//Shader noBump;
	//Shader what;

	//Textures TODO: Rework into list/vector or something
	//Texture texture1;

};

