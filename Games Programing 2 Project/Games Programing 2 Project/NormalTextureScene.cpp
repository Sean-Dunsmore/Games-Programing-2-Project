#include "NormalTextureScene.h"

//Constructor
NormalTextureScene::NormalTextureScene()
{

	normalTex = new Shader;
	texture = new Texture;
	mesh = new Mesh;
	transform = new Transform;
}

//Deconstructor
NormalTextureScene::~NormalTextureScene()
{
	cleanup();
}

//Initilize game
void NormalTextureScene::initaliseScene(Camera& myCamera)
{

	//Load shader
	normalTex->init("..\\res\\normalTex.vert", "..\\res\\normalTex.frag");

	//Load texture
	texture->load("..\\res\\white.jpg");

	//Load mesh
	mesh->loadModel("..\\res\\monkey3.obj");

	//Set camera lookat
	myCamera.setPos(glm::vec3(2, 0, -4));
	myCamera.setUp(glm::vec3(0, 1, 0));
	myCamera.setLook(glm::vec3(0, 0, 0));
};

//Process inputs from user
void NormalTextureScene::processInput(time_t dt)
{

	//Control position of transform
	if (GetKeyState(VK_NUMPAD1) & 0x8000)
	{
		posZ = posZ - 0.001 * dt;
	}
	if (GetKeyState(VK_NUMPAD2) & 0x8000)
	{
		posZ = 0;
	}
	if (GetKeyState(VK_NUMPAD3) & 0x8000)
	{
		posZ = posZ + 0.001 * dt;
	}
	if (GetKeyState(VK_NUMPAD4) & 0x8000)
	{
		posY = posY - 0.001 * dt;
	}
	if (GetKeyState(VK_NUMPAD5) & 0x8000)
	{
		posY = 0;
	}
	if (GetKeyState(VK_NUMPAD6) & 0x8000)
	{
		posY = posY + 0.001 * dt;
	}
	if (GetKeyState(VK_NUMPAD7) & 0x8000)
	{
		posX = posX - 0.001 * dt;
	}
	if (GetKeyState(VK_NUMPAD8) & 0x8000)
	{
		posX = 0;
	}
	if (GetKeyState(VK_NUMPAD9) & 0x8000)
	{
		posX = posX + 0.001 * dt;
	}
};

//Main update function
void NormalTextureScene::updateScene(time_t dt)
{
	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(posX, posY, posZ));
	transform->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	transform->SetScale(glm::vec3(0.6, 0.6, 0.6));

};

//Set visuals from game data
void NormalTextureScene::draw(time_t dt, Camera myCamera)
{

	//Bind bump shader
	normalTex->Bind();
	linkNormalTexShader();
	normalTex->Update(*transform, myCamera);

	mesh->draw();

};

//Link normal shader
void NormalTextureScene::linkNormalTexShader()
{

	normalTex->setMat4("modelMatrix", transform->GetModel());

	//set textures
	GLuint t1L = glGetUniformLocation(normalTex->getID(), "diffuse"); //texture 1 location
	texture->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void NormalTextureScene::cleanup()
{
	delete normalTex;
	normalTex = nullptr;

	delete texture;
	texture = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;
}