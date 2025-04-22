#include "BumpScene.h"

//Constructor
BumpScene::BumpScene()
{

}

//Deconstructor
BumpScene::~BumpScene()
{
	cleanup();
}

//Initilize game
void BumpScene::initaliseScene()
{

	//Load shader
	bump.init("..\\res\\bump.vert", "..\\res\\bump.frag");
	
	//Load texture
	texture.load("..\\res\\rock.jpg");

	//Load bumpmap
	bumpMapping.loadNormals("..\\res\\n.jpg");

	//Load mesh
	Vertex vertices[] = { Vertex(glm::vec3(-1.0, 1.0, 0), glm::vec2(0.0, 1.0)),
					Vertex(glm::vec3(1.0, 1.0, 0), glm::vec2(1.0, 1.0)),
					Vertex(glm::vec3(-1.0, -1.0, 0), glm::vec2(0.0, 0.0)),
					Vertex(glm::vec3(-1.0, -1.0, 0), glm::vec2(0.0, 0.0)),
					Vertex(glm::vec3(1.0, 1.0, 0), glm::vec2(1.0, 1.0)),
					Vertex(glm::vec3(1.0, -1.0, 0), glm::vec2(1.0, 0.0)) };

	mesh.loadVertexs(vertices, sizeof(vertices) / sizeof(vertices[0]));

};

//Reset the game
void BumpScene::resetScene()
{

}

//Process inputs from user
void BumpScene::processInput(time_t dt)
{
	
};

//Main update function
void BumpScene::updateScene(time_t dt)
{

};

//Set visuals from game data
void BumpScene::draw(time_t dt, Camera myCamera)
{

	//Update counter
	counter = counter + (0.0003f * dt);

	//Update transform position
	transform.SetPos(glm::vec3(1.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, sin(counter), 0.0));
	transform.SetScale(glm::vec3(1.5, 1.5, 1.5));

	//Bind bump shader
	bump.Bind();
	linkBumpMapping();
	bump.Update(transform, myCamera);
	mesh.drawVertexes();

	//Set camera lookat TODO:remove this
	myCamera.setLook(*transform.GetPos());

};

void BumpScene::linkBumpMapping()
{
	GLuint t1L = glGetUniformLocation(bump.getID(), "diffuse"); //texture 1 location
	GLuint t2L = glGetUniformLocation(bump.getID(), "normalT");

	//set textures
	glActiveTexture(GL_TEXTURE0); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, texture.getID());
	glUniform1i(t1L, 0);

	glActiveTexture(GL_TEXTURE1); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, bumpMapping.getID());
	glUniform1i(t2L, 1);
}

//Cleanup
void BumpScene::cleanup()
{
	
}