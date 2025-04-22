#pragma once
#include "Scene.h"

class BumpScene: public Scene
{
public:

	BumpScene(); //Default Constructor
	~BumpScene(); //Default Deconstructor

	void initaliseScene(); //Initilize Scene

	void resetScene(); //Reset Game

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkBumpMapping(); //Link bump mapping

	void cleanup();

	Shader bump;
	Texture texture;
	Texture bumpMapping;
	Mesh mesh;
	Transform transform;

	float counter = 1;

};

