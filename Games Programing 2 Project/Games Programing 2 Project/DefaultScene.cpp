#include "DefaultScene.h"

//Constructor
DefaultScene::DefaultScene()
{

	fog = new Shader;
	bump = new Shader;
	toon = new Shader;

	rock = new Texture;
	bumpMapping = new Texture;

	fogMesh = new Mesh;
	bumpMesh = new Mesh;
	toonMesh = new Mesh;

	fogTrans = new Transform;
	bumpTrans = new Transform;
	toonTrans = new Transform;

}

//Deconstructor
DefaultScene::~DefaultScene()
{
	cleanup();
}

//Initilize game
void DefaultScene::initaliseScene(Camera& myCamera)
{

	//Load shaders
	fog->init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag");
	bump->init("..\\res\\bump.vert", "..\\res\\bump.frag");
	toon->init("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag");

	//Load textures
	rock->load("..\\res\\rock.jpg");

	//Load bumpmap
	bumpMapping->loadNormals("..\\res\\n.jpg");

	//Load mesh
	fogMesh->loadModel("..\\res\\ball.obj");
	bumpMesh->loadModel("..\\res\\monkey3.obj");
	toonMesh->loadModel("..\\res\\monkey3.obj");

	//Set camera lookat
	myCamera.setLook(*fogTrans->GetPos());
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
	fogTrans->SetPos(glm::vec3(0, 0, 0));
	fogTrans->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	fogTrans->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Update transform position
	bumpTrans->SetPos(glm::vec3(-2, 0, 0));
	bumpTrans->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	bumpTrans->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Update transform position
	toonTrans->SetPos(glm::vec3(2, 0, 0));
	toonTrans->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	toonTrans->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Bind fog shader
	fog->Bind();
	linkFogShader();
	fog->Update(*fogTrans, myCamera);

	fogMesh->draw();

	//Bind bump shader
	bump->Bind();
	linkFogShader();
	bump->Update(*bumpTrans, myCamera);

	bumpMesh->draw();

	//Bind toon shader
	toon->Bind();
	linkToonShader();
	toon->Update(*toonTrans, myCamera);

	toonMesh->draw();

};

void DefaultScene::linkFogShader()
{
	fog->setFloat("maxDist", 20.0f);
	fog->setFloat("minDist", 0.0f);
	fog->setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));

	fog->setInt("rimType", 0);

	//set textures
	GLuint t1L = glGetUniformLocation(fog->getID(), "diffuse"); //texture 1 location
	rock->Bind(0);
	glUniform1i(t1L, 0);

}

void DefaultScene::linkBumpMapping()
{
	GLuint t1L = glGetUniformLocation(bump->getID(), "diffuse"); //texture 1 location
	GLuint t2L = glGetUniformLocation(bump->getID(), "normalT");

	//set textures
	glActiveTexture(GL_TEXTURE0); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, rock->getID());
	glUniform1i(t1L, 0);

	glActiveTexture(GL_TEXTURE1); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, bumpMapping->getID());
	glUniform1i(t2L, 1);
}

void DefaultScene::linkToonShader()
{
	toon->setMat4("modelMatrix", toonTrans->GetModel());
	toon->setVec3("lightDir", glm::vec3(0.5f, 0.5f, -0.5f));

}

//Cleanup
void DefaultScene::cleanup()
{
	delete fog;
	fog = nullptr;

	delete bump;
	bump = nullptr;

	delete rock;
	rock = nullptr;

	delete bumpMapping;
	bumpMapping = nullptr;

	delete fogMesh;
	fogMesh = nullptr;

	delete bumpMesh;
	bumpMesh = nullptr;

	delete toonMesh;
	toonMesh = nullptr;

	delete fogTrans;
	fogTrans = nullptr;

	delete bumpTrans;
	bumpTrans = nullptr;

	delete toonTrans;
	toonTrans = nullptr;

}