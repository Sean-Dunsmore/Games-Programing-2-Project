#include "AmbientLightScene.h"

//Constructor
AmbientLightScene::AmbientLightScene()
{

	light = new Shader;
	texture = new Texture;
	mesh = new Mesh;
	transform = new Transform;
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
	light->init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag");

	//Load texture
	texture->load("..\\res\\bricks.jpg");

	//Load mesh
	mesh->loadModel("..\\res\\monkey3.obj");

	//Set camera lookat
	myCamera.setLook(*transform->GetPos());
	myCamera.setPos(glm::vec3(2, 0, -4));
	myCamera.setUp(glm::vec3(0, 1, 0));
};

//Reset the game
void AmbientLightScene::resetScene()
{

}

//Process inputs from user
void AmbientLightScene::processInput(time_t dt)
{

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
	transform->SetPos(glm::vec3(-sinf(counter), -0.5, 10.0 + (-sinf(counter) * 8)));
	transform->SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Bind bump shader
	light->Bind();
	linkLightShader();
	light->Update(*transform, myCamera);

	mesh->draw();

};

void AmbientLightScene::linkLightShader()
{
	light->setFloat("maxDist", 20.0f);
	light->setFloat("minDist", 0.0f);
	light->setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));

	light->setInt("rimType", lightType);

	//set textures
	GLuint t1L = glGetUniformLocation(light->getID(), "diffuse"); //texture 1 location
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
}