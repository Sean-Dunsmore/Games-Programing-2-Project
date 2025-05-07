#pragma once
#include "Scene.h"
#include <windows.h>

class SpotLightScene : public Scene
{
public:

	SpotLightScene(); //Constructor
	~SpotLightScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void resetScene(); //Reset Game

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkLightShader(Camera myCamera); //Link light shader

	void cleanup();

	Shader* light;
	Texture* texture;
	Mesh* mesh;
	Transform* transform;

	Mesh* lightMesh;
	Transform* lightTransform;

	float counter = 1;
	int lightType = 2;

	float RotX = 0.5;
	float RotY = 2;
	float RotZ = 0.5;

	float PosX = 0;
	float PosY = 5;
	float PosZ = 0;

};
