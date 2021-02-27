#pragma once

#include "TexturedCube.h"
#include "EventManager.h"
#include "Light.h"
#include "WheelModel.h"
#include "Quad.h"
#include "Bus.h"

#include <vector>
#include <list>

#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>



class Car
{
public:
	Car(int shader1);
	~Car();

	void Create();
	void Update(float dt, float rot);
	void SetOriginal();
	void setLights(int shader);
	void Draw(int shader, GLuint shadow);
	//void Draw(int shader);
	void Render(int shader);
	void SetScaling();
	void SetPosition();
	void setCarPosition(glm::vec3 position);
	glm::vec3 getPosition() const { return mPosition;  }
	glm::vec3 GetScaling() const { return mScaling; }
	void SetRotation();
	void SetAnimation(int start);

protected:

	glm::vec3 mPosition;
	glm::vec3 mScaling;
	glm::vec3 mRotationAxis;
	float     mRotationAngleInDegrees;
	int releaseState = GLFW_RELEASE;
	int releaseL = GLFW_RELEASE;

private:
	int shader;
//	TexturedCube* body = new TexturedCube(cubeVAO, 36, shader);
//	TexturedCube* bonnet = new TexturedCube(cubeVAO, 36, shader);
//	TexturedCube* roof = new TexturedCube(cubeVAO, 36, shader);
//	TexturedCube* trunk = new TexturedCube(cubeVAO, 36, shader);
//	TexturedCube* exhaust = new TexturedCube(cubeVAO, 36, shader);

	Bus* bus = new Bus(shader);

	WheelModel* wheel1 = new WheelModel(shader);
	WheelModel* wheel2 = new WheelModel(shader);
	WheelModel* wheel3 = new WheelModel(shader);
	WheelModel* wheel4 = new WheelModel(shader);

	// change for Lights
	Light* frontLight1 = new Light(shader);
	Light* frontLight2 = new Light(shader);
	Light* tailLight1 = new Light(shader);
	Light* tailLight2 = new Light(shader);

//	std::vector<TexturedCube*>carParts;
	std::vector<WheelModel*>wheels;
	std::vector<Light*>lights;
	std::list<Quad*>particles;

	float spawnTimer = 0;
	const float SPAWN_PERIOD = 0.25;
	float spinningAngle = 0.0f;
	int animStart;

	
	GLuint cubeVAO;
	GLuint setVAO();
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
};