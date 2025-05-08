#pragma once
#include "Scene.h"
#include <windows.h>

//Scene containing a simple toon shader
//Additional controls
//1,2,3 - Change blue color
//4,5,6 - Change green color
//7,8,9 - Change red color
class ToonScene : public Scene
{
public:

	ToonScene(); //Constructor
	~ToonScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkToonShader(); //Link toon shader

	void cleanup(); // Cleanup

	Shader* toon;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;

	float R = 1.0;
	float G = 0.5;
	float B = 0.5;

};

