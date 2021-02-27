
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <string>
#include <time.h>
#include "Camera.h"
#include "FirstPersonCamera.h"
#include "ThirdPersonCamera.h"
#include "EventManager.h"
#include "TexturedCube.h"
#include "Car.h"
#include "WheelModel.h"
#include "Models.h"
#include "Model.h"
#include "Light.h"
#include "Block.h"
#include "Shadows.h"
#include <irrKlang.h>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
						// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include <FreeImageIO.h>
//#include "OBJloaderV2.h"  //For loading .obj files using a polygon list format
#include "A2main.h"

using glm::mat4;
using std::vector;
using namespace glm;
using namespace std;
using namespace irrklang;

#define SHADOW_WIDTH 2048
#define SHADOW_HEIGHT 2048
#define SCR_WIDTH 1024
#define SCR_HEIGHT 768

int compileAndLinkShaders(std::string vertex_shader_path, std::string fragment_shader_path)
{
	// compile and link shader program
	// return shader program id
	// ------------------------------------
	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_shader_path.c_str());
		getchar();
		exit(-1);
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	std::string geometryCode;

	char const* VertexSourcePointer = VertexShaderCode.c_str();
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

int compileAndLinkShaders(std::string vertex_shader_path, std::string fragment_shader_path, std::string shadow_shader_path)
{
	// compile and link shader program
	// return shader program id
	// ------------------------------------
	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_shader_path.c_str());
		getchar();
		exit(-1);
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	std::string GeometryShaderCode;
	std::ifstream GeometryShaderStream(shadow_shader_path, std::ios::in);
	if (GeometryShaderStream.is_open()) {
		std::string Line = "";
		while (getline(GeometryShaderStream, Line))
			GeometryShaderCode += "\n" + Line;
		GeometryShaderStream.close();
	}


	char const* VertexSourcePointer = VertexShaderCode.c_str();
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Geometry shader
	char const* GeometrySourcePointer = GeometryShaderCode.c_str();
	int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometryShader, 1, &GeometrySourcePointer, NULL);
	glCompileShader(geometryShader);

	// check for shader compile errors
	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, geometryShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);

	return shaderProgram;
}

	void setProjectionMatrix(int shaderProgram, mat4 projectionMatrix)
	{
		glUseProgram(shaderProgram);
		GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	}

	void setViewMatrix(int shaderProgram, mat4 viewMatrix)
	{
		glUseProgram(shaderProgram);
		GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	}

	void setWorldMatrix(int shaderProgram, mat4 worldMatrix)
	{
		glUseProgram(shaderProgram);
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
	}

	void setLights(int shaderProgram) {
		// directional light
		glUseProgram(shaderProgram);
		

	}


int main(int argc, char* argv[])
{
	EventManager::Initialize();
	// Initialize GLFW and OpenGL version
	
	GLFWwindow* spWindow = EventManager::GetWindow();
	glfwMakeContextCurrent(spWindow);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to create GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	// start the sound engine with default parameters
	ISoundEngine* engine = createIrrKlangDevice();


	if (!engine)
		return 0; // error starting up the engine

	// Show OpenGL version on console
	std::cout << glGetString(GL_VERSION) << std::endl;



	// Black background
	glClearColor(0.53f, 0.80f, 0.98f, 1.0f);

#if defined(PLATFORM_OSX)
	std::string shaderPathPrefix = "Shaders/";
#else
	std::string shaderPathPrefix = "../Assets/Shaders/";
#endif
//	int colorShaderProgram = compileAndLinkShaders(shaderPathPrefix + "VertexShader.vertexshader", shaderPathPrefix + "FragmentShader.fragmentshader");
//	int lightTextureShaderProgram = compileAndLinkShaders(shaderPathPrefix + "Pathlines.vertexshader", shaderPathPrefix + "Pathlines.fragmentshader");
	int lightTextureShaderProgram = compileAndLinkShaders(shaderPathPrefix + "TexturedLight.vertexshader", shaderPathPrefix + "TexturedLight.fragmentshader"); // Single light
//	int lightTextureShaderProgram = compileAndLinkShaders(shaderPathPrefix + "Textured.vertexshader", shaderPathPrefix + "Textured.fragmentshader"); // Testing multiple lights
	int depthShaderProgram = compileAndLinkShaders(shaderPathPrefix + "depthshader.vertexshader", shaderPathPrefix + "depthshader.fragmentshader", shaderPathPrefix + "depthshader.geometryshader");
	

	//Setup models
#if defined(PLATFORM_OSX)
	string reindeerPath = "Models/reindeer.obj";
	string santaPath = "Models/Santa.obj";
#else
	string reindeerPath = "../Assets/Models/reindeer.obj";
	string santaPath = "../Assets/Models/Santa.obj";
	string bellsPath = "../Assets/Models/Bells.obj";
	string girlPath = "../Assets/Models/Plane.obj";
	string snowPath = "../Assets/Models/Snowflake.obj";
	string snowmanPath = "../Assets/Models/snow.obj";
	string elfPath = "../Assets/Models/elf.obj";
#endif

	glUseProgram(lightTextureShaderProgram);
	int txtsamplerloc = glGetUniformLocation(lightTextureShaderProgram, "textureSampler");
	glUniform1d(txtsamplerloc, 0);

	glUseProgram(lightTextureShaderProgram);
	int dmloc = glGetUniformLocation(lightTextureShaderProgram, "depthMap");
	glUniform1d(dmloc, 1);

	int reindeerVertices;
	int santaVertices;
	int bellsVertices;
	int girlVertices;
	int snowVertices;
	int snowmanVertices;
	int elfVertices;
	//GLuint reindeerVAO = setupModelVBO(reindeerPath, reindeerVertices);
	//GLuint santaVAO = setupModelVBO(santaPath, santaVertices);
	GLuint reindeerVAO = Models::makeModelsVAO(reindeerPath, reindeerVertices);
	int activeVAOVertices = reindeerVertices;
	GLuint activeVAO = reindeerVAO;

	GLuint santaVAO = Models::makeModelsVAO(santaPath, santaVertices);
	int activeSantaVertices = santaVertices;
	GLuint activeSantaVAO = santaVAO;

	GLuint bellsVAO = Models::makeModelsVAO(bellsPath, bellsVertices);
	int activebellsVertices = bellsVertices;
	GLuint activeBellsVAO = bellsVAO;

	GLuint girlVAO = Models::makeModelsVAO(girlPath, girlVertices);
	int activeGirlVertices = girlVertices;
	GLuint activeGirlVAO = girlVAO;

	GLuint snowVAO = Models::makeModelsVAO(snowPath, snowVertices);
	int activeSnowVertices = snowVertices;
	GLuint activeSnowVAO = snowVAO;

	GLuint snowmanVAO = Models::makeModelsVAO(snowmanPath, snowmanVertices);
	int activeSnowmanVertices = snowmanVertices;
	GLuint activeSnowmanVAO = snowmanVAO;

	GLuint elfVAO = Models::makeModelsVAO(elfPath, elfVertices);
	int activeElfVertices = elfVertices;
	GLuint activeElfVAO = elfVAO;


//	int activeVAOVertices2 = santaVertices;
//	GLuint activeVAO2 = santaVAO;
	// General scene lighting
	glm::vec3 LightPos(0.0f, 30.0f, 0.0f);
//	int vertexColorLocation = glGetUniformLocation(colorShaderProgram, "lightPos");
//	glUseProgram(colorShaderProgram);
//	glUniform3f(vertexColorLocation, LightPos.x, LightPos.y, LightPos.z);

	int vertextxtColorLocation = glGetUniformLocation(lightTextureShaderProgram, "lightPos");
	glUseProgram(lightTextureShaderProgram);
	glUniform3f(vertextxtColorLocation, LightPos.x, LightPos.y, LightPos.z);

	int vertexColorLocation2 = glGetUniformLocation(lightTextureShaderProgram, "lightColor");
	glUseProgram(lightTextureShaderProgram);
	glUniform3f(vertexColorLocation2, 1.0f, 1.0f, 1.0f);

	int tex = 1;
	int lightSwitchlocation = glGetUniformLocation(lightTextureShaderProgram, "tex");
	glUniform1i(lightSwitchlocation, tex);


	// Camera setup
	std::vector<Camera*> camera;
	unsigned int currentCamera;
	FirstPersonCamera* firstpersoncamera = new FirstPersonCamera(vec3(0.0f, 5.0f, 20.0f));
	camera.push_back(firstpersoncamera);
	currentCamera = 0;
//	int txtViewPosColorLocation = glGetUniformLocation(textureShaderProgram, "viewPos");
	// Setup initial keyboard release state
	int releaseState = GLFW_RELEASE;
	glUseProgram(lightTextureShaderProgram);
	int txtViewPosColorLocation = glGetUniformLocation(lightTextureShaderProgram, "viewPos");
	vec3 cameraPosition = camera[currentCamera]->GetPosition();
	glUniform3f(txtViewPosColorLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);
	// Camera parameters for view transform
	//vec3 cameraPosition(0.6f, 4.0f, 10.0f);
	//vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
	//vec3 cameraUp(0.0f, 1.0f, 0.0f);

//	int viewPosColorLocation = glGetUniformLocation(colorShaderProgram, "viewPos");
//	glUseProgram(colorShaderProgram);
//	glUniform3f(viewPosColorLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);
	//int txtViewPosColorLocation = glGetUniformLocation(textureShaderProgram, "viewPos");
	//glUseProgram(textureShaderProgram);
	//glUniform3f(txtViewPosColorLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);

//	vertexColorLocation = glGetUniformLocation(colorShaderProgram, "lightColor");
//	glUseProgram(colorShaderProgram);
//	glUniform3f(vertexColorLocation, 1.0f, 1.0f, 1.0f);

	// Other camera parameters
	//float cameraSpeed = 2.0f;
	//float cameraFastSpeed = 2 * cameraSpeed;
	//float cameraHorizontalAngle = 90.0f;
	//float cameraVerticalAngle = 0.0f;
	//bool  cameraFirstPerson = true; // press 1 or 2 to toggle this variable

	// Spinning cube at camera position
	float spinningCubeAngle = 0.0f;

	// Set projection matrix for shader, this won't change
	mat4 projectionMatrix = glm::perspective(70.0f,            // field of view in degrees
		1024.0f / 768.0f,  // aspect ratio
		0.01f, 100.0f);   // near and far (near > 0)

	mat4 viewMatrix = camera[currentCamera]->GetViewMatrix();
	// Set initial view matrix
//	mat4 viewMatrix = lookAt(cameraPosition,  // eye
	//	cameraPosition + cameraLookAt,  // center
		//cameraUp); // up

	// Set View and Projection matrices on both shaders
//	setViewMatrix(colorShaderProgram, viewMatrix);
//	setViewMatrix(lightShaderProgram, viewMatrix);
//	setViewMatrix(textureShaderProgram, viewMatrix);
	setViewMatrix(lightTextureShaderProgram, viewMatrix);
	setViewMatrix(depthShaderProgram, viewMatrix);
	

//	setProjectionMatrix(colorShaderProgram, projectionMatrix);
//	setProjectionMatrix(lightShaderProgram, projectionMatrix);
//	setProjectionMatrix(textureShaderProgram, projectionMatrix);
	setProjectionMatrix(lightTextureShaderProgram, projectionMatrix);
//	setProjectionMatrix(depthShaderProgram, projectionMatrix);
	// For frame time
	float lastFrameTime = glfwGetTime();
	int lastMouseLeftState = GLFW_RELEASE;
	double lastMousePosX, lastMousePosY;
	glfwGetCursorPos(EventManager::GetWindow(), &lastMousePosX, &lastMousePosY);

	// Other OpenGL states to set once
	// Enable Backface culling
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); //  Enable Depth Test

	bool ifTextured = true;
	Car* car = new Car(lightTextureShaderProgram);
	//Light* light = new Light;
	//light->SetPosition(LightPos);

	vec3 camPos = car->getPosition();
	ThirdPersonCamera* thirdpersoncamera = new ThirdPersonCamera(vec3(camPos.x, camPos.y + 5.0f, camPos.z + 20.0f));
	camera.push_back(new ThirdPersonCamera(vec3(camPos.x, camPos.y, camPos.z+5.0f)));

	// Set the light positions
	glm::vec3 pointLightPositions[] = {
		glm::vec3(2.9f,  0.8f,  -0.3f),
		glm::vec3(2.9f, 0.8f, 0.3f),
		glm::vec3(-2.5f,  0.8f, -0.3f),
		glm::vec3(-2.5f,  0.8f, 0.3f)
	};
	// Draw ground
	GLuint cubeVAO=TexturedCube::makeCubeVAO();
	Block* ground = new Block(lightTextureShaderProgram);
	ground->setScaling(vec3(200.0f, 0.02f, 200.0f));
	//WheelModel* wheel = new WheelModel;
	//wheel->SetScaling(vec3(5.0f, 5.0f, 5.0f));
	float dt;
	float sLastFrameTime = glfwGetTime();
	srand(time(NULL));

	float spinningAngle = 0;
	double currentTime = glfwGetTime();
	dt = static_cast<float>(currentTime - sLastFrameTime);
	spinningAngle += 45.0f * dt;
	std::list<Quad*>particles;
	Models* reindeer = new Models(activeVAO, activeVAOVertices, lightTextureShaderProgram);
	reindeer->SetPosition(vec3(30.0f, 0.0f, -5.0f));
	reindeer->SetScaling(vec3(0.025f, 0.025f, 0.025f));
	reindeer->SetRotation(vec3(1.0f, 0.0f, 0.0f), -90.0f);

	Models* santa = new Models(activeSantaVAO, activeSantaVertices, lightTextureShaderProgram);
	santa->SetPosition(vec3(50.0f, 0.0f, -5.0f));
	santa->SetScaling(vec3(0.025f, 0.025f, 0.025f));
	santa->SetRotation(vec3(1.0f, 0.0f, 0.0f), -90.0f);

	Models* bells = new Models(activeBellsVAO, activebellsVertices, lightTextureShaderProgram);
	bells->SetPosition(vec3(10.0f, 0.0f, -10.0f));
	bells->SetScaling(vec3(0.50f, 0.50f, 0.50f));
	bells->SetRotation(vec3(1.0f, 0.0f, 0.0f), -90.0f);

	Models* girl = new Models(activeGirlVAO, activeGirlVertices, lightTextureShaderProgram);
	girl->SetPosition(vec3(70.0f, 0.0f, -5.0f));
	girl->SetScaling(vec3(0.25f, 0.25f, 0.25f));
	girl->SetRotation(vec3(1.0f, 0.0f, 0.0f), -90.0f);

	Models* snow = new Models(activeSnowVAO, activeSnowVertices, lightTextureShaderProgram);
	snow->SetPosition(vec3(-50.0f, 5.0f, -5.0f));
	snow->SetScaling(vec3(0.25f, 0.25f, 0.25f));
	

	Models* snowman = new Models(activeSnowmanVAO, activeSnowmanVertices, lightTextureShaderProgram);
	snowman->SetPosition(vec3(-30.0f, 0.0f, -6.0f));
	snowman->SetScaling(vec3(1.0f, 1.0f, 1.0f));


	Models* elf= new Models(activeElfVAO, activeElfVertices, lightTextureShaderProgram);
	elf->SetPosition(vec3(-10.0f, 0.0f, -5.0f));
	elf->SetScaling(vec3(0.50f, 0.50f, 0.50f));
	elf->SetRotation(vec3(1.0f, 0.0f, 0.0f), -90.0f);

	Shadows* shadows = new Shadows(lightTextureShaderProgram);


	float spawnTimer=0;
	const float SPAWN_PERIOD = 0.25;
	spinningAngle = 0.0f;
	int releaseL = GLFW_RELEASE;
	

	// Entering Main Loop
	while (!glfwWindowShouldClose(EventManager::GetWindow()))
	{
		EventManager::Update();

		currentTime = glfwGetTime();
		dt = static_cast<float>(currentTime - sLastFrameTime);
		sLastFrameTime = currentTime;
		
		camera[currentCamera]->Update(dt);
		camPos = car->getPosition();
		camera[1]->SetPosition(vec3(camPos.x+5.0f, camPos.y+2.0f, camPos.z));
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		// Each frame, reset color of each pixel to glClearColor
		float near_plane = 1.0f;
		float far_plane = 25.0f;

		
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, shadows->getFBO());
		glUseProgram(depthShaderProgram);
		const mat4 lightProjection = shadows->projection();
		vector<mat4> views = shadows->views();
		std::vector<glm::mat4> shadowTransforms;
		for (int i = 0; i < 6; i++)
		{
			glUniformMatrix4fv(glGetUniformLocation(depthShaderProgram, ("shadowMatrices[" + std::to_string(i) + "]").c_str()), 1, GL_FALSE, value_ptr(lightProjection * views[i]));
		}
		int shadows_fpLocation = glGetUniformLocation(depthShaderProgram, "far_plane");
		glUniform1f(shadows_fpLocation, far_plane);
		int lightposLocation = glGetUniformLocation(depthShaderProgram, "lightPos");
		glUniform3f(lightposLocation, LightPos.x, LightPos.y, LightPos.z);

		
			ground->Draw(depthShaderProgram, shadows->getdepthMap());
			car->Draw(depthShaderProgram, shadows->getdepthMap());

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

			//Reset views
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(lightTextureShaderProgram);
		setViewMatrix(lightTextureShaderProgram, viewMatrix);
	

		vec3 cameraPosition = camera[currentCamera]->GetPosition();
		int lightLocation = glGetUniformLocation(lightTextureShaderProgram, "ViewPos");
		glUniform3f(lightLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);
		int shadows_fpLocation2 = glGetUniformLocation(lightTextureShaderProgram, "far_plane");
		glUniform1f(shadows_fpLocation2, far_plane);
		int lightposLocation2 = glGetUniformLocation(lightTextureShaderProgram, "lightPos");
		glUniform3f(lightposLocation2, LightPos.x, LightPos.y, LightPos.z);
		lightLocation = glGetUniformLocation(lightTextureShaderProgram, "material.shininess");
		glUniform1f(lightLocation, 32.0f);

		setLights(lightTextureShaderProgram);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, shadows->getdepthMap());
		

		reindeer->Draw(lightTextureShaderProgram);
		santa->Draw(lightTextureShaderProgram);
		bells->Draw(lightTextureShaderProgram);
		snow->Draw(lightTextureShaderProgram);
		girl->Draw(lightTextureShaderProgram);
		snowman->Draw(lightTextureShaderProgram);
		elf->Draw(lightTextureShaderProgram);

		ground->Draw(lightTextureShaderProgram, shadows->getdepthMap());
		car->Draw(lightTextureShaderProgram, shadows->getdepthMap());

	//	if (ifTextured == true) {
			//wheel->Draw(tireTextureID);
	//		ground->Draw(lightTextureShaderProgram);
	//		car->Draw(lightTextureShaderProgram);
			
//			light->Draw(lightShaderProgram);
			
	//	}
	//	else {
		//	ground->Draw(textureShaderProgram, greengrassTextureID);
		//	car->Draw(textureShaderProgram, purplemetalTextureID, tireTextureID, lampTextureID);
	//	}

		// Spinning model rotation animation
		//spinningAngle += 45.0f * dt; //This is equivalent to 45 degrees per second

		//glUseProgram(lightTextureShaderProgram);

		//glActiveTexture(GL_TEXTURE0);
		//GLuint textureLocation = glGetUniformLocation(lightTextureShaderProgram, "textureSampler"); // shader program
		//glBindTexture(GL_TEXTURE_2D, purplemetalTextureID);
		//glUniform1i(textureLocation, 0);

		//GLuint worldMatrixLocation = glGetUniformLocation(lightTextureShaderProgram, "worldMatrix");
		//Set world matrix
		//mat4 modelWorldMatrix =
		//	glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, -5.0f)) *
		//	glm::rotate(mat4(1.0f), radians(spinningAngle), vec3(0.0f, 1.0f, 0.0f)) *
		//	glm::rotate(mat4(1.0f), radians(-90.0f), vec3(1.0f, 0.0f, 0.0f)) *
		//	glm::scale(mat4(1.0f), vec3(0.2f));
		//setWorldMatrix(lightTextureShaderProgram, modelWorldMatrix);

		//Draw the stored vertex objects
		//glBindVertexArray(activeVAO);
		//glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);

		//TODO3 Draw model as elements, instead of as arrays
		//glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);
		//modelWorldMatrix =
		//	glm::translate(mat4(1.0f), vec3(1.0f, 1.0f, -5.0f)) *
		//	glm::rotate(mat4(1.0f), radians(spinningAngle), vec3(0.0f, 1.0f, 0.0f)) *
		//	glm::rotate(mat4(1.0f), radians(-90.0f), vec3(1.0f, 0.0f, 0.0f)) *
		//	glm::scale(mat4(1.0f), vec3(0.2f));
		//setWorldMatrix(lightTextureShaderProgram, modelWorldMatrix);

		//Draw the stored vertex objects
		//glBindVertexArray(activeVAO2);
		//glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices2);
		vec3 originalAxis(0, 0, 1);
		vec3 cameraLookAt = vec3(-firstpersoncamera->GetLookAt());
		if (currentCamera == 0) {
			cameraLookAt=vec3(-firstpersoncamera->GetLookAt());
		}
		else if (currentCamera == 1) {
			cameraLookAt=vec3(-thirdpersoncamera->GetLookAt());
		}
		cameraLookAt.y = 0; //project onto xz plane
		cameraLookAt.x *= -1;
		cameraLookAt = normalize(cameraLookAt);


		float billboardRotation = glm::acos(-1 * dot(originalAxis, cameraLookAt)) * 360 / (2 * pi<float>());
		
		if (cameraLookAt.x > 0) {
			billboardRotation = 360 - billboardRotation;
		}
	 
		// Draw car parts
		car->Update(dt, billboardRotation);


		// Spinning cube at camera position
		/*spinningCubeAngle += 180.0f * dt;

		if (cameraFirstPerson) {
			mat4 spinningCubeWorldMatrix(1.0f);
			mat4 spinningCubeViewMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -1.0f)) *
				rotate(mat4(1.0f), radians(spinningCubeAngle), vec3(0.0f, 1.0f, 0.0f)) *
				scale(mat4(1.0f), vec3(0.01f, 0.01f, 0.01f));
		}
		else {
			// In third person view, let's draw the spinning cube in world space, like any other models
			mat4 spinningCubeWorldMatrix = translate(mat4(1.0f), cameraPosition) *
				rotate(mat4(1.0f), radians(spinningCubeAngle), vec3(0.0f, 1.0f, 0.0f)) *
				scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f));

		}
		glDrawArrays(GL_TRIANGLES, 0, 36);
		*/
		// End Frame
		glfwSwapBuffers(EventManager::GetWindow());
		glfwPollEvents();

		// Handle inputs
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(EventManager::GetWindow(), true);

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_Q) == GLFW_PRESS) // Start the animation
		{
			engine->play2D("../Assets/Sounds/Wheelsonthebus.mp3", GL_TRUE);
			currentCamera = 1;
			car->setCarPosition(vec3(-94.0f, 0.0f, 0.0f));
			car->SetAnimation(1);
		}

		int newState2 = glfwGetKey(EventManager::GetWindow(), GLFW_KEY_L);
		if (newState2 == GLFW_RELEASE && releaseL == GLFW_PRESS) {
			if (tex == 1)
				tex = 0;
			else if (tex == 0)
				tex = 1;
			glUseProgram(lightTextureShaderProgram);
			int lightSwitchlocation = glGetUniformLocation(lightTextureShaderProgram, "tex");
			glUniform1i(lightSwitchlocation, tex);

		}
		releaseL = newState2;

/*		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_1) == GLFW_PRESS) // move camera down
		{
			cameraFirstPerson = true;
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_2) == GLFW_PRESS) // move camera down
		{
			cameraFirstPerson = false;
		}*/

/*		// We'll change this to be a first or third person camera
		bool fastCam = glfwGetKey(EventManager::GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(EventManager::GetWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
		float currentCameraSpeed = (fastCam) ? cameraFastSpeed : cameraSpeed;


		//  Calculate mouse motion dx and dy
		//  Update camera horizontal and vertical angle
		double mousePosX, mousePosY;
		glfwGetCursorPos(EventManager::GetWindow(), &mousePosX, &mousePosY);

		double dx = mousePosX - lastMousePosX;
		double dy = mousePosY - lastMousePosY;

		lastMousePosX = mousePosX;
		lastMousePosY = mousePosY;

		// Convert to spherical coordinates
		const float cameraAngularSpeed = 60.0f;
		cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
		cameraVerticalAngle -= dy * cameraAngularSpeed * dt;

		// Clamp vertical angle to [-85, 85] degrees
		cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
		if (cameraHorizontalAngle > 360)
		{
			cameraHorizontalAngle -= 360;
		}
		else if (cameraHorizontalAngle < -360)
		{
			cameraHorizontalAngle += 360;
		}

		float theta = radians(cameraHorizontalAngle);
		float phi = radians(cameraVerticalAngle);

		cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
		vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

		glm::normalize(cameraSideVector);*/

		// Change camera between First person Third person
		int newCstate = glfwGetKey(EventManager::GetWindow(), GLFW_KEY_C);
		if (newCstate == GLFW_RELEASE && releaseState == GLFW_PRESS) 
		{
			if (currentCamera == 1) {
				currentCamera = 0;
			}
			else if (currentCamera == 0) {
				currentCamera = 1;
			}

		}
		releaseState = newCstate;
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_1) == GLFW_PRESS)
		{
			currentCamera = 0;
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_2) == GLFW_PRESS)
		{
			if (camera.size() > 1)
			{
				currentCamera = 1;
			}
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_3) == GLFW_PRESS)
		{
			if (camera.size() > 2)
			{
				currentCamera = 2;
			}
		}

/*		// use camera lookat and side vectors to update positions with ASDW
		// adjust code below
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS) // move camera to the left
		{
			
			cameraVerticalAngle += 5.0f;
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) // move camera to the right
		{
			cameraVerticalAngle -= 5.0f;
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) // move camera up
		{
			cameraHorizontalAngle -= 5.0f;
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) // move camera down
		{
			cameraHorizontalAngle += 5.0f;
		}
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_HOME) == GLFW_PRESS)
		{
			cameraPosition=vec3(0.6f, 4.0f, 10.0f);
			cameraLookAt=vec3(0.0f, 0.0f, -1.0f);
			cameraUp=vec3(0.0f, 1.0f, 0.0f);
			cameraHorizontalAngle = 90.0f;
			cameraVerticalAngle = 0.0f;
		}
		// ZOoms out of scene
		if (glfwGetMouseButton(EventManager::GetWindow(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		{
			cameraPosition -= vec3(cameraLookAt.x - 0.2f, cameraLookAt.y -0.2f, cameraLookAt.z - 0.2f);
		}
		// Tilts the camera
		if (glfwGetMouseButton(EventManager::GetWindow(), GLFW_MOUSE_BUTTON_3) == GLFW_PRESS)
		{
			cameraVerticalAngle -= 5.0f;
		}
		// Zooms in the scene
		if (glfwGetMouseButton(EventManager::GetWindow(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
		{
			cameraPosition += vec3(cameraLookAt.x + 0.2f, cameraLookAt.y + 0.2f, cameraLookAt.z + 0.2f);
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_L) == GLFW_PRESS)
		{
			if (ifTextured == true)
				ifTextured = false;
			else
				ifTextured = true;
		}

		// Set the view matrix for first and third person cameras
		// - In first person, camera lookat is set like below
		// - In third person, camera position is on a sphere looking towards center
		mat4 viewMatrix(1.0f);

		
		if (cameraFirstPerson) {
			viewMatrix = lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp);
		}
		else {
			float radius = 5.0f;
			vec3 position = cameraPosition - vec3(radius * cosf(phi) * cosf(theta),
				radius * sinf(phi),
				-radius * cosf(phi) * sinf(theta));
			viewMatrix = lookAt(position, cameraPosition, cameraUp);
		}
*/
		if (currentCamera == 0) {
			viewMatrix = camera[currentCamera]->GetViewMatrix();
		}
		if (currentCamera == 1) {
			viewMatrix = camera[currentCamera]->GetViewMatrix();
		}
//		setViewMatrix(colorShaderProgram, viewMatrix);
//		setViewMatrix(texturedShaderProgram, viewMatrix);
//		setViewMatrix(textureShaderProgram, viewMatrix);
		
		

	}

	for (list<Quad*>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		delete* it;
	}

	// Camera
	for (vector<Camera*>::iterator it = camera.begin(); it < camera.end(); ++it)
	{
		delete* it;
	}
	camera.clear();

	particles.clear();


	// Shutdown GLFW
	glfwTerminate();

	return 0;
}
