#include "TexturedCube.h"

using namespace std;
using namespace glm;
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include "Textureloader.h"


TexturedCube::TexturedCube(int vao, int vertexCount, int shaderProgram) :Model("cube", vao, vertexCount, shaderProgram), mPosition(0.0f, 0.0f, 0.0f), mScaling(0.0f, 0.0f, 0.0f), mRotationAxis(0.0f, 0.0f, 0.0f),
	mRotationAngleInDegrees(0.0f) {
//	initializeTexture();
}

TexturedCube::~TexturedCube()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void TexturedCube::Update(float dt)
{
}

void TexturedCube::Draw(int shader)
{
	int opacityLoc = glGetUniformLocation(shader, "opacity");
	glUniform1f(opacityLoc, 0.5f);
//	glActiveTexture(GL_TEXTURE0);
//	GLuint textureLocation = glGetUniformLocation(shader, "textureSampler"); // shader program
//	glBindTexture(GL_TEXTURE_2D, particleTexture);
//	glUniform1i(textureLocation, 0);

	Model::Draw(shader);

}

//void TexturedCube::Draw(int shader)
//{
//	int vertexColorLocation = glGetUniformLocation(shader, "lightColor");
//	glUseProgram(shader);
//	glUniform3f(vertexColorLocation, 1.0f, 1.0f, 1.0f);
//
//	glBindVertexArray(vertexArrayObject);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
//
//	GLuint worldMatrixLocation = glGetUniformLocation(shader, "worldMatrix"); // shader program
//	mat4 worldMatrix = this->GetWorldMatrix();
//	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

//	glDrawArrays(GL_TRIANGLES, 0, 36);
//}

/*void TexturedCube::Render(int shader)
{
	int vertexColorLocation = glGetUniformLocation(shader, "model");
	glm::mat4 model = mat4(1.0f);
	model = translate(model, vec3(mPosition));
	model = scale(model, vec3(mScaling));
	glUseProgram(shader);
	glUniformMatrix4fv(vertexColorLocation, 1, GL_FALSE, &model[0][0]);

	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);


	glDrawArrays(GL_TRIANGLES, 0, 36);
}
*/

void TexturedCube::setPosition(glm::vec3 position)
{
	mPosition = position;
	this->SetPosition(position);
}

void TexturedCube::setRotation(glm::vec3 axis, float angleDegrees) {
	
	this->SetRotation(axis, angleDegrees);
}


void TexturedCube::setScaling(glm::vec3 scaling)
{
	mScaling = scaling;
	this->SetScaling(scaling);
}


glm::mat4 TexturedCube::GetWorldMatrix() const
{
	mat4 worldMatrix(1.0f);

	mat4 t = glm::translate(mat4(1.0f), mPosition);
	mat4 r = glm::rotate(mat4(1.0f), glm::radians(mRotationAngleInDegrees), mRotationAxis);
	mat4 s = glm::scale(mat4(1.0f), mScaling);

	worldMatrix = t * r * s;

	return worldMatrix;
}

glm::vec3 TexturedCube::getPosition() const
{
	glm::vec3 pos = this->GetPosition();
	return pos;
}

GLuint TexturedCube::makeCubeVAO()
{
	vector<vec3> positions{ vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f,-0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f),
							vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f,-0.5f), 

							vec3(0.5f, 0.5f,-0.5f), vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f, 0.5f,-0.5f),
							vec3(0.5f, 0.5f,-0.5f), vec3(0.5f,-0.5f,-0.5f), vec3(-0.5f,-0.5f,-0.5f),

							vec3(0.5f,-0.5f, 0.5f), vec3(-0.5f,-0.5f,-0.5f), vec3(0.5f,-0.5f,-0.5f),
							vec3(0.5f,-0.5f, 0.5f), vec3(-0.5f,-0.5f, 0.5f), vec3(-0.5f,-0.5f,-0.5f),

							vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f,-0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f),
							vec3(0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f),

							vec3(0.5f, 0.5f, 0.5f), vec3(0.5f,-0.5f,-0.5f), vec3(0.5f, 0.5f,-0.5f),
							vec3(0.5f,-0.5f,-0.5f), vec3(0.5f, 0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f),

							vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f,-0.5f), vec3(-0.5f, 0.5f,-0.5f),
							vec3(0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f,-0.5f), vec3(-0.5f, 0.5f, 0.5f)
	};

	vector<vec3> normals{	vec3(-1.0f, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f),
							vec3(-1.0f, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f),

							vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, -1.0f),
							vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, -1.0f),

							vec3(0.0f,-1.0f, 0.0f), vec3(0.0f,-1.0f, 0.0f), vec3(0.0f,-1.0f, 0.0f),
							vec3(0.0f,-1.0f, 0.0f), vec3(0.0f,-1.0f, 0.0f), vec3(0.0f,-1.0f, 0.0f),

							vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f),
							vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f),

							vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f),
							vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f),

							vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f),
							vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)
	
	};

	vector<vec2> uvs{		vec2(0.0f, 0.0f), vec2(0.0f, 1.0f), vec2(1.0f, 1.0f),
							vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), vec2(1.0f, 0.0f),

							vec2(1.0f, 1.0f), vec2(0.0f, 0.0f), vec2(0.0f, 1.0f),
							vec2(1.0f, 1.0f), vec2(1.0f, 0.0f), vec2(0.0f, 0.0f),

							vec2(1.0f, 1.0f), vec2(0.0f, 0.0f), vec2(1.0f, 0.0f),
							vec2(1.0f, 1.0f), vec2(0.0f, 1.0f), vec2(0.0f, 0.0f),

							vec2(0.0f, 1.0f), vec2(0.0f, 0.0f), vec2(1.0f, 0.0f),
							vec2(1.0f, 1.0f), vec2(0.0f, 1.0f), vec2(1.0f, 0.0f),

							vec2(1.0f, 1.0f), vec2(0.0f, 0.0f), vec2(1.0f, 0.0f),
							vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), vec2(0.0f, 1.0f),

							vec2(1.0f, 1.0f), vec2(1.0f, 0.0f), vec2(0.0f, 0.0f),
							vec2(1.0f, 1.0f), vec2(0.0f, 0.0f), vec2(0.0f, 1.0f),
	
	};

	int vertexCount = 36;
	return Model::createVAO(vertexCount, positions, normals, uvs);


}

GLuint TexturedCube::particleTexture=0;
bool TexturedCube::initializeTexture()
{
#if defined(PLATFORM_OSX)
particleTexture = TextureLoader::LoadTexture("Textures/Particle.png");
#else
	particleTexture = TextureLoader::LoadTexture("../Assets/Textures/Lamp.png");
#endif

	return particleTexture != 0;
}

