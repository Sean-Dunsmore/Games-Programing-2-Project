#include "DefaultScene.h"

//Constructor
DefaultScene::DefaultScene()
{

	fog = new Shader;
	bump = new Shader;
	toon = new Shader;
	fade = new Shader;
	normal = new Shader;
	water = new Shader;
	light = new Shader;

	rock = new Texture;
	bricks = new Texture;
	brickwall = new Texture;
	waterTex = new Texture;
	white = new Texture;
	bumpMapping = new Texture;

	fogMesh = new Mesh;
	bumpMesh = new Mesh;
	toonMesh = new Mesh;
	fadeMesh = new Mesh;
	normalMesh = new Mesh;
	waterMesh = new Mesh;
	ambientMesh = new Mesh;
	pointMesh = new Mesh;
	spotMesh = new Mesh;

	fogTrans = new Transform;
	bumpTrans = new Transform;
	toonTrans = new Transform;
	fadeTrans = new Transform;
	normalTrans = new Transform;
	waterTrans = new Transform;
	ambientTrans = new Transform;
	pointTrans = new Transform;
	spotTrans = new Transform;

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
	fade->init("..\\res\\fade.vert", "..\\res\\fade.frag");
	normal->init("..\\res\\normalTex.vert", "..\\res\\normalTex.frag");
	water->init("..\\res\\water.vert", "..\\res\\water.frag");
	light->init("..\\res\\Light.vert", "..\\res\\Light.frag");

	//Load textures
	rock->load("..\\res\\rock.jpg");
	bricks->load("..\\res\\bricks.jpg");
	brickwall->load("..\\res\\brickwall.jpg");
	waterTex->load("..\\res\\water.jpg");
	white->load("..\\res\\white.jpg");

	//Load bumpmap
	bumpMapping->loadNormals("..\\res\\n.jpg");

	//Load mesh
	fogMesh->loadModel("..\\res\\ball.obj");
	bumpMesh->loadModel("..\\res\\monkey3.obj");
	toonMesh->loadModel("..\\res\\monkey3.obj");
	fadeMesh->loadModel("..\\res\\monkey3.obj");;
	normalMesh->loadModel("..\\res\\monkey3.obj");;
	waterMesh->loadModel("..\\res\\surface.obj");;
	ambientMesh->loadModel("..\\res\\ball.obj");;
	pointMesh->loadModel("..\\res\\monkey3.obj");;
	spotMesh->loadModel("..\\res\\ball.obj");;

	//Set camera lookat
	myCamera.setPos(glm::vec3(0, 3, -5));
	myCamera.setUp(glm::vec3(0, 1, 0));
	myCamera.setLook(glm::vec3(0, 0, 0));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
};

//Process inputs from user
void DefaultScene::processInput(time_t dt)
{

};

//Main update function
void DefaultScene::updateScene(time_t dt)
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

	//Update transform position
	fadeTrans->SetPos(glm::vec3(-1, 0, -2));
	fadeTrans->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	fadeTrans->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Update transform position
	normalTrans->SetPos(glm::vec3(1, 0, -2));
	normalTrans->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	normalTrans->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Update transform position
	waterTrans->SetPos(glm::vec3(0, -50, 0));
	waterTrans->SetRot(glm::vec3(0.0, 0.0, 0.0));
	waterTrans->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Update transform position
	ambientTrans->SetPos(glm::vec3(2, 0, 2));
	ambientTrans->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	ambientTrans->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Update transform position
	pointTrans->SetPos(glm::vec3(0, 0, 2));
	pointTrans->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	pointTrans->SetScale(glm::vec3(0.6, 0.6, 0.6));

	//Update transform position
	spotTrans->SetPos(glm::vec3(-2, 0, 2));
	spotTrans->SetRot(glm::vec3(0.0, counter * 1, 0.0));
	spotTrans->SetScale(glm::vec3(0.6, 0.6, 0.6));
};

//Set visuals from game data
void DefaultScene::draw(time_t dt, Camera myCamera)
{

	//Bind fog shader
	fog->Bind();
	linkFogShader(myCamera);
	fog->Update(*fogTrans, myCamera);

	fogMesh->draw();

	//Bind bump shader
	bump->Bind();
	linkBumpMapping();
	bump->Update(*bumpTrans, myCamera);

	bumpMesh->draw();

	//Bind toon shader
	toon->Bind();
	linkToonShader();
	toon->Update(*toonTrans, myCamera);

	toonMesh->draw();

	//Bind fade shader
	fade->Bind();
	linkFadeShader();
	fade->Update(*fadeTrans, myCamera);

	fadeMesh->draw();

	//Bind normal shader
	normal->Bind();
	linkNormalTexShader();
	normal->Update(*normalTrans, myCamera);

	normalMesh->draw();

	//Bind water shader
	water->Bind();
	linkWaterShader();
	water->Update(*waterTrans, myCamera);

	waterMesh->draw();

	//Bind ambient shader
	lightType = 0;

	light->Bind();
	linkLightShader(myCamera, ambientTrans);
	light->Update(*ambientTrans, myCamera);

	ambientMesh->draw();

	//Bind point shader
	lightType = 1;

	light->Bind();
	linkLightShader(myCamera, pointTrans);
	light->Update(*pointTrans, myCamera);

	pointMesh->draw();

	//Bind Spot shader
	lightType = 3;

	light->Bind();
	linkLightShader(myCamera, spotTrans);
	light->Update(*spotTrans, myCamera);

	spotMesh->draw();
};

//Link rim shader
void DefaultScene::linkFogShader(Camera myCamera)
{
	

	fog->setFloat("maxDist", 20.0f);
	fog->setFloat("minDist", 0.0f);
	fog->setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));

	fog->setInt("rimType", 0);

	fog->setVec3("camPos", myCamera.getPos());
	fog->setMat4("modelMatrix", fogTrans->GetModel());

	//set textures
	GLuint t1L = glGetUniformLocation(fog->getID(), "diffuse"); //texture 1 location
	rock->Bind(0);
	glUniform1i(t1L, 0);

}

//Link bump shader
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

//Link toon shader
void DefaultScene::linkToonShader()
{
	toon->setMat4("modelMatrix", toonTrans->GetModel());
	toon->setVec3("lightDir", glm::vec3(0.5f, 0.5f, -0.5f));
	toon->setVec3("inColor", glm::vec3(1.0, 0.5, 0.5));
}

//Link fade shader
void DefaultScene::linkFadeShader()
{
	fade->setFloat("counter", counter);

	//set textures
	GLuint t1L = glGetUniformLocation(fade->getID(), "diffuse1"); //texture 1 location
	brickwall->Bind(0);
	glUniform1i(t1L, 0);

	GLuint t2L = glGetUniformLocation(fade->getID(), "diffuse2"); //texture 1 location
	rock->Bind(1);
	glUniform1i(t2L, 1);

}

//Link normal shader
void DefaultScene::linkNormalTexShader()
{

	normal->setMat4("modelMatrix", normalTrans->GetModel());

	//set textures
	GLuint t1L = glGetUniformLocation(normal->getID(), "diffuse"); //texture 1 location
	white->Bind(0);
	glUniform1i(t1L, 0);

}

//Link water shader
void DefaultScene::linkWaterShader()
{
	water->setFloat("counter", counter);
	water->setFloat("height", 20);
	water->setFloat("width", 0.5);

	//set textures
	GLuint t1L = glGetUniformLocation(water->getID(), "diffuse"); //texture 1 location
	waterTex->Bind(0);
	glUniform1i(t1L, 0);

}

//Link light shader
void DefaultScene::linkLightShader(Camera myCamera, Transform* transform)
{

	//Vert 
	light->setMat4("modelMatrix", transform->GetModel());
	light->setVec3("camPos", myCamera.getPos());

	//Frag
	light->setVec3("lightDir", glm::vec3(-0.5, 2, -0.5));
	light->setVec3("lightPos", glm::vec3(0, 1, 1));
	light->setVec4("ambient", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	light->setVec4("diffuse", glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
	light->setVec4("specular", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	light->setInt("lightType", lightType);

	//set textures
	GLuint t1L = glGetUniformLocation(light->getID(), "sampler"); //texture 1 location
	bricks->Bind(0);
	glUniform1i(t1L, 0);

}

//Cleanup
void DefaultScene::cleanup()
{
	delete fog;
	fog = nullptr;

	delete bump;
	bump = nullptr;

	delete toon;
	toon = nullptr;

	delete fade;
	fade = nullptr;

	delete normal;
	normal = nullptr;

	delete water;
	water = nullptr;

	delete light;
	light = nullptr;

	delete rock;
	rock = nullptr;

	delete bricks;
	bricks = nullptr;

	delete brickwall;
	brickwall = nullptr;

	delete waterTex;
	waterTex = nullptr;

	delete white; 
	white = nullptr;

	delete bumpMapping;
	bumpMapping = nullptr;

	delete fogMesh;
	fogMesh = nullptr;

	delete bumpMesh;
	bumpMesh = nullptr;

	delete toonMesh;
	toonMesh = nullptr;

	delete fadeMesh;
	fadeMesh = nullptr;

	delete normalMesh;
	normalMesh = nullptr;

	delete waterMesh;
	waterMesh = nullptr;

	delete ambientMesh;
	ambientMesh = nullptr;

	delete pointMesh;
	pointMesh = nullptr;

	delete spotMesh;
	spotMesh = nullptr;

	delete fogTrans;
	fogTrans = nullptr;

	delete bumpTrans;
	bumpTrans = nullptr;

	delete toonTrans;
	toonTrans = nullptr;

	delete fadeTrans;
	fadeTrans = nullptr;

	delete normalTrans;
	normalTrans = nullptr;

	delete waterTrans;
	waterTrans = nullptr;

	delete ambientTrans;
	ambientTrans = nullptr;

	delete pointTrans;
	pointTrans = nullptr;

	delete spotTrans;
	spotTrans = nullptr;

}