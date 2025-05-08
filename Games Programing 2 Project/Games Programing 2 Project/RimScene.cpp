#include "RimScene.h"

//Constructor
RimScene::RimScene()
{

	fog = new Shader;
	texture = new Texture;
	mesh = new Mesh;
	transform = new Transform;
}

//Deconstructor
RimScene::~RimScene()
{
	cleanup();
}

//Initilize game
void RimScene::initaliseScene(Camera& myCamera)
{

	//Load shader
	fog->init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag");

	//Load texture
	texture->load("..\\res\\bricks.jpg");

	//Load mesh
	mesh->loadModel("..\\res\\monkey3.obj");

	//Set camera lookat
	myCamera.setPos(glm::vec3(2, 0, -4));
	myCamera.setUp(glm::vec3(0, 1, 0));
	myCamera.setLook(glm::vec3(-sinf(counter), -0.5, 10.0 + (-sinf(counter) * 8)));
};

//Process inputs from user
void RimScene::processInput(time_t dt)
{

	//Swap rim
	if (GetKeyState(VK_NUMPAD1) & 0x8000)
	{
		rimType = 1;
	}
	if (GetKeyState(VK_NUMPAD2) & 0x8000)
	{
		rimType = 2;
	}
	if (GetKeyState(VK_NUMPAD3) & 0x8000)
	{
		rimType = 3;
	}

};

//Main update function
void RimScene::updateScene(time_t dt)
{
	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(-sinf(counter), -0.5, 10.0 + (-sinf(counter) * 8)));
	transform->SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform->SetScale(glm::vec3(0.6, 0.6, 0.6));
};

//Set visuals from game data
void RimScene::draw(time_t dt, Camera myCamera)
{

	//Bind bump shader
	fog->Bind();
	linkFogShader(myCamera);
	fog->Update(*transform, myCamera);

	mesh->draw();

};

//Link fog shader
void RimScene::linkFogShader(Camera myCamera)
{
	fog->setFloat("maxDist", 20.0f);
	fog->setFloat("minDist", 0.0f);
	fog->setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));

	fog->setInt("rimType", rimType);

	fog->setVec3("camPos", myCamera.getPos());
	fog->setMat4("modelMatrix", transform->GetModel());

	//set textures
	GLuint t1L = glGetUniformLocation(fog->getID(), "diffuse"); //texture 1 location
	texture->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void RimScene::cleanup()
{
	delete fog;
	fog = nullptr;

	delete texture;
	texture = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;
}