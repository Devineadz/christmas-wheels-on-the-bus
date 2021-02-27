#pragma once

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include "TexturedCube.h"
#include "Textureloader.h"

class Block
{
public:
	Block(int shaderi);
	~Block();

	void Update(float dt);
	void Draw(int shader, GLuint shadow);
	void setPosition(glm::vec3 position);
	void setScaling(glm::vec3 scaling);
	void setRotation(glm::vec3 axis, float angleDegrees);
	glm::vec3 GetPosition() const { return mPosition; }
	glm::vec3 GetScaling() const { return mScaling; }
	glm::vec3 GetRotationAxis() const { return mRotationAxis; }
	float     GetRotationAngle() const { return mRotationAngleInDegrees; }
	static bool initializeTexture();

protected:
	glm::vec3 mPosition;
	glm::vec3 mScaling;
	glm::vec3 mRotationAxis;
	float     mRotationAngleInDegrees;

private:
	TexturedCube* block = new TexturedCube(cubeVAO, 36, shader);

	GLuint setVAO();

	int shader;
	GLuint cubeVAO;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
	unsigned int vBO;
	unsigned int vAO;

	static GLuint blockTexture;
};