//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2019 Concordia University. All rights reserved.
//

#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>

class Model
{
public:
	Model(std::string name, int vao, int vertexCount, int shaderProgram);
	~Model();

	void Update(float dt);
	void Accelerate(glm::vec3 force, float dt);
	//void Angulate(glm::vec3 torque, float dt);
	void Draw(int shaderi);

	//void Load(ci_istringstream& iss);

	glm::mat4 GetWorldMatrix() const;

	void SetPosition(glm::vec3 position);
	void SetScaling(glm::vec3 scaling);
	void SetRotation(glm::vec3 axis, float angleDegrees);
	void SetVelocity(glm::vec3 velocity);
	//void SetAngularVelocity(glm::vec3 axis, float angleDegrees);

	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetScaling() const { return scaling; }
	glm::vec3 GetRotationAxis() const { return rotationAxis; }
	float     GetRotationAngle() const { return rotationAngleInDegrees; }
	//ci_string GetName()                 { return mName; }

	//glm::vec3 GetVelocity() const		{ return mVelocity; }
	//float	  GetMass() const			{ return mMass; }

	//virtual bool ContainsPoint(glm::vec3 position) = 0;//Whether or not the given point is withing the model. For collisions.
	//virtual bool IntersectsPlane(glm::vec3 planePoint, glm::vec3 planeNormal) = 0;
	//virtual float IntersectsRay(glm::vec3 rayOrigin, glm::vec3 rayDirection) = 0; //Returns a strictly positive value if an intersection occurs
	//void BounceOffGround();

	//virtual bool isSphere() = 0; //This is not at all object-oriented, but somewhat necessary due to need for a simple double-dispatch mechanism
	static GLuint createVAO(int& vertexCount, std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs);
	//virtual bool ParseLine(const std::vector<ci_string>& token) = 0;

private:


	int vao, shader;
	int vertexCount;
	std::string name; // The model name is mainly for debugging

	glm::vec3 position;
	glm::vec3 scaling;
	glm::vec3 rotationAxis;
	float     rotationAngleInDegrees;

	glm::vec3 velocity;
	glm::vec3 angularAxis;
	float     angularVelocityInDegrees;


};
