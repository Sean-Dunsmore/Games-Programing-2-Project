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
	myCamera.setLook(*transform->GetPos());
	myCamera.setPos(glm::vec3(2, 0, -4));
	myCamera.setUp(glm::vec3(0, 1, 0));
};

//Reset the game
void ToonScene::resetScene()
{

}

//Process inputs from user
void ToonScene::processInput(time_t dt)
{

};

//Main update function
void ToonScene::updateScene(time_t dt)
{

};

//Set visuals from game data
void ToonScene::draw(time_t dt, Camera myCamera)
{

	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(-sinf(counter), -0.5, 10.0 + (-sinf(counter) * 8)));
	transform->SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform->SetScale(glm::vec3(0.6, 0.6, 0.6));

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