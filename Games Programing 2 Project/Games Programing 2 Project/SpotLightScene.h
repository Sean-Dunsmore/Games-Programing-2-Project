#pragma once
#include "Scene.h"
#include <windows.h>

//Scene that uses the light shader to create a pointlight
//Additional controls
//1,2,3 - Rotate light on Z
//4,5,6 - Rotate light on Y
//7,8,9 - Rotate light on X
class SpotLightScene : public Scene
{
public:

	SpotLightScene(); //Constructor
	~SpotLightScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkLightShader(Camera myCamera); //Link light shader

	void cleanup(); //Clean up

	Shader* light;
	Texture* texture;
	Mesh* mesh;
	Transform* transform;

	//Mesh to represent light
	Mesh* lightMesh;
	Transform* lightTransform;

	float counter = 1;
	int lightType = 2;

	float rotX = 0.5;
	float rotY = 2;
	float rotZ = 0.5;

};
