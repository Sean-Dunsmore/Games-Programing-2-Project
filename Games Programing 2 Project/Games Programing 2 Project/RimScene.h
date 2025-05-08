#pragma once
#include "Scene.h"
#include <windows.h>

//Scene containing a simple rimlight shader
//Addtional controls on numpad
//1,2,3 - Swap rim lighting method and color
class RimScene : public Scene
{
public:

	RimScene(); //Constructor
	~RimScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkFogShader(Camera myCamera); //Link fog shader

	void cleanup(); //Clean up

	Shader* fog;
	Texture* texture;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;
	int rimType = 0;

};

