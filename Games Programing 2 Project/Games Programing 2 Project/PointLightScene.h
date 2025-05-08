#pragma once
#include "Scene.h"
#include <windows.h>

//Scene that uses the light shader to create a point light
//Additional controls on numpad
//1,2,3 - Move light on Z
//4,5,6 - Move light on Y
//7,8,9 - Move light on X
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

	void linkLightShader(Camera myCamera); //Link light shader

	void cleanup(); //Cleanup

	Shader* light;
	Texture* texture;
	Mesh* mesh;
	Transform* transform;

	//Mesh to represent location of light
	Mesh* lightMesh;
	Transform* lightTransform;

	float counter = 1;
	int lightType = 1;

	float posX = 0;
	float posY = 1.3;
	float posZ = 0;

};

