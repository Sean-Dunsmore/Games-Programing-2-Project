#pragma once
#include "Scene.h"

//Scene demonstrating a simple bump map on a plane
//Additional controls on numpad
//1,2 - Enable disable bump map
class BumpScene: public Scene
{
public:

	BumpScene(); //Constructor
	~BumpScene(); //Deconstructor

	void initaliseScene(Camera &myCamera); //Initilize Scene

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkBumpMapping(); //Link bump mapping
	void linkNoBump(); //Link No Bump

	void cleanup(); //Clean up

	Shader* bump;
	Shader* noBump;
	Texture* texture;
	Texture* bumpMapping;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;

	bool hasBump = true;
};

