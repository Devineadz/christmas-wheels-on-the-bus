#pragma once

#include <vector>

#include "Model.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "Textureloader.h"

class Quad : public Model
{
public:
	Quad(int vao, int vertexCount, int shaderProgram);

	bool expired() const;
	void Update(float dt);
	void Draw(int shader);

	static GLuint makeQuadVAO(int& vertexCount);
	static bool initializeTexture();

private:
	float age, opacity;

	const glm::vec3 SCALE_I = glm::vec3(0, 0, 0);
	const glm::vec3 SCALE_F = glm::vec3(2, 2, 2);
	const float OPACITY_I = 1;
	const float OPACITY_F = 0;
	const float LIFETIME = 5; // in seconds

	static GLuint quadVAO;
	static GLuint particleTexture;
	static int textureWidth;

	static float linear(float t);
	static float quadratic(float t);
	static float root(float t);
	static float smooth(float t);
};

