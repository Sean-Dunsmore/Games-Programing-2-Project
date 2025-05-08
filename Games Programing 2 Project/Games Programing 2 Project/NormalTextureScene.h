#pragma once
#include "Scene.h"
#include <windows.h>

//Scene that contains a shader that applies color to an object based on normals
//Additional controls on numpad
//1,2,3 - Move on Z axis
//4,5,6 - Move on Y axis
//7,8,9 - Move on Z axis
class NormalTextureScene : public Scene
{
public:

	NormalTextureScene(); //Constructor
	~NormalTextureScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkNormalTexShader(); //Link light shader

	void cleanup(); //Cleanup

	Shader* normalTex;
	Texture* texture;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;

	float posX = 0;
	float posY = 0;
	float posZ = 0;
};

