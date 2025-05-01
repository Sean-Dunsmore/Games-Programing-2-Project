#pragma once
#include "Scene.h"
#include <windows.h>

class RimScene : public Scene
{
public:

	RimScene(); //Constructor
	~RimScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void resetScene(); //Reset Game

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkFogShader(); //Link fog shader

	void cleanup();

	Shader* fog;
	Texture* texture;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;
	int rimType = 0;

};

