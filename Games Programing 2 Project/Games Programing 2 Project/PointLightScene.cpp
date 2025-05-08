#include "PointLightScene.h"

//Constructor
PointLightScene::PointLightScene()
{

	light = new Shader;
	texture = new Texture;
	mesh = new Mesh;
	transform = new Transform;

	lightMesh = new Mesh;
	lightTransform = new Transform;
}

//Deconstructor
PointLightScene::~PointLightScene()
{
	cleanup();
}

//Initilize game
void PointLightScene::initaliseScene(Camera& myCamera)
{

	//Load shader
	light->init("..\\res\\Light.vert", "..\\res\\Light.frag");

	//Load texture
	texture->load("..\\res\\white.jpg");

	//Load mesh
	mesh->loadModel("..\\res\\surface.obj");
	lightMesh->loadModel("..\\res\\ball.obj");

	//Set camera lookat
	myCamera.setPos(glm::vec3(1, 4, 6));
	myCamera.setUp(glm::vec3(0, 1, 0));
	myCamera.setLook(glm::vec3(0, 1.5, 1));
};

//Reset the game
void PointLightScene::resetScene()
{

}

//Process inputs from user
void PointLightScene::processInput(time_t dt)
{
	//Control position of light
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
		posY = 1.3;
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
void PointLightScene::updateScene(time_t dt)
{
	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(0, 1, 0.0));
	transform->SetRot(glm::vec3(3, 0, 0));
	transform->SetScale(glm::vec3(0.1, 0.1, 0.1));

	//Update light position
	lightTransform->SetPos(glm::vec3(posX, posY, posZ));
	lightTransform->SetRot(glm::vec3(3, -1, 0));
	lightTransform->SetScale(glm::vec3(0.1, 0.1, 0.1));

};

//Set visuals from game data
void PointLightScene::draw(time_t dt, Camera myCamera)
{

	//Bind bump shader
	light->Bind();
	linkLightShader(myCamera);
	light->Update(*transform, myCamera);

	mesh->draw();

	light->Update(*lightTransform, myCamera);
	lightMesh->draw();

};

//Link light shader
void PointLightScene::linkLightShader(Camera myCamera)
{
	//Vert 
	light->setMat4("modelMatrix", transform->GetModel());
	light->setVec3("camPos", myCamera.getPos());

	//Frag
	light->setVec3("lightDir", glm::vec3(3, -1, 0));
	light->setVec3("lightPos", glm::vec3(posX, posY, posZ));

	light->setVec4("ambient", glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	light->setVec4("diffuse", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	light->setVec4("specular", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	light->setInt("lightType", lightType);

	//set textures
	GLuint t1L = glGetUniformLocation(light->getID(), "sampler"); //texture 1 location
	texture->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void PointLightScene::cleanup()
{
	delete light;
	light = nullptr;

	delete texture;
	texture = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;

	delete lightMesh;
	lightMesh = nullptr;

	delete lightTransform;
	lightTransform = nullptr;

}