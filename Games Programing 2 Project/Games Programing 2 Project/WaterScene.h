#pragma once
#include "Scene.h"
#include <windows.h>

//Water scene containing a simple water shader that applies a scroling texture, transparancy, and vertex manipulation
//Additonal controls
//4,6 - Change wave Width
//2,8 - Change wave Height
class WaterScene : public Scene
{
public:

	WaterScene(); //Constructor
	~WaterScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkWaterShader(); //Link water shader

	void cleanup(); //Clean up

	Shader* water;
	Texture* texture;
	Mesh* mesh;
	Transform* transform;

	float counter = 0;
	float waveHeight = 20;
	float waveWidth = 0.5;
};
