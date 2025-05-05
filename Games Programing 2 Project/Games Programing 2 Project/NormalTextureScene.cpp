#include "NormalTextureScene.h"

//Constructor
NormalTextureScene::NormalTextureScene()
{

	normalTex = new Shader;
	texture1 = new Texture;
	mesh = new Mesh;
	transform = new Transform;
}

//Deconstructor
NormalTextureScene::~NormalTextureScene()
{
	cleanup();
}

//Initilize game
void NormalTextureScene::initaliseScene(Camera& myCamera)
{

	//Load shader
	normalTex->init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag");

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
void NormalTextureScene::resetScene()
{

}

//Process inputs from user
void NormalTextureScene::processInput(time_t dt)
{

};

//Main update function
void NormalTextureScene::updateScene(time_t dt)
{

};

//Set visuals from game data
void NormalTextureScene::draw(time_t dt, Camera myCamera)
{

	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(-sinf(counter), -0.5, 10.0 + (-sinf(counter) * 8)));
	transform->SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Bind bump shader
	normalTex->Bind();
	linkNormalTexShader();
	normalTex->Update(*transform, myCamera);

	mesh->draw();

};

void NormalTextureScene::linkNormalTexShader()
{
	normalTex->setFloat("maxDist", 20.0f);
	normalTex->setFloat("minDist", 0.0f);
	normalTex->setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));

	normalTex->setInt("rimType", 0);

	//set textures
	GLuint t1L = glGetUniformLocation(normalTex->getID(), "diffuse"); //texture 1 location
	texture1->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void NormalTextureScene::cleanup()
{
	delete normalTex;
	normalTex = nullptr;

	delete texture1;
	texture1 = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;
}