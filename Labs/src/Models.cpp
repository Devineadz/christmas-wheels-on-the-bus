#include "Models.h"

Models::Models(int vao, int vertexCount, int shaderProgram) :Model("models", vao, vertexCount, shaderProgram)
{
	initializeTexture();
}

void Models::Update(float dt)
{
}

void Models::Draw(int shader)
{
	glActiveTexture(GL_TEXTURE0);
	GLuint textureLocation = glGetUniformLocation(shader, "textureSampler"); // shader program
	glBindTexture(GL_TEXTURE_2D, modelTexture);
	glUniform1i(textureLocation, 0);

	Model::Draw(shader);
}

GLuint Models::makeModelsVAO(std::string path, int& vertexCount)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;

	//read the vertex data from the model's OBJ file
	loadOBJ(path.c_str(), vertices, normals, UVs);


	return Model::createVAO(vertexCount, vertices, normals, UVs);

}

GLuint Models::modelTexture = 0;
bool Models::initializeTexture()
{
#if defined(PLATFORM_OSX)
	particleTexture = TextureLoader::LoadTexture("Textures/Particle.png");
#else
	modelTexture = TextureLoader::LoadTexture("../Assets/Textures/christmasdeco.png");
#endif
	return modelTexture != 0;
}
