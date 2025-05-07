#include "AmbientLightScene.h"

//Constructor
AmbientLightScene::AmbientLightScene()
{

	light = new Shader;
	texture = new Texture;
	mesh = new Mesh;
	transform = new Transform;

	lightMesh = new Mesh;
	lightTransform = new Transform;

}

//Deconstructor
AmbientLightScene::~AmbientLightScene()
{
	cleanup();
}

//Initilize game
void AmbientLightScene::initaliseScene(Camera& myCamera)
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

//Reset the game
void AmbientLightScene::resetScene()
{

}

//Process inputs from user
void AmbientLightScene::processInput(time_t dt)
{
	if (GetKeyState('1') & 0x8000)
	{
		RotX = RotX + 0.001 * dt;
	}
	if (GetKeyState('2') & 0x8000)
	{
		RotY = RotY + 0.001 * dt;
	}
	if (GetKeyState('3') & 0x8000)
	{
		RotZ = RotZ + 0.001 * dt;
	}

	if (GetKeyState('7') & 0x8000)
	{
		PosX = PosX + 0.001 * dt;
	}
	if (GetKeyState('8') & 0x8000)
	{
		PosY = PosY + 0.001 * dt;
	}
	if (GetKeyState('9') & 0x8000)
	{
		PosZ = PosZ + 0.001 * dt;
	}
};

//Main update function
void AmbientLightScene::updateScene(time_t dt)
{

};

//Set visuals from game data
void AmbientLightScene::draw(time_t dt, Camera myCamera)
{

	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(0, 1, 0.0));
	transform->SetRot(glm::vec3(3, 0, 0));
	transform->SetScale(glm::vec3(0.1, 0.1, 0.1));

	//Update light position
	lightTransform->SetPos(glm::vec3(PosX, PosY, PosZ));
	lightTransform->SetRot(glm::vec3(RotX, RotY, RotZ));
	lightTransform->SetScale(glm::vec3(0.1, 0.1, 0.1));

	//Bind bump shader
	light->Bind();
	linkLightShader(myCamera);
	light->Update(*transform, myCamera);

	mesh->draw();

	light->Update(*lightTransform, myCamera);
	lightMesh->draw();
};

void AmbientLightScene::linkLightShader(Camera myCamera)
{

	//Vert 
	light->setMat4("modelMatrix", transform->GetModel());
	light->setVec3("camPos", myCamera.getPos());

	//Frag
	light->setVec3("lightDir", glm::vec3(RotX, RotY, RotZ));
	light->setVec3("lightPos", glm::vec3(PosX, PosY, PosZ));

	light->setVec4("ambient", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	light->setVec4("diffuse", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	light->setVec4("specular", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	light->setInt("lightType", lightType);

	//set textures
	GLuint t1L = glGetUniformLocation(light->getID(), "sampler"); //texture 1 location
	texture->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void AmbientLightScene::cleanup()
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