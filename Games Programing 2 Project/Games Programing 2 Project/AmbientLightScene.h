#pragma once
#include "Scene.h"

//Ambient Light Scene
//Scene that contains a single directional light to demonstrate ADS
//Ambient light is red
//Diffuse light is green
//Specular light is blue
//Additional controls on numpad
//1,2,3 - Rotate Light
class AmbientLightScene : public Scene
{
public:

	AmbientLightScene(); //Constructor
	~AmbientLightScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

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

	float counter = 1;
	int lightType = 0;

	float RotX = 3;
	float RotY = -1;
	float RotZ = 0;

};


