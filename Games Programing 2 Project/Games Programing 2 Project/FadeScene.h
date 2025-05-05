#pragma once
#include "Scene.h"
#include <windows.h>

class FadeScene : public Scene
{
public:

	FadeScene(); //Constructor
	~FadeScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void resetScene(); //Reset Game

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkFadeShader(); //Link fade shader

	void cleanup();

	Shader* fade;
	Texture* texture1;
	Texture* texture2;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;

};
