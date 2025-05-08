#include "SpotLightScene.h"

//Constructor
SpotLightScene::SpotLightScene()
{

	light = new Shader;
	texture = new Texture;
	mesh = new Mesh;
	transform = new Transform;

	lightMesh = new Mesh;
	lightTransform = new Transform;
}

//Deconstructor
SpotLightScene::~SpotLightScene()
{
	cleanup();
}

//Initilize game
void SpotLightScene::initaliseScene(Camera& myCamera)
{

	//Load shader
	light->init("..\\res\\Light.vert", "..\\res\\Light.frag");

	//Load texture
	texture->load("..\\res\\white.jpg");

	//Load mesh
	mesh->loadModel("..\\res\\surface.obj");
	lightMesh->loadModel("..\\res\\ball.obj");

	//Set camera lookat
	myCamera.setPos(glm::vec3(2, 50, -100));
	myCamera.setUp(glm::vec3(0, 1, 0));
	myCamera.setLook(glm::vec3(0, 20, 0.0));
};

//Process inputs from user
void SpotLightScene::processInput(time_t dt)
{
	//Control roation of light
	if (GetKeyState(VK_NUMPAD1) & 0x8000)
	{
		rotZ = rotZ - 0.001 * dt;
	}
	if (GetKeyState(VK_NUMPAD2) & 0x8000)
	{
		rotZ = 0.5;
	}
	if (GetKeyState(VK_NUMPAD3) & 0x8000)
	{
		rotZ = rotZ + 0.001 * dt;
	}
	if (GetKeyState(VK_NUMPAD4) & 0x8000)
	{
		rotY = rotY - 0.001 * dt;
	}
	if (GetKeyState(VK_NUMPAD5) & 0x8000)
	{
		rotY = 2;
	}
	if (GetKeyState(VK_NUMPAD6) & 0x8000)
	{
		rotY = rotY + 0.001 * dt;
	}
	if (GetKeyState(VK_NUMPAD7) & 0x8000)
	{
		rotX = rotX - 0.001 * dt;
	}
	if (GetKeyState(VK_NUMPAD8) & 0x8000)
	{
		rotX = 0.5;
	}
	if (GetKeyState(VK_NUMPAD9) & 0x8000)
	{
		rotX = rotX + 0.001 * dt;
	}

};

//Main update function
void SpotLightScene::updateScene(time_t dt)
{
	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(0, 1, 0.0));
	transform->SetRot(glm::vec3(3, 0, 0));
	transform->SetScale(glm::vec3(0.1, 0.1, 0.1));

	//Update light position
	lightTransform->SetPos(glm::vec3(0, 1.3, 0));
	lightTransform->SetRot(glm::vec3(rotX, rotY, rotZ));
	lightTransform->SetScale(glm::vec3(0.1, 0.1, 0.1));
};

//Set visuals from game data
void SpotLightScene::draw(time_t dt, Camera myCamera)
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
void SpotLightScene::linkLightShader(Camera myCamera)
{
	//Vert 
	light->setMat4("modelMatrix", transform->GetModel());
	light->setVec3("camPos", myCamera.getPos());

	//Frag
	light->setVec3("lightDir", glm::vec3(rotX, rotY, rotZ));
	light->setVec3("lightPos", glm::vec3(0, 1.3, 0));

	light->setVec4("ambient", glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	light->setVec4("diffuse", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	light->setVec4("specular", glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	light->setInt("lightType", lightType);

	//set textures
	GLuint t1L = glGetUniformLocation(light->getID(), "sampler"); //texture 1 location
	texture->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void SpotLightScene::cleanup()
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