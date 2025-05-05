#pragma once
#include "Scene.h"
#include <windows.h>

class PointLightScene : public Scene
{
public:

	PointLightScene(); //Constructor
	~PointLightScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void resetScene(); //Reset Game

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkLightShader(); //Link light shader

	void cleanup();

	Shader* light;
	Texture* texture;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;
	int lightType = 0;

};

