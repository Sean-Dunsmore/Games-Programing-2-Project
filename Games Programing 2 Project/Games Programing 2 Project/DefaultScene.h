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
	void linkFadeShader(); //Link Fade shader
	void linkNormalTexShader(); //Link Normal tex shader
	void linkWaterShader(); //Link Water shader
	void linkLightShader(Camera myCamera, Transform* transform); //Link light shader

	void cleanup();

	//Shaders
	Shader* fog;
	Shader* bump;
	Shader* toon;

	Shader* fade;
	Shader* normal;
	Shader* water;
	Shader* light;

	//Textures
	Texture* rock;

	Texture* bricks;
	Texture* brickwall;
	Texture* waterTex;
	Texture* white;

	Texture* bumpMapping;

	//Meshes
	Mesh* fogMesh;
	Mesh* bumpMesh;
	Mesh* toonMesh;

	Mesh* fadeMesh;
	Mesh* normalMesh;
	Mesh* waterMesh;
	Mesh* ambientMesh;
	Mesh* pointMesh;
	Mesh* spotMesh;

	//Transforms
	Transform* fogTrans;
	Transform* bumpTrans;
	Transform* toonTrans;

	Transform* fadeTrans;
	Transform* normalTrans;
	Transform* waterTrans;
	Transform* ambientTrans;
	Transform* pointTrans;
	Transform* spotTrans;

	float counter = 1;
	int lightType = 0;

};

