#include "Bus.h"

#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

using namespace std;
using namespace glm;

Bus::Bus(int shaderi)
	: mPosition(0.0f, 0.0f, 0.0f), mScaling(0.0f, 0.0f, 0.0f), mRotationAxis(0.0f, 0.0f, 0.0f),
	mRotationAngleInDegrees(0.0f)
{
	shader = shaderi;
	Create();
	SetOriginal();
	initializeTexture();
}

Bus::~Bus()
{
	for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
	{
		delete* it;
	}
}

// Creates parts of the car and puts them in a car object vector
void Bus::Create()
{
	// Body
	cubeVAO = setVAO();
	body = new TexturedCube(cubeVAO, 36, shader);
	carParts.push_back(body);

	// Bonnet
	cubeVAO = setVAO();
	bonnet = new TexturedCube(cubeVAO, 36, shader);
	carParts.push_back(bonnet);

	// Roof
	cubeVAO = setVAO();
	roof = new TexturedCube(cubeVAO, 36, shader);
	carParts.push_back(roof);

	// Exhaust
	cubeVAO = setVAO();
	exhaust = new TexturedCube(cubeVAO, 36, shader);
	carParts.push_back(exhaust);

	
}

void Bus::Update(float dt)
{
	
}

// Set Car to the original position
void Bus::SetOriginal()
{
	// Body
	//vec3 mPosition(0.0f, 1.0f, 0.0f);
	//vec3 mScaling(2.5f, 1.0f, 1.0f);
	//body->setPosition(mPosition);
	//body->setScaling(mScaling);
	body->setScaling(vec3(mScaling.x + 5.0f, mScaling.y + 1.5f, mScaling.z + 1.0f));
	body->setPosition(vec3(mPosition.x + 0.0f, mPosition.y + 1.0f, mPosition.z + 0.0f));


	// Bonnet
//	mPosition = vec3(1.25f, 0.75f, 0.0f);
//	mScaling = vec3(2.0f, 0.5f, 0.95f);
//	bonnet->setPosition(mPosition);
//	bonnet->setScaling(mScaling);
//	bonnet->SetScaling(vec3(mScaling.x + 1.0f, mScaling.y + 0.8f, mScaling.z + 0.95f));
	bonnet->setScaling(vec3(mScaling.x + 1.0f, mScaling.y + 0.8f, mScaling.z + 0.95f));
	bonnet->setPosition(vec3(mPosition.x + 2.4f, mPosition.y + 0.8f, mPosition.z + 0.0f));

	// Roof
//	mPosition = vec3(0.0f, 1.5f, 0.0f);
//	mScaling = vec3(2.4f, 0.50f, 0.95f);
//	roof->setPosition(mPosition);
//	roof->setScaling(mScaling);
	roof->setScaling(vec3(mScaling.x + 4.9f, mScaling.y + 0.5f, mScaling.z + 0.95f));
	roof->setPosition(vec3(mPosition.x + 0.0f, mPosition.y + 1.5f, mPosition.z + 0.0f));

	// Trunk
//	mPosition = vec3(-1.25f, 0.75f, 0.0f);
//	mScaling = vec3(2.0f, 0.5f, 0.95f);
//	exhaust->setPosition(mPosition);
//	exhaust->setScaling(mScaling);
	exhaust->setScaling(vec3(mScaling.x + 0.25f, mScaling.y + 0.2f, mScaling.z + 0.2f));
	exhaust->setPosition(vec3(mPosition.x - 2.5f, mPosition.y + 0.4f, mPosition.z + 0.0f));
}

void Bus::Draw(int shader, GLuint shadow)
{
	glActiveTexture(GL_TEXTURE0);
	GLuint textureLocation = glGetUniformLocation(shader, "textureSampler"); // shader program
	glBindTexture(GL_TEXTURE_2D, busTexture);
	

	glActiveTexture(GL_TEXTURE1);
	GLuint shadowLocation = glGetUniformLocation(shader, "shadowMap");
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadow);
	

	// Draw car parts with textures
	for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
	{

		(*it)->Draw(shader);
	}
	
}


void Bus::Render(int shader)
{
	for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
	{

		glUseProgram(shader);
	//	(*it)->Draw(shader);
	}
	//for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
	//{
	//	(*it)->Draw(shader);
	//}
}


void Bus::SetPosition(glm::vec3 position)
{ 
	mPosition = position;
	//for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
	//{
	//	glm::vec3 partPosition = (*it)->GetPosition();
	//	glm::vec3 setPos = position + partPosition;
	//	(*it)->setPosition(setPos);
	//}
	body->SetPosition(vec3(mPosition.x + 0.0f, mPosition.y + 1.0f, mPosition.z + 0.0f));

	// Bonnet
	bonnet->SetPosition(vec3(mPosition.x + 2.4f, mPosition.y + 0.8f, mPosition.z + 0.0f));

	// Roof
	roof->SetPosition(vec3(mPosition.x + 0.0f, mPosition.y + 1.5f, mPosition.z + 0.0f));

	//Exhaust 
	exhaust->SetPosition(vec3(mPosition.x - 2.5f, mPosition.y + 0.4f, mPosition.z + 0.0f));


}

glm::vec3 Bus::getExhaustpos()
{
	glm::vec3 exhaustpos = exhaust->getPosition();
	return exhaustpos;
}

void Bus::SetScaling(glm::vec3 scaling)
{
	mScaling = scaling;

	for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
	{
		glm::vec3 partScaling = (*it)->getScaling();
		partScaling += scaling;
		(*it)->setScaling(partScaling);
	}
}

void Bus::SetRotation(glm::vec3 axis, float angleDegrees)
{
	mRotationAxis = axis;
	mRotationAngleInDegrees = angleDegrees;

	for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
	{
		(*it)->setRotation(axis, angleDegrees);
	}

}

GLuint Bus::busTexture = 0;

bool Bus::initializeTexture()
{
#if defined(PLATFORM_OSX)
	particleTexture = TextureLoader::LoadTexture("Textures/Particle.png");
#else
	busTexture = TextureLoader::LoadTexture("../Assets/Textures/bus.jpg");
#endif
	return busTexture != 0;
}

GLuint Bus::setVAO()
{
	GLuint cubeVAO = TexturedCube::makeCubeVAO();
	return cubeVAO;
}
