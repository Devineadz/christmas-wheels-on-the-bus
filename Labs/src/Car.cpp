#include "Car.h"

#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <string>
#include<iostream>

using namespace std;
using namespace glm;

Car::Car(int shader1)
	: mPosition(0.0f, 0.0f, 0.0f), mScaling(0.0f, 0.0f, 0.0f), mRotationAxis(0.0f, 0.0f, 0.0f),
	mRotationAngleInDegrees(0.0f)
{
	shader = shader1;
	Create();
	SetPosition();
	SetScaling();
	animStart = 0;
}

Car::~Car()
{
	delete bus;

	for (vector<WheelModel*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
	{
		delete* it;
	}
	wheels.clear();
	for (vector<Light*>::iterator it = lights.begin(); it < lights.end(); ++it) 
	{
		delete* it;
	}
	lights.clear();
	
}

// Creates parts of the car and puts them in a car object vector
void Car::Create()
{
	//cubeVAO = setVAO();
	// Body
	//body = new TexturedCube(cubeVAO, 36, shader);
	//carParts.push_back(body);

	//cubeVAO = setVAO();
	// Bonnet
	//bonnet = new TexturedCube(cubeVAO, 36, shader);
	//carParts.push_back(bonnet);

	// Roof
	//cubeVAO = setVAO();
	//roof = new TexturedCube(cubeVAO, 36, shader);
	//carParts.push_back(roof);

	// Exhaust
	//cubeVAO = setVAO();
	//exhaust = new TexturedCube(cubeVAO, 36, shader);
	//carParts.push_back(exhaust);

	bus = new Bus(shader);

	// Wheels
	
	wheel1 = new WheelModel(shader);
	wheels.push_back(wheel1);

	
	wheel2 = new WheelModel(shader);
	wheels.push_back(wheel2);

	
	wheel3 = new WheelModel(shader);
	wheels.push_back(wheel3);


	wheel4 = new WheelModel(shader);
	wheels.push_back(wheel4);

	// LIghts
	
	frontLight1 = new Light(shader);
	lights.push_back(frontLight1);

	
	frontLight2 = new Light(shader);
	lights.push_back(frontLight2);

	tailLight1 = new Light(shader);
	lights.push_back(tailLight1);

	
	tailLight2 = new Light(shader);
	lights.push_back(tailLight2);
}

void Car::Update(float dt, float rot)
{
	int newState = glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE);

	// Moves the car to a random position
	if (newState == GLFW_RELEASE && releaseState == GLFW_PRESS) 
	{
		SetOriginal();
		int randX = rand() % 100 - 50;
		int randZ = rand() % 100 - 50;
		
		mPosition = vec3(mPosition.x + randX, mPosition.y, mPosition.z + randZ);
		SetPosition();

		releaseState = GLFW_RELEASE;
		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x+(float)randX, move.y, move.z+(float)randZ));
		}
		for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x +(float)randX, move.y, move.z+(float)randZ));
		}*/
	}
	releaseState = newState;

	int newState2 = glfwGetKey(EventManager::GetWindow(), GLFW_KEY_L);
	if (newState2 == GLFW_RELEASE && releaseState == GLFW_PRESS) {

	}
	releaseL = newState2;


	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_H) == GLFW_PRESS) // TODO make so that only one transition happens!
	{
		SetOriginal();
		SetPosition();
		
	}

	/*//Moves cars upwards
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		mPosition = vec3(mPosition.x, mPosition.y + 0.2f, mPosition.z);
		SetPosition();
		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x, move.y + 0.2f, move.z));
		}
		for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x, move.y+0.2f, move.z));
		}
	}
	*/
	// Makes the car go downwards
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_Y) == GLFW_PRESS)
	{
		mPosition = vec3(mPosition.x, mPosition.y - 0.2f, mPosition.z);
		SetPosition();
		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x, move.y-0.2f, move.z));
		}
		for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x, move.y-0.2f, move.z));

		}*/

	}

	/* Turns the car to the right
	// TODO FIX
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		mPosition = vec3(mPosition.x, mPosition.y + 0.2f, mPosition.z-0.2f);
		SetPosition();
		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x, move.y, move.z-0.2f));
		}
		for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x, move.y, move.z-0.2f));
		}
	}

	// Moves car backwards and rotates wheels
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		mPosition = vec3(mPosition.x-0.2f, mPosition.y, mPosition.z);
		SetPosition();

		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x, move.y, move.z+0.2f));
		}
		for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x, move.y, move.z+0.2f));
		}
	}
	*/
	//Moves cars forward and rotates wheels
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_F) == GLFW_PRESS)
	{
		mPosition = vec3(mPosition.x + 0.2f, mPosition.y, mPosition.z);
		SetPosition();

		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x+0.2f, move.y, move.z));
		}*/
		for (vector<WheelModel*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			(*it)->setRotation(vec3(0.0, 0.0, 1.0), -45.0f);
		}
	}

	if (animStart == 1) {
		mPosition = vec3(mPosition.x + 0.50f, mPosition.y, mPosition.z);
		SetPosition();
		for (vector<WheelModel*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			(*it)->setRotation(vec3(0.0, 0.0, 1.0), -22.5f);
		}
	}

	// Turns the car left
	// TODO FIX 
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_N) == GLFW_PRESS)
	{
		mPosition = vec3(mPosition.x, mPosition.y, mPosition.z+0.2f);
		SetPosition();

		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x + 0.2, move.y, move.z- cos(dt)));
		}
		for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x+0.2, move.y, move.z - cos(dt)));
			(*it)->SetRotation(vec3(0.0, 1.0, 0.0), 45); // TODO Draw call?
		}*/
	
	}

	// Turns the car to the right
	// TODO FIX
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_B) == GLFW_PRESS)
	{
		mPosition = vec3(mPosition.x + 0.2f, mPosition.y, mPosition.z +0.2f);
		SetPosition();

		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x + 0.2f, move.y, move.z + 0.2f));
		}
		for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x, move.y, move.z + 0.2f));
		}*/
	}

	// Moves car backwards and rotates wheels
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_V) == GLFW_PRESS)
	{
		mPosition = vec3(mPosition.x - 0.2f, mPosition.y, mPosition.z);
		SetPosition();
		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move.x - 0.2f, move.y, move.z));
		}*/
		for (vector<WheelModel*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			(*it)->setRotation(vec3(0.0, 0.0, 1.0), 45);
		}
	}

	// Size up the car bigger
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_U) == GLFW_PRESS)
	{
		mPosition = vec3(mPosition + 0.001f);
		mScaling = vec3(mScaling + 0.002f);
		SetPosition();
		SetScaling();
		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 scaling = vec3( (*it)->GetScaling());
			(*it)->SetScaling(vec3(scaling+0.002f));
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move+0.001f));
		}
		for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			glm::vec3 scaling = vec3((*it)->GetScaling());
		
			(*it)->SetScaling(vec3(scaling+0.002f));
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move + 0.001f));
			
		}*/

	}

	// Size up the car smaller
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_O) == GLFW_PRESS)
	{
		mPosition = vec3(mPosition - 0.001f);
		mScaling = vec3(mScaling - 0.002f);
		SetPosition();
		SetScaling();
		/*for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
		{
			glm::vec3 scaling = vec3((*it)->GetScaling());
			(*it)->SetScaling(vec3(scaling - 0.002f));
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move - 0.001f));
		}
		for (vector<TexturedCube*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
		{
			glm::vec3 scaling = vec3((*it)->GetScaling());

			(*it)->SetScaling(vec3(scaling - 0.002f));
			glm::vec3 move = (*it)->GetPosition();
			(*it)->SetPosition(vec3(move - 0.001f));

		}*/

	}
	

	spawnTimer += dt;
	if (spawnTimer > SPAWN_PERIOD) {
		int vertexCount;
		int vao = Quad::makeQuadVAO(vertexCount);
		Quad* model = new Quad(vao, vertexCount, shader);
		//TODO 1 - Give the particles some motion when created
		float angle = EventManager::GetRandomFloat(0, 360);
		vec4 randomSidewaysVelocity(0.5, 2, 0, 0);
		randomSidewaysVelocity = glm::rotate(mat4(1.0f), glm::radians(angle), vec3(0, 1, 0)) * randomSidewaysVelocity;
		model->SetVelocity(vec3(randomSidewaysVelocity));
		model->SetScaling(vec3(0.5f, 0.5f, 0.5f));
		vec3 exPos = bus->getExhaustpos();
		model->SetPosition(exPos);

		particles.push_back(model);		//spawn
		spawnTimer -= 0.25;
	}

	vec3 originalAxis(0, 0, 1);
	//vec3 cameraLookAt(-GetCurrentCamera()->GetLookAt());
	//cameraLookAt.y = 0; //project onto xz plane
	//cameraLookAt.x *= -1;
	//cameraLookAt = normalize(cameraLookAt);

	//vec3 billboardRotationAxis(vec3(0,1,0));

	//float billboardRotation = glm::acos(-1 * dot(originalAxis, cameraLookAt)) * 360 / (2 * pi<float>());
	//
	//if (cameraLookAt.x > 0) {
	//	billboardRotation = 360 - billboardRotation;
	//}

	list<Quad*>::iterator it = particles.begin();
	while (it != particles.end())
	{
		vec3 billboardRotationAxis=(vec3(0.0f, 1.0f, 0.0f));
		(*it)->SetRotation(billboardRotationAxis, rot); // TODO 4 - Set the rotation
		(*it)->Update(dt);

		if ((*it)->expired()) {
			it = particles.erase(it);
		}
		else {
			++it;
		}
	}

	
}

// Set Car to the original position
void Car::SetOriginal()
{
	mPosition = vec3(0.0f, 0.0f, 0.0f);
}


void Car::Draw(int shader, GLuint shadow)
{
	
	setLights(shader);
	
	// Draw car parts with textures
//	for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
//	{
		
//		(*it)->Draw(shader, textureid);
//	}
	bus->Draw(shader, shadow);
	for (vector<WheelModel*>::iterator it = wheels.begin(); it < wheels.end(); ++it)
	{
		
		
	
		(*it)->Draw(shader);
	}
	for (vector<Light*>::iterator it = lights.begin(); it < lights.end(); ++it)
	{
		
		

		(*it)->LightDraw(shader);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_DEPTH_TEST);
	for (list<Quad*>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		(*it)->Draw(shader);
	}
	// Re-enable depth test
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	
}

//void Car::Draw(int shader)
//{
	// Draw car parts without textures
//	for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
//	{
		
		
//		(*it)->Draw(shader);
//	}
//	for (vector<TexturedCube*>::iterator it = lights.begin(); it < lights.end(); ++it)
//	{
//		(*it)->Draw(shader);
//	}
//}

void Car::Render(int shader)
{
//	for (vector<TexturedCube*>::iterator it = carParts.begin(); it < carParts.end(); ++it)
//	{
		
		
//	}
	for (vector<Light*>::iterator it = lights.begin(); it < lights.end(); ++it)
	{
		
	}
}


void Car::SetPosition()
{
	// Body
//	body->SetPosition(vec3(mPosition.x + 0.0f, mPosition.y + 1.0f, mPosition.z + 0.0f));
	
	// Bonnet
//	bonnet->SetPosition(vec3(mPosition.x + 2.4f, mPosition.y + 0.8f, mPosition.z + 0.0f));

	// Roof
//	roof->SetPosition(vec3(mPosition.x + 0.0f, mPosition.y + 1.5f, mPosition.z + 0.0f));

	//Exhaust 
//	exhaust->SetPosition(vec3(mPosition.x - 2.5f, mPosition.y + 0.4f, mPosition.z + 0.0f));

	bus->SetPosition(mPosition);

	// Wheels
	// Back
	wheel1->SetPosition(vec3(mPosition.x - 1.5f, mPosition.y + 0.5f, mPosition.z - 0.5f));

	wheel2->SetPosition(vec3(mPosition.x - 1.5f, mPosition.y + 0.5f, mPosition.z + 0.5f));

	// Front
	wheel3->SetPosition(vec3(mPosition.x + 2.0f, mPosition.y + 0.5f, mPosition.z - 0.5f));

	wheel4->SetPosition(vec3(mPosition.x + 2.0f, mPosition.y + 0.5f, mPosition.z + 0.5f));

	// Lights
	frontLight1->setPosition(vec3(mPosition.x + 2.9f, mPosition.y + 0.8f, mPosition.z - 0.3f));

	frontLight2->setPosition(vec3(mPosition.x + 2.9f, mPosition.y + 0.8f, mPosition.z + 0.3f));

	tailLight1->setPosition(vec3(mPosition.x - 2.5f, mPosition.y + 0.8f, mPosition.z - 0.3f));

	tailLight2->setPosition(vec3(mPosition.x - 2.5f, mPosition.y + 0.8f, mPosition.z + 0.3f));
}

void Car::setCarPosition(glm::vec3 position)
{

	mPosition = position;
	SetPosition();
}

void Car::SetScaling()
{
//	body->SetScaling(vec3(mScaling.x + 5.0f, mScaling.y + 1.5f, mScaling.z + 1.0f));

//	bonnet->SetScaling(vec3(mScaling.x + 1.0f, mScaling.y + 0.8f, mScaling.z + 0.95f));

//	roof->SetScaling(vec3(mScaling.x + 4.9f, mScaling.y + 0.5f, mScaling.z + 0.95f));

//	exhaust->SetScaling(vec3(mScaling.x + 0.25f, mScaling.y + 0.2f, mScaling.z + 0.2f));

	bus->SetScaling(mScaling);

	wheel1->SetScaling(vec3(mScaling.x + 0.8f, mScaling.y + 0.8f, mScaling.z + 0.25f));

	wheel2->SetScaling(vec3(mScaling.x + 0.8f, mScaling.y + 0.8f, mScaling.z + 0.25f));

	wheel3->SetScaling(vec3(mScaling.x + 0.8f, mScaling.y + 0.8f, mScaling.z + 0.25f));

	wheel4->SetScaling(vec3(mScaling.x + 0.8f, mScaling.y + 0.8f, mScaling.z + 0.25f));

	frontLight1->setScaling(vec3(mScaling.x + 0.2f, mScaling.y + 0.2f, mScaling.z + 0.25f));

	frontLight2->setScaling(vec3(mScaling.x + 0.2f, mScaling.y + 0.2f, mScaling.z + 0.25f));

	tailLight1->setScaling(vec3(mScaling.x + 0.2f, mScaling.y + 0.2f, mScaling.z + 0.25f));

	tailLight2->setScaling(vec3(mScaling.x + 0.2f, mScaling.y + 0.2f, mScaling.z + 0.25f));
	
}

void Car::SetRotation()
{
	
}

void Car::SetAnimation(int start)
{
	animStart = 1;
}

GLuint Car::setVAO()
{
	GLuint cubeVAO = TexturedCube::makeCubeVAO();
	return cubeVAO;
}

void Car::setLights(int shader)
{
	int lightLocation = glGetUniformLocation(shader, "pointLights[0].position");
	vec3 light = frontLight1->GetPosition();
	glUniform3f(lightLocation, light.x + 0.4f, light.y, light.z -0.1f);

	lightLocation = glGetUniformLocation(shader, "pointLights[1].position");
	light = frontLight2->GetPosition();
	glUniform3f(lightLocation, light.x + 0.4f, light.y, light.z +0.1f);


	lightLocation = glGetUniformLocation(shader, "pointLights[2].position");
	light = tailLight1->GetPosition();
	glUniform3f(lightLocation, light.x - 0.3f, light.y, light.z - 0.1f);
	lightLocation = glGetUniformLocation(shader, "pointLights[3].position");
	light = tailLight2->GetPosition();
	glUniform3f(lightLocation, light.x - 0.3f, light.y, light.z +0.1f);
}
