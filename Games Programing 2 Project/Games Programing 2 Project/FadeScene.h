#pragma once
#include "Scene.h"

//Scene containing a shader that fades between 2 textures
//Additional controls on numpad
//1,2,3 - Scale Z
//4,5,6 - Scale Y
//7,8,9 - Scale X
class FadeScene : public Scene
{
public:

	FadeScene(); //Constructor
	~FadeScene(); //Deconstructor

	void initaliseScene(Camera& myCamera); //Initilize Scene

	void processInput(time_t dt); //Process inputs from user

	void updateScene(time_t dt); //Main update function

	void draw(time_t dt, Camera myCamera); //Set visuals from game data

protected:

	void linkFadeShader(); //Link fade shader

	void cleanup(); //Cleanup

	Shader* fade;
	Texture* texture1;
	Texture* texture2;
	Mesh* mesh;
	Transform* transform;

	float counter = 1;

	float scaleX = 0.6;
	float scaleY = 0.6;
	float scaleZ = 0.6;

};
