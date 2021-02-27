#include "WheelModel.h"

#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

using namespace std;
using namespace glm;

WheelModel::WheelModel(int shaderi)
: mPosition(0.0f, 0.0f, 0.0f), mScaling(0.0f, 0.0f, 0.0f), mRotationAxis(0.0f, 0.0f, 0.0f),
	mRotationAngleInDegrees(0.0f)
{
	shader = shaderi;
	Create();
	setRotation();
	initializeTexture();
}

WheelModel::~WheelModel() {
	for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
	{
		delete* it;
	}
}

void WheelModel::Create()
{

	// Body
	cubeVAO = setVAO();
	wheel1 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel1);

	cubeVAO = setVAO();
	wheel2 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel2);

	cubeVAO = setVAO();
	wheel3 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel3);

	cubeVAO = setVAO();
	wheel4 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel4);

	cubeVAO = setVAO();
	wheel5 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel5);

	cubeVAO = setVAO();
	wheel6 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel6);

	cubeVAO = setVAO();
	wheel7 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel7);

	cubeVAO = setVAO();
	wheel8 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel8);

	cubeVAO = setVAO();
	wheel9 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel9);

	cubeVAO = setVAO();
	wheel10 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel10);

	cubeVAO = setVAO();
	wheel11 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel1);

	cubeVAO = setVAO();
	wheel12 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel2);

	cubeVAO = setVAO();
	wheel13 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel3);

	cubeVAO = setVAO();
	wheel14 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel4);

	cubeVAO = setVAO();
	wheel15 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel5);

	cubeVAO = setVAO();
	wheel16 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel6);

	cubeVAO = setVAO();
	wheel17 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel7);

	cubeVAO = setVAO();
	wheel18 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel8);

	cubeVAO = setVAO();
	wheel19 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel9);

	cubeVAO = setVAO();
	wheel20 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel10);

	cubeVAO = setVAO();
	wheel21 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel1);

	cubeVAO = setVAO();
	wheel22 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel2);

	cubeVAO = setVAO();
	wheel23 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel3);

	cubeVAO = setVAO();
	wheel24 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel4);

	cubeVAO = setVAO();
	wheel25 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel5);

	cubeVAO = setVAO();
	wheel26 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel6);

	cubeVAO = setVAO();
	wheel27 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel7);

	cubeVAO = setVAO();
	wheel28 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel8);

	cubeVAO = setVAO();
	wheel29 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel9);

	cubeVAO = setVAO();
	wheel30 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel10);

	cubeVAO = setVAO();
	wheel31 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel1);

	cubeVAO = setVAO();
	wheel32 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel2);

	cubeVAO = setVAO();
	wheel33 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel3);

	cubeVAO = setVAO();
	wheel34 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel4);

	cubeVAO = setVAO();
	wheel35 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel5);

	cubeVAO = setVAO();
	wheel36 = new TexturedCube(cubeVAO, 36, shader);
	wheels.push_back(wheel6);


}

void WheelModel::Update(float dt)
{
}

void WheelModel::Draw(int shader)
{
	glActiveTexture(GL_TEXTURE0);
	GLuint textureLocation = glGetUniformLocation(shader, "textureSampler"); // shader program
	glBindTexture(GL_TEXTURE_2D, wheelTexture);
	glUniform1i(textureLocation, 0);

	for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
	{
		(*it)->Draw(shader);
	}
}

void WheelModel::Render(int shader)
{
}

void WheelModel::SetScaling(glm::vec3 scaling)
{
	mScaling = vec3(scaling);
	for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
	{
		(*it)->SetScaling(mScaling);
	}

}

void WheelModel::SetPosition(glm::vec3 position)
{
	mPosition = vec3(position);
	for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
	{
		(*it)->SetPosition(mPosition);
	}
}

void WheelModel::setRotation()
{
	float add = 0.0f;
	for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it) {
		add = add + 2.5f;
		float rot = (*it)->GetRotationAngle();
		(*it)->setRotation(vec3(0.0, 0.0, 1.0), rot + add);
	}
}

void WheelModel::setRotation(glm::vec3 axis, float degrees)
{
	for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
	{
		float rot = (*it)->GetRotationAngle();
		(*it)->SetRotation(vec3(axis), rot + degrees);
	}
}

GLuint WheelModel::wheelTexture = 0;
bool WheelModel::initializeTexture()
{
#if defined(PLATFORM_OSX)
	particleTexture = TextureLoader::LoadTexture("Textures/Particle.png");
#else
	wheelTexture = TextureLoader::LoadTexture("../Assets/Textures/tire.jpg");
#endif
	return wheelTexture != 0;
}

GLuint WheelModel::setVAO()
{
	GLuint cubeVAO = TexturedCube::makeCubeVAO();
	return cubeVAO;
}



