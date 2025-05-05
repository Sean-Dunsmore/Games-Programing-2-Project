#pragma once
#include "Scene.h"
#include <windows.h>

class DefaultScene : public Scene
{
public:

	DefaultScene(); //Constructor
	~DefaultScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void resetScene(); //Reset Game

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	//Link Shaders
	void linkLightShader(); //Link light shader

	void cleanup();

	Shader* light;
	Texture* texture1;
	Texture* texture2;
	Texture* texture3;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;
	int lightType = 0;

};

