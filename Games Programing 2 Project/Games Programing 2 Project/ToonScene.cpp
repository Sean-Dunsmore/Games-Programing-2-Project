#include "ToonScene.h"

//Constructor
ToonScene::ToonScene()
{

	toon = new Shader;
	mesh = new Mesh;
	transform = new Transform;
}

//Deconstructor
ToonScene::~ToonScene()
{
	cleanup();
}

//Initilize game
void ToonScene::initaliseScene(Camera& myCamera)
{

	//Load shader
	toon->init("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag");

	//Load mesh
	mesh->loadModel("..\\res\\monkey3.obj");

	//Set camera lookat
	myCamera.setPos(glm::vec3(2, 0, -4));
	myCamera.setUp(glm::vec3(0, 1, 0));
	myCamera.setLook(glm::vec3(0, 0, 0));
};

//Process inputs from user
void ToonScene::processInput(time_t dt)
{
	//Control color
	if (GetKeyState(VK_NUMPAD1) & 0x8000)
	{
		if (B > 0)
		{
			B = B - 0.001 * dt;
		}
		else
		{
			B = 0;
		}
	}
	if (GetKeyState(VK_NUMPAD2) & 0x8000)
	{
		B = 0.5;
	}
	if (GetKeyState(VK_NUMPAD3) & 0x8000)
	{
		if (B < 1)
		{
			B = B + 0.001 * dt;
		}
		else
		{
			B = 1;
		}
	}
	if (GetKeyState(VK_NUMPAD4) & 0x8000)
	{
		if (G > 0)
		{
			G = G - 0.001 * dt;
		}
		else
		{
			G = 0;
		}
	}
	if (GetKeyState(VK_NUMPAD5) & 0x8000)
	{
		G = 0.5;
	}
	if (GetKeyState(VK_NUMPAD6) & 0x8000)
	{
		if (G < 1)
		{
			G = G + 0.001 * dt;
		}
		else
		{
			G = 1;
		}
	}
	if (GetKeyState(VK_NUMPAD7) & 0x8000)
	{
		if (R > 0)
		{
			R = R - 0.001 * dt;
		}
		else
		{
			R = 0;
		}
	}
	if (GetKeyState(VK_NUMPAD8) & 0x8000)
	{
		R = 1;
	}
	if (GetKeyState(VK_NUMPAD9) & 0x8000)
	{
		if (R < 1)
		{
			R = R + 0.001 * dt;
		}
		else
		{
			R = 1;
		}
	}
};

//Main update function
void ToonScene::updateScene(time_t dt)
{
	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(0, 0, 0));
	transform->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	transform->SetScale(glm::vec3(0.6, 0.6, 0.6));

};

//Set visuals from game data
void ToonScene::draw(time_t dt, Camera myCamera)
{

	//Bind bump shader
	toon->Bind();
	linkToonShader();
	toon->Update(*transform, myCamera);

	mesh->draw();

};

void ToonScene::linkToonShader()
{
	toon->setMat4("modelMatrix", transform->GetModel());
	toon->setVec3("lightDir", glm::vec3(0.5f, 0.5f, -0.5f));
	toon->setVec3("inColor", glm::vec3(R, G, B));

}

//Cleanup
void ToonScene::cleanup()
{
	delete toon;
	toon = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;
}