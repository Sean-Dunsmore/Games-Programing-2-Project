#include "BumpScene.h"

//Constructor
BumpScene::BumpScene()
{

	bump = new Shader;
	noBump = new Shader;
	texture = new Texture;
	bumpMapping = new Texture;
	mesh = new Mesh;
	transform = new Transform;
}

//Deconstructor
BumpScene::~BumpScene()
{
	cleanup();
}

//Initilize game
void BumpScene::initaliseScene(Camera &myCamera)
{

	//Load shader
	bump->init("..\\res\\bump.vert", "..\\res\\bump.frag");
	noBump->init("..\\res\\noBump.vert", "..\\res\\noBump.frag");

	//Load texture
	texture->load("..\\res\\rock.jpg");

	//Load bumpmap
	bumpMapping->loadNormals("..\\res\\n.jpg");

	//Load mesh
	Vertex vertices[] = { Vertex(glm::vec3(-1.0, 1.0, 0), glm::vec2(0.0, 1.0)),
					Vertex(glm::vec3(1.0, 1.0, 0), glm::vec2(1.0, 1.0)),
					Vertex(glm::vec3(-1.0, -1.0, 0), glm::vec2(0.0, 0.0)),
					Vertex(glm::vec3(-1.0, -1.0, 0), glm::vec2(0.0, 0.0)),
					Vertex(glm::vec3(1.0, 1.0, 0), glm::vec2(1.0, 1.0)),
					Vertex(glm::vec3(1.0, -1.0, 0), glm::vec2(1.0, 0.0)) };

	mesh->loadVertexs(vertices, sizeof(vertices) / sizeof(vertices[0]));

	//Set camera lookat
	myCamera.setPos(glm::vec3(2, 0, -4));
	myCamera.setUp(glm::vec3(0, 1, 0));
	myCamera.setLook(glm::vec3(1.0, 0.0, 0.0));
};

//Process inputs from user
void BumpScene::processInput(time_t dt)
{
	if (GetKeyState(VK_NUMPAD1) & 0x8000)
	{
		hasBump = true;
	}
	if (GetKeyState(VK_NUMPAD2) & 0x8000)
	{
		hasBump = false;
	}
};

//Main update function
void BumpScene::updateScene(time_t dt)
{
	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform->SetPos(glm::vec3(1.0, 0.0, 0.0));
	transform->SetRot(glm::vec3(0.0, sin(counter), 0.0));
	transform->SetScale(glm::vec3(1.5, 1.5, 1.5));

};

//Set visuals from game data
void BumpScene::draw(time_t dt, Camera myCamera)
{

	if (hasBump)
	{
		//Bind bump shader
		bump->Bind();
		linkBumpMapping();
		bump->Update(*transform, myCamera);
	}
	else
	{
		//Bind bump shader
		noBump->Bind();
		linkNoBump();
		noBump->Update(*transform, myCamera);
	}

	mesh->drawVertexes();
};

//Link bump map shader
void BumpScene::linkBumpMapping()
{
	GLuint t1L = glGetUniformLocation(bump->getID(), "diffuse"); //texture 1 location
	GLuint t2L = glGetUniformLocation(bump->getID(), "normalT");

	//set textures
	glActiveTexture(GL_TEXTURE0); //set active texture unit
	glBindTexture(GL_TEXTURE_2D, texture->getID());
	glUniform1i(t1L, 0);

	glActiveTexture(GL_TEXTURE1); //set active texture unit
	glBindTexture(GL_TEXTURE_2D, bumpMapping->getID());
	glUniform1i(t2L, 1);
}

//Link no bump map shader
void BumpScene::linkNoBump()
{
	GLuint t1L = glGetUniformLocation(bump->getID(), "diffuse"); //texture 1 location

	//set textures
	glActiveTexture(GL_TEXTURE0); //set active texture unit
	glBindTexture(GL_TEXTURE_2D, texture->getID());
	glUniform1i(t1L, 0);

}

//Cleanup
void BumpScene::cleanup()
{
	delete bump;
	bump = nullptr;

	delete noBump;
	noBump = nullptr;

	delete texture;
	texture = nullptr;

	delete bumpMapping;
	bumpMapping = nullptr;

	delete mesh;
	mesh = nullptr;

	delete transform;
	transform = nullptr;
}