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

	void draw(); //Set visuals from game data

protected:

	void cleanup();

};

