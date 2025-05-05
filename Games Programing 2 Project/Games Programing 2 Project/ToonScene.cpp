#include "ToonScene.h"

//Constructor
ToonScene::ToonScene()
{

	toon = new Shader;
	texture = new Texture;
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
	toon->init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag");

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
	toon->setFloat("maxDist", 20.0f);
	toon->setFloat("minDist", 0.0f);
	toon->setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));

	toon->setInt("rimType", 0);

	//set textures
	GLuint t1L = glGetUniformLocation(toon->getID(), "diffuse"); //texture 1 location
	texture->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void ToonScene::cleanup()
{
	delete toon;
	toon = nullptr;

	delete texture;
	texture = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;
}