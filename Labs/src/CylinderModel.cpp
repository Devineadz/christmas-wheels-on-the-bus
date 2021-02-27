/*
#include "CylinderModel.h"
#include "Renderer.h"
#include <math.h>

using namespace glm;


CylinderModel::CylinderModel(glm::vec3 size) : Model()
{
	float fS = 1 * 0.5f;
	double pi = 3.1415926535897;
	float theta = 2.0 * pi;

	Vertex vertexBuffer[] = {  // position,                normal,                  color
								{ vec3(0.0f, fS, 0.0), vec3(0.0f, fS, 0.0), vec3(1.0f, 0.0f, 0.0f) }, //layer 1
								{ vec3(fS * cos(0 * theta), fS, fS * sin(0 * theta)), vec3(fS * cos(0 * theta), fS, fS * sin(0 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(1 * theta), fS, fS * sin(1 * theta)), vec3(fS * cos(1 * theta), fS, fS * sin(1 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(1 * theta), -fS, fS* sin(1 * theta)), vec3(fS * cos(1 * theta), -fS, fS * sin(1 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(0 * theta), -fS, fS * sin(0 * theta)), vec3(fS * cos(0 * theta), -fS, fS * sin(0 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(0.0, -fS, 0.0), vec3(0.0, -fS, 0.0), vec3(1.0f, 0.0f, 0.0f) },

								{ vec3(0.0f, fS, 0.0), vec3(0.0f, fS, 0.0), vec3(1.0f, 0.0f, 0.0f) }, //layer 2
								{ vec3(fS * cos(1 * theta), fS, fS * sin(1 * theta)), vec3(fS * cos(1 * theta), fS, fS * sin(1 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(2 * theta), fS, fS * sin(2 * theta)), vec3(fS * cos(2 * theta), fS, fS * sin(2 * theta)), vec3(1.0f, 0.0f, 0.0f)},
								{ vec3(fS * cos(2 * theta), -fS, fS * sin(2 * theta)), vec3(fS * cos(2 * theta), -fS, fS * sin(2 * theta)), vec3(1.0f, 0.0f, 0.0f)},
								{ vec3(fS * cos(1 * theta), -fS, fS * sin(1 * theta)), vec3(fS * cos(1 * theta), -fS, fS * sin(1 * theta)), vec3(1.0f, 0.0f, 0.0f)},
								{ vec3(0.0, -fS, 0.0), vec3(0.0, -fS, 0.0), vec3(1.0f, 0.0f, 0.0f) },

								{ vec3(0.0f, fS, 0.0), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) }, //layer 3
								{ vec3(fS * cos(2 * theta), fS, fS * sin(2 * theta)), vec3(fS * cos(2 * theta), fS, fS * sin(2 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(3 * theta), fS, fS * sin(3 * theta)), vec3(fS * cos(3 * theta), fS, fS * sin(3 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(3 * theta), -fS,fS * sin(3 * theta)), vec3(fS * cos(3 * theta), -fS,fS * sin(3 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(2 * theta), -fS, fS * sin(2 * theta)), vec3(fS * cos(2 * theta), -fS, fS * sin(2 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(0.0, -fS, 0.0), vec3(0.0, -fS, 0.0), vec3(1.0f, 0.0f, 0.0f) },

								{ vec3(0.0f, fS, 0.0), vec3(0.0f, fS, 0.0), vec3(1.0f, 0.0f, 0.0f) }, //layer 4
								{ vec3(fS * cos(3 * theta), fS, fS * sin(3 * theta)), vec3(fS * cos(3 * theta), fS, fS * sin(3 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(4 * theta), fS, fS * sin(4 * theta)), vec3(fS * cos(4 * theta), fS, fS * sin(4 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(4 * theta), -fS, fS * sin(4 * theta)), vec3(fS * cos(4 * theta), -fS, fS * sin(4 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(3 * theta), -fS, fS * sin(3 * theta)), vec3(fS * cos(3 * theta), -fS, fS * sin(3 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(0.0, -fS, 0.0), vec3(0.0, -fS, 0.0), vec3(1.0f, 0.0f, 0.0f) },

								{ vec3(0.0f, fS, 0.0), vec3(0.0f, fS, 0.0), vec3(1.0f, 0.0f, 0.0f) }, //layer 4
								{ vec3(fS * cos(4 * theta), fS, fS * sin(4 * theta)), vec3(fS * cos(4 * theta), fS, fS * sin(4 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(5 * theta), fS, fS * sin(5 * theta)), vec3(fS * cos(5 * theta), fS, fS * sin(5 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(5 * theta), -fS, fS * sin(5 * theta)), vec3(fS * cos(5 * theta), -fS, fS * sin(5 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(4 * theta), -fS, fS * sin(4 * theta)), vec3(fS * cos(4 * theta), -fS, fS * sin(4 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(0.0, -fS, 0.0), vec3(0.0, -fS, 0.0), vec3(1.0f, 0.0f, 0.0f) },

								{ vec3(0.0f, fS, 0.0), vec3(0.0f, fS, 0.0), vec3(1.0f, 0.0f, 0.0f) }, //layer 5
								{ vec3(fS * cos(5 * theta), fS, fS * sin(5 * theta)), vec3(fS * cos(5 * theta), fS, fS * sin(5 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(6 * theta), fS, fS * sin(6 * theta)), vec3(fS * cos(6 * theta), fS, fS * sin(6 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(6 * theta), -fS, fS * sin(6 * theta)), vec3(fS * cos(6 * theta), -fS, fS * sin(6 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(fS * cos(5 * theta), -fS, fS * sin(5 * theta)), vec3(fS * cos(5 * theta), -fS, fS * sin(5 * theta)), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(0.0, -fS, 0.0), vec3(0.0, -fS, 0.0), vec3(1.0f, 0.0f, 0.0f) }
					};

	// Create a vertex array
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);



	// 1st attribute buffer : vertex Positions
	glVertexAttribPointer(0,                // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                // size
		GL_FLOAT,        // type
		GL_FALSE,        // normalized?
		sizeof(Vertex), // stride
		(void*)0        // array buffer offset
	);
	glEnableVertexAttribArray(0);

	// 2nd attribute buffer : vertex normal
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
	);
	glEnableVertexAttribArray(1);


	// 3rd attribute buffer : vertex color
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(2 * sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
	);
	glEnableVertexAttribArray(2);
}

CylinderModel::~CylinderModel()
{
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
}

void CylinderModel::Update(float dt)
{
	Model::Update(dt);
}

void CylinderModel::Draw()
{
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
bool CylinderModel::ParseLine(const std::vector<ci_string>& token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}
*/