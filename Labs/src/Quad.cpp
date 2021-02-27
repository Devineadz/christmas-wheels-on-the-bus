#include "Quad.h"

#include<vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Textureloader.h"


using namespace std;
using namespace glm;

Quad::Quad(int vao, int vertexCount, int shaderProgram) :Model("quad", vao, vertexCount, shaderProgram), age(0), opacity(0.5f) {
	initializeTexture();
}

//TODO 2 - Add an expiration condition
bool Quad::expired() const {

	if (age >= LIFETIME) {
		return true;
	}
	else
		return false;
}



void Quad::Update(float dt) {
	Model::Update(dt);
	age += 0.5*dt;

	float interpolationParameter = age / LIFETIME;

	float scalingParam = linear(interpolationParameter);
	float opacityParam = linear(interpolationParameter);

	opacity = OPACITY_I * (1 - opacityParam) + OPACITY_F * opacityParam;
	SetScaling(SCALE_I * (1 - scalingParam) + SCALE_F * scalingParam);

}

void Quad::Draw(int shader) {
	
	glActiveTexture(GL_TEXTURE0);
	GLuint textureLocation = glGetUniformLocation(shader, "textureSampler"); // shader program
	glBindTexture(GL_TEXTURE_2D, particleTexture);
	glUniform1i(textureLocation, 0);

	GLuint opacityLocation = glGetUniformLocation(shader, "opacity");
	glUniform1f(opacityLocation, opacity);


	Model::Draw(shader);
}

//Static stuff
GLuint Quad::quadVAO = 0;

GLuint Quad::makeQuadVAO(int& vertexCount) {
	if (quadVAO != 0) {
		return quadVAO;
	}
	else {
		vector<vec3> positions{ vec3(-.5,.5,0), vec3(-.5,-.5,0), vec3(.5,.5,0),
							   vec3(.5,.5,0),  vec3(-.5,-.5,0), vec3(.5,-.5,0) };

		vector<vec3> normals{ 6, vec3(0,0,1) };
		vector<vec3> colors(6, vec3(1, 0, 1));

		vector<vec2> uvs{ vec2(0,1), vec2(0,0), vec2(1,1),
						 vec2(1,1), vec2(0,0), vec2(1,0) };



		return Model::createVAO(vertexCount, positions, normals, uvs);
	}
}

GLuint Quad::particleTexture = 0;
bool Quad::initializeTexture()
{
#if defined(PLATFORM_OSX)
	particleTexture = TextureLoader::LoadTexture("Textures/Particle.png");
#else
	particleTexture = TextureLoader::LoadTexture("../Assets/Textures/cement.jpg");
#endif
	return particleTexture != 0;
}

float Quad::linear(float t) { return t; }
float Quad::quadratic(float t) { return t * t; }
float Quad::root(float t) { return sqrt(t); }
float Quad::smooth(float t) {
	float theta = pi<float>() * (1 + t);
	return (glm::cos(theta) + 1) / 2;
}