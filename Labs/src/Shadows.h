#pragma once

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#define SHADOW_WIDTH 2048
#define SHADOW_HEIGHT 2048
#define SHADOWS_FAR_PLANE 25.0f

#define FOV 90.0f
#define NEAR 1.0f

using glm::perspective;
using glm::radians;

class Shadows {
public:
	Shadows(int shaderi);
	~Shadows();
	void setup();
	GLuint getFBO() const { return FBO; }
	GLuint getdepthMap() const { return depthMap; }
	glm::mat4 projection() const;
	std::vector<glm::mat4> views() const;
private: 
	GLuint FBO;
	GLuint shader;
	GLuint depthMap;
};