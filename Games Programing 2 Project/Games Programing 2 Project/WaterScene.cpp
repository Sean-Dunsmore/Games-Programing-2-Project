#include "WaterScene.h"

//Constructor
WaterScene::WaterScene()
{

	water = new Shader;
	texture = new Texture;
	mesh = new Mesh;
	transform = new Transform;
}

//Deconstructor
WaterScene::~WaterScene()
{
	cleanup();
}

//Initilize game
void WaterScene::initaliseScene(Camera& myCamera)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Load shader
	water->init("..\\res\\water.vert", "..\\res\\water.frag");

	//Load texture
	texture->load("..\\res\\water.jpg");

	//Load mesh
	mesh->loadModel("..\\res\\surface.obj");

	//Set camera lookat
	myCamera.setLook(*transform->GetPos());
	myCamera.setPos(glm::vec3(2, 5, -4));
	myCamera.setUp(glm::vec3(0, 1, 0));
};

//Reset the game
void WaterScene::resetScene()
{

}

//Process inputs from user
void WaterScene::processInput(time_t dt)
{

};

//Main update function
void WaterScene::updateScene(time_t dt)
{

};

//Set visuals from game data
void WaterScene::draw(time_t dt, Camera myCamera)
{

	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(0, 1, 0.0));
	transform->SetRot(glm::vec3(3, 0, 0));
	transform->SetScale(glm::vec3(0.1, 0.1, 0.1));

	//Bind water shader
	water->Bind();
	linkWaterShader();
	water->Update(*transform, myCamera);

	mesh->draw();

};

void WaterScene::linkWaterShader()
{
	water->setFloat("counter", counter);

	//set textures
	GLuint t1L = glGetUniformLocation(water->getID(), "diffuse"); //texture 1 location
	texture->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void WaterScene::cleanup()
{
	delete water;
	water = nullptr;

	delete texture;
	texture = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;
}