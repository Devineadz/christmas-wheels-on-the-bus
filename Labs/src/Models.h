#pragma once

#include <vector>

#include "Model.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "OBJloader.h" 
#include "Textureloader.h"



class Models : public Model
{
public:
	Models(int vao, int vertexCount, int shaderProgram);


	void Update(float dt);
	void Draw(int shader);

	static GLuint makeModelsVAO(std::string path, int& vertexCount);
	static bool initializeTexture();

private:
	

	static GLuint modelsVAO;
	static GLuint modelTexture;
	static int textureWidth;
	std::string path;
};