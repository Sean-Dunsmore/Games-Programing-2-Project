#pragma once
#include "Scene.h"
#include <windows.h>

class PlanetScene : public Scene
{
public:

	PlanetScene(); //Constructor
	~PlanetScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void resetScene(); //Reset Game

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkPlanetShader(); //Link planet shader

	void cleanup();

	Shader* planet;
	Texture* texture;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;

};
