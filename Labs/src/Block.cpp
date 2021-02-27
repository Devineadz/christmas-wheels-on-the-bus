#include "Block.h"

#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

using namespace std;
using namespace glm;

Block::Block(int shaderi)
	: mPosition(0.0f, 0.0f, 0.0f), mScaling(0.0f, 0.0f, 0.0f), mRotationAxis(0.0f, 0.0f, 0.0f),
	mRotationAngleInDegrees(0.0f)
{
	shader = shaderi;
	cubeVAO = setVAO();
	block = new TexturedCube(cubeVAO, 36, shader);
	initializeTexture();
}

Block::~Block()
{
	delete block;
}

void Block::Update(float dt)
{
}

void Block::Draw(int shader, GLuint shadow)
{
	glActiveTexture(GL_TEXTURE0);
	GLuint textureLocation = glGetUniformLocation(shader, "textureSampler"); // shader program
	glBindTexture(GL_TEXTURE_2D, blockTexture);

	glActiveTexture(GL_TEXTURE1);
	GLuint shadowLocation = glGetUniformLocation(shader, "shadowMap");
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadow);

	block->Draw(shader);
}

void Block::setPosition(glm::vec3 position)
{
	mPosition = position;
	block->SetPosition(mPosition);
}

void Block::setScaling(glm::vec3 scaling)
{
	mScaling = scaling;
	block->SetScaling(scaling);
}

void Block::setRotation(glm::vec3 axis, float angleDegrees)
{
	mRotationAngleInDegrees = angleDegrees;
	mRotationAxis = axis;
}

GLuint Block::blockTexture = 0;

bool Block::initializeTexture()
{
#if defined(PLATFORM_OSX)
	particleTexture = TextureLoader::LoadTexture("Textures/Particle.png");
#else
	blockTexture = TextureLoader::LoadTexture("../Assets/Textures/snow.png");
#endif
	return blockTexture != 0;
}

GLuint Block::setVAO()
{
	GLuint cubeVAO = TexturedCube::makeCubeVAO();
	return cubeVAO;
}
