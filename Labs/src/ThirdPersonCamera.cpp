#include "ThirdPersonCamera.h"

#include "EventManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include <GLFW/glfw3.h>
#include <algorithm>

using namespace glm;

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position) : Camera(), mPosition(position), mLookAt(0.0f, 0.0f, -1.0f), mHorizontalAngle(90.0f), mVerticalAngle(0.0f), mSpeed(5.0f), mAngularSpeed(2.5f)
{
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::Update(float dt)
{
	// Clamp vertical angle to [-85, 85] degrees
	mVerticalAngle = std::max(-85.0f, std::min(85.0f, mVerticalAngle));
	if (mHorizontalAngle > 360)
	{
		mHorizontalAngle -= 360;
	}
	else if (mHorizontalAngle < -360)
	{
		mHorizontalAngle += 360;
	}

	float theta = radians(mHorizontalAngle);
	float phi = radians(mVerticalAngle);

	mLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));

	vec3 sideVector = glm::cross(mLookAt, vec3(0.0f, 1.0f, 0.0f));
	glm::normalize(sideVector);
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
	return glm::lookAt(mPosition, mPosition + mLookAt, vec3(0.0f, 1.0f, 0.0f));
}

void ThirdPersonCamera::SetPosition(glm::vec3 position)
{
	mPosition = position;
}

glm::vec3 ThirdPersonCamera::GetLookAt() const
{
	glm::mat4 viewMatrix = GetViewMatrix();

	glm::vec3 lookAt(viewMatrix[2]);
	return glm::normalize(lookAt);
}
