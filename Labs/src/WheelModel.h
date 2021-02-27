#pragma once

#include "TexturedCube.h"
#include "EventManager.h"
#include "Light.h"
#include "Model.h"

#include <vector>

#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include "Textureloader.h"



class WheelModel
{
public:
	WheelModel(int shaderi);
	~WheelModel();

	void Create();
	void Update(float dt);

	void Draw(int shader);
	void Render(int shader);
	void SetScaling(glm::vec3 scaling);
	void SetPosition(glm::vec3 position);
	glm::vec3 getPosition() const { return mPosition; }
	glm::vec3 GetScaling() const { return mScaling; }
	void setRotation();
	void setRotation(glm::vec3 axis, float degrees);
	static bool initializeTexture();

protected:

	glm::vec3 mPosition;
	glm::vec3 mScaling;
	glm::vec3 mRotationAxis;
	float     mRotationAngleInDegrees;

private:

	TexturedCube* wheel1 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel2 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel3 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel4 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel5 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel6 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel7 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel8 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel9 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel10 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel11 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel12 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel13 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel14 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel15 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel16 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel17 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel18 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel19 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel20 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel21 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel22 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel23 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel24 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel25 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel26 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel27 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel28 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel29 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel30 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel31 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel32 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel33 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel34 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel35 = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* wheel36 = new TexturedCube(cubeVAO, 36, shader);
	
	GLuint setVAO();

	int shader;
	GLuint cubeVAO;
	std::vector<TexturedCube*>wheels;
	static GLuint wheelTexture;
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
};