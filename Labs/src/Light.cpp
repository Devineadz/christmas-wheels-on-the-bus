#include "Light.h"

using namespace glm;

Light::Light(int shaderi)
	: mPosition(0.0f, 0.0f, 0.0f), mScaling(1.0f, 1.0f, 1.0f), mRotationAxis(0.0f, 1.0f, 0.0f),
	mRotationAngleInDegrees(0.0f)
{
	shader = shaderi;
	cubeVAO = setVAO();
	light = new TexturedCube(cubeVAO, 36, shader);
	initializeTexture();
}

Light::~Light()
{
	delete light;
}

void Light::Update(float dt)
{
}

void Light::LightDraw(int shader)
{
	glActiveTexture(GL_TEXTURE0);
	GLuint textureLocation = glGetUniformLocation(shader, "textureSampler"); // shader program
	glBindTexture(GL_TEXTURE_2D, lightTexture);
	glUniform1i(textureLocation, 0);

	light->Draw(shader);
}

void Light::setPosition(glm::vec3 position)
{
	mPosition = position;
	light->SetPosition(mPosition);
}

void Light::setScaling(glm::vec3 scaling)
{
	mScaling = scaling;
	light->SetScaling(scaling);
}

void Light::setRotation(glm::vec3 axis, float angleDegrees)
{
	mRotationAngleInDegrees = angleDegrees;
	mRotationAxis = axis;
}

glm::mat4 Light::GetWorldMatrix() const
{
	mat4 worldMatrix(1.0f);

	mat4 t = glm::translate(mat4(1.0f), mPosition);
	mat4 r = glm::rotate(mat4(1.0f), glm::radians(mRotationAngleInDegrees), mRotationAxis);
	mat4 s = glm::scale(mat4(1.0f), mScaling);

	worldMatrix = t * r * s;

	return worldMatrix;
}

GLuint Light::lightTexture = 0;
bool Light::initializeTexture()
{
#if defined(PLATFORM_OSX)
	particleTexture = TextureLoader::LoadTexture("Textures/Particle.png");
#else
	lightTexture = TextureLoader::LoadTexture("../Assets/Textures/lamp.png");
#endif
	return lightTexture != 0;
}

GLuint Light::setVAO()
{
	GLuint cubeVAO = TexturedCube::makeCubeVAO();
	return cubeVAO;
}
