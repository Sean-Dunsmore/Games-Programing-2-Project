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
	void linkFogShader(); //Link fog shader
	void linkBumpMapping(); //Link bump mapping

	void cleanup();

	//Shaders
	Shader* fog;
	Shader* bump;

	//Textures
	Texture* texture1;
	Texture* bumpMapping;

	//Meshes
	Mesh* mesh1;
	Mesh* mesh2;

	//Transforms
	Transform* transform1;
	Transform* transform2;

	float counter = 1;

};

