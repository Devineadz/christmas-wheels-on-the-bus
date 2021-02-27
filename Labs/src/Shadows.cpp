#include "Shadows.h"

#include <vector>

using glm::mat4;
using std::vector;

Shadows::Shadows(int shaderi):FBO(0), depthMap(0)
{
	shader = shaderi;
	setup();
}

Shadows::~Shadows()
{
}

void Shadows::setup()
{
	glGenFramebuffers(1, &FBO);

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	int shadowLocation = glGetUniformLocation(shader, "depthMap");
	glUniform1i(shadowLocation, 1);
}

glm::mat4 Shadows::projection() const
{
	return perspective(radians(FOV), static_cast<float>(SHADOW_WIDTH) / SHADOW_HEIGHT, NEAR, SHADOWS_FAR_PLANE);
}

std::vector<glm::mat4> Shadows::views() const
{
	//Light look vectors
	glm::vec3 x(1.0f, 0.0f, 0.0f);
	glm::vec3 y(0.0f, 1.0f, 0.0f);
	glm::vec3 z(0.0f, 0.0f, 1.0f);

	//Lookat matrix
	glm::vec3 pos = glm::vec3(0.0f, 30.f, 0.0f);
	vector<glm::mat4> matrices;
	matrices.push_back(lookAt(pos, pos + x, -y));
	matrices.push_back(lookAt(pos, pos - x, -y));
	matrices.push_back(lookAt(pos, pos + y, z));
	matrices.push_back(lookAt(pos, pos - y, -z));
	matrices.push_back(lookAt(pos, pos + z, -y));
	matrices.push_back(lookAt(pos, pos - z, -y));
	return matrices;
}
