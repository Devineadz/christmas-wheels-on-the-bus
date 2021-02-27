#pragma once

#include "TexturedCube.h"
#include "EventManager.h"

#include <vector>

#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include "Textureloader.h"



class Bus
{
public:
	Bus(int shaderi);
	~Bus();

	void Create();
	void Update(float dt);
	void SetOriginal();
	void Draw(int shader, GLuint shadow);
	void Render(int shader);
	void SetScaling(glm::vec3 scaling);
	void SetPosition(glm::vec3 position);
	glm::vec3 getPosition() const { return mPosition; }
	glm::vec3 getExhaustpos();
	glm::vec3 GetScaling() const { return mScaling; }
	void SetRotation(glm::vec3 axis, float angleDegrees);
	static bool initializeTexture();

protected:

	glm::vec3 mPosition;
	glm::vec3 mScaling;
	glm::vec3 mRotationAxis;
	float     mRotationAngleInDegrees;

private:
	TexturedCube* body = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* bonnet = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* roof = new TexturedCube(cubeVAO, 36, shader);
	TexturedCube* exhaust = new TexturedCube(cubeVAO, 36, shader);

	GLuint setVAO();

	int shader;
	GLuint cubeVAO;


	std::vector<TexturedCube*>carParts;
	std::vector<TexturedCube*>wheels;
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};

	static GLuint busTexture;
};
