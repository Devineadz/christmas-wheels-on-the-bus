#pragma once

#include <vector>
#include <FreeImageIO.h>
#include "EventManager.h"
#include<iostream> 
#include<string> // for string class 
using namespace std;

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <string>
#include "Model.h"



class TexturedCube :public Model
{
public:
	TexturedCube(int vao, int vertexCount, int shaderProgram);
	~TexturedCube();

	void Update(float dt);
	void Draw(int shader);
//	void Draw(int shader);
	//void Render(int shader);
	void setPosition(glm::vec3 position);
	void setScaling(glm::vec3 scaling);
	void setRotation(glm::vec3 axis, float angleDegrees);
	glm::mat4 GetWorldMatrix() const;
	glm::vec3 getPosition() const;
	glm::vec3 getScaling() const { return mScaling; }
	glm::vec3 getRotationAxis() const { return mRotationAxis; }
	float     getRotationAngle() const { return mRotationAngleInDegrees; }
	static GLuint makeCubeVAO();
	static bool initializeTexture();
	

protected:
	
	glm::vec3 mPosition;
	glm::vec3 mScaling;
	glm::vec3 mRotationAxis;
	float     mRotationAngleInDegrees;

private:
	unsigned int vertexBufferObject;
	unsigned int vertexArrayObject;
	static GLuint particleTexture;

};
