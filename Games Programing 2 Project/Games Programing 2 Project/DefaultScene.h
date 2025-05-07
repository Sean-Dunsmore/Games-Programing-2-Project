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
	void linkFogShader(Camera myCamera); //Link fog shader
	void linkBumpMapping(); //Link bump mapping
	void linkToonShader(); //Link toon shader

	void cleanup();

	//Shaders
	Shader* fog;
	Shader* bump;
	Shader* toon;

	//Textures
	Texture* rock;
	Texture* bumpMapping;

	//Meshes
	Mesh* fogMesh;
	Mesh* bumpMesh;
	Mesh* toonMesh;

	//Transforms
	Transform* fogTrans;
	Transform* bumpTrans;
	Transform* toonTrans;

	float counter = 1;

};

