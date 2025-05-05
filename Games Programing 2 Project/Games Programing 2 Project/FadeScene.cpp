#include "FadeScene.h"

//Constructor
FadeScene::FadeScene()
{

	fade = new Shader;
	texture1 = new Texture;
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
	fade->init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag");

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
	transform->SetPos(glm::vec3(-sinf(counter), -0.5, 10.0 + (-sinf(counter) * 8)));
	transform->SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Bind bump shader
	fade->Bind();
	linkFadeShader();
	fade->Update(*transform, myCamera);

	mesh->draw();

};

void FadeScene::linkFadeShader()
{
	fade->setFloat("maxDist", 20.0f);
	fade->setFloat("minDist", 0.0f);
	fade->setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));

	fade->setInt("rimType", 0);

	//set textures
	GLuint t1L = glGetUniformLocation(fade->getID(), "diffuse"); //texture 1 location
	texture1->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void FadeScene::cleanup()
{
	delete fade;
	fade = nullptr;

	delete texture1;
	texture1 = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;
}