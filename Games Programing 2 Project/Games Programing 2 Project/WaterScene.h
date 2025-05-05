#pragma once
#include "Scene.h"
#include <windows.h>

class WaterScene : public Scene
{
public:

	WaterScene(); //Constructor
	~WaterScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void resetScene(); //Reset Game

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkWaterShader(); //Link water shader

	void cleanup();

	Shader* water;
	Texture* texture;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;

};
