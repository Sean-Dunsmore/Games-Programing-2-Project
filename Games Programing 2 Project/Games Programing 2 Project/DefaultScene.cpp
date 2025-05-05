#include "DefaultScene.h"

//Constructor
DefaultScene::DefaultScene()
{

	fog = new Shader;
	bump = new Shader;

	texture1 = new Texture;
	bumpMapping = new Texture;

	mesh1 = new Mesh;
	mesh2 = new Mesh;

	transform1 = new Transform;
	transform2 = new Transform;

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
	fog->init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag");
	bump->init("..\\res\\bump.vert", "..\\res\\bump.frag");

	//Load texture
	texture1->load("..\\res\\rock.jpg");

	//Load bumpmap
	bumpMapping->loadNormals("..\\res\\n.jpg");

	//Load mesh
	mesh1->loadModel("..\\res\\ball.obj");
	mesh2->loadModel("..\\res\\monkey3.obj");

	//Set camera lookat
	myCamera.setLook(*transform1->GetPos());
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
	transform1->SetPos(glm::vec3(-sinf(counter), -0.5, 10.0 + (-sinf(counter) * 8)));
	transform1->SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform1->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Update transform position
	transform2->SetPos(glm::vec3(-sinf(-counter), -0.5, 10.0 + (-sinf(-counter) * 8)));
	transform2->SetRot(glm::vec3(0.0, 0.0, -counter * 5));
	transform2->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Bind fog shader
	fog->Bind();
	linkFogShader();
	fog->Update(*transform1, myCamera);

	mesh1->draw();

	//Bind bump shader
	bump->Bind();
	linkFogShader();
	bump->Update(*transform2, myCamera);

	mesh2->draw();

};

void DefaultScene::linkFogShader()
{
	fog->setFloat("maxDist", 20.0f);
	fog->setFloat("minDist", 0.0f);
	fog->setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));

	fog->setInt("rimType", 0);

	//set textures
	GLuint t1L = glGetUniformLocation(fog->getID(), "diffuse"); //texture 1 location
	texture1->Bind(0);
	glUniform1i(t1L, 0);

}

void DefaultScene::linkBumpMapping()
{
	GLuint t1L = glGetUniformLocation(bump->getID(), "diffuse"); //texture 1 location
	GLuint t2L = glGetUniformLocation(bump->getID(), "normalT");

	//set textures
	glActiveTexture(GL_TEXTURE0); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, texture1->getID());
	glUniform1i(t1L, 0);

	glActiveTexture(GL_TEXTURE1); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, bumpMapping->getID());
	glUniform1i(t2L, 1);
}

//Cleanup
void DefaultScene::cleanup()
{
	delete fog;
	fog = nullptr;

	delete bump;
	bump = nullptr;

	delete texture1;
	texture1 = nullptr;

	delete bumpMapping;
	bumpMapping = nullptr;

	delete mesh1;
	mesh1 = nullptr;

	delete mesh2;
	mesh2 = nullptr;

	delete transform1;
	transform1 = nullptr;

	delete transform2;
	transform2 = nullptr;

}