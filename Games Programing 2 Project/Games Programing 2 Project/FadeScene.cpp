#include "FadeScene.h"

//Constructor
FadeScene::FadeScene()
{

	fade = new Shader;
	texture1 = new Texture;
	texture2 = new Texture;
	mesh = new Mesh;
	transform = new Transform;
}

//Deconstructor
FadeScene::~FadeScene()
{
	cleanup();
}

//Initilize game
void FadeScene::initaliseScene(Camera& myCamera)
{

	//Load shader
	fade->init("..\\res\\fade.vert", "..\\res\\fade.frag");

	//Load texture
	texture1->load("..\\res\\brickwall.jpg");
	texture2->load("..\\res\\rock.jpg");

	//Load mesh
	mesh->loadModel("..\\res\\monkey3.obj");

	//Set camera lookat
	myCamera.setLook(*transform->GetPos());
	myCamera.setPos(glm::vec3(2, 0, -4));
	myCamera.setUp(glm::vec3(0, 1, 0));
};

//Reset the game
void FadeScene::resetScene()
{

}

//Process inputs from user
void FadeScene::processInput(time_t dt)
{

};

//Main update function
void FadeScene::updateScene(time_t dt)
{

};

//Set visuals from game data
void FadeScene::draw(time_t dt, Camera myCamera)
{

	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(0, 0, 0));
	transform->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	transform->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Bind bump shader
	fade->Bind();
	linkFadeShader();
	fade->Update(*transform, myCamera);

	mesh->draw();

};

void FadeScene::linkFadeShader()
{
	fade->setFloat("counter", counter);

	//set textures
	GLuint t1L = glGetUniformLocation(fade->getID(), "diffuse1"); //texture 1 location
	texture1->Bind(0);
	glUniform1i(t1L, 0);

	GLuint t2L = glGetUniformLocation(fade->getID(), "diffuse2"); //texture 1 location
	texture2->Bind(1);
	glUniform1i(t2L, 1);

}

//Cleanup
void FadeScene::cleanup()
{
	delete fade;
	fade = nullptr;

	delete texture1;
	texture1 = nullptr;

	delete texture2;
	texture1 = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;
}