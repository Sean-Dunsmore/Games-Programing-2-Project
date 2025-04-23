#pragma once
#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Camera.h"

//Parent class for all scenes to inherit from
class Scene
{
public:

	Scene(); //Default Constructor
	virtual ~Scene(); //Default Deconstructor

	virtual void initaliseScene(Camera &myCamera) {}; //Initilize Scene

	virtual void resetScene() {}; //Reset Game

	virtual void processInput(time_t dt) {}; //Process inputs from user

	virtual void updateScene(time_t dt) {}; //Main update function

	virtual void draw(time_t dt, Camera myCamera) {}; //Set visuals from game data

protected:

	virtual void cleanup();

};

