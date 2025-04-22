#pragma once
#include <iostream>
#include <fstream>

//Parent class for all scenes to inherit from
class Scene
{
public:

	Scene(); //Default Constructor
	~Scene(); //Default Deconstructor

	virtual void initaliseScene() {}; //Initilize Scene

	virtual void resetScene() {}; //Reset Game

	virtual void processInput(time_t dt) {}; //Process inputs from user

	virtual void updateScene(time_t dt) {}; //Main update function

	virtual void draw() {}; //Set visuals from game data

protected:

	virtual void cleanup();

};

