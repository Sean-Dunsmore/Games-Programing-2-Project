#include "DefaultScene.h"

//Constructor
DefaultScene::DefaultScene()
{

	light = new Shader;
	texture1 = new Texture;
	mesh = new Mesh;
	transform = new Transform;
}

//Deconstructor
DefaultScene::~DefaultScene()
{
	cleanup();
}

//Initilize game
void DefaultScene::initaliseScene(Camera& myCamera)
{

	//Load shader
	light->init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag");

	//Load texture
	texture1->load("..\\res\\bricks.jpg");

	//Load mesh
	mesh->loadModel("..\\res\\monkey3.obj");

	//Set camera lookat
	myCamera.setLook(*transform->GetPos());
	myCamera.setPos(glm::vec3(2, 0, -4));
	myCamera.setUp(glm::vec3(0, 1, 0));
};

//Reset the game
void DefaultScene::resetScene()
{

}

//Process inputs from user
void DefaultScene::processInput(time_t dt)
{

};

//Main update function
void DefaultScene::updateScene(time_t dt)
{

};

//Set visuals from game data
void DefaultScene::draw(time_t dt, Camera myCamera)
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

void DefaultScene::linkLightShader()
{
	light->setFloat("maxDist", 20.0f);
	light->setFloat("minDist", 0.0f);
	light->setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));

	light->setInt("rimType", lightType);

	//set textures
	GLuint t1L = glGetUniformLocation(light->getID(), "diffuse"); //texture 1 location
	texture1->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void DefaultScene::cleanup()
{
	delete light;
	light = nullptr;

	delete texture1;
	texture1 = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;
}