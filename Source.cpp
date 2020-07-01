#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRender.h"
#include "MeshRenderer.h"
#include "TextureLoader.h"
// bullet physics includes:
#include <btBulletDynamicsCommon.h>

// including chrono fro time
#include <chrono>

// bullet dynamics pointer:
btDiscreteDynamicsWorld* dynamicsWorld;
// create Camera instace
Camera* camera;

// create renderer instace
LightRender* light;

// sphere mesh renderer
MeshRenderer* Sphere;


void initGame()
{
	printf("calling intGame************ \n");
	glEnable(GL_DEPTH_TEST);

	// init physics:
	btBroadphaseInterface* broadPhase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadPhase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));

	// creatin a dymamic sphere
	btCollisionShape* sphereShape = new btSphereShape(1.0f);
	btDefaultMotionState* sphereMotionState = 
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0,10.0f,0)));
	// creating physical properties:
	btScalar mass = 10.0;
	btVector3 sphereInertia(0,0,0);
	sphereShape->calculateLocalInertia(mass, sphereInertia); /// inertia is an output value

	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState,
																sphereShape, sphereInertia);
	//create the actuall rigid body:
	btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);

	// settings properties:
	sphereRigidBody->setRestitution(1.0f);
	sphereRigidBody->setFriction(1.0f);

	// ading rigid body to world:
	dynamicsWorld->addRigidBody(sphereRigidBody);

	ShaderLoader shader;
	GLuint flatShaderProgram = shader.CreateProgram("Assets/Shaders/FlatModel.vs", 
													"Assets/Shaders/flatModel.fs");
	// texture shader Program:
	GLuint texturedShaderProgram = shader.CreateProgram("Assets/Shaders/TexturedModel.vs",
														"Assets/Shaders/TexturedModel.fs");
	TextureLoader tLoader;
	// stores the texture result of thexture loader
	GLuint sphereTexture = tLoader.getTextureID("Assets/Textures/globe.jpg");



	// initilize camera
	camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 20.0f));

	// init Mesh renderer to Sphere
	Sphere = new MeshRenderer(MeshType::kSphere, camera, sphereRigidBody);
	Sphere->setProgram(texturedShaderProgram);
	Sphere->setTexture(sphereTexture);
	Sphere->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	Sphere->setScale(glm::vec3(1.0f));

	// ligt Renderre init should be commented for performace issues.
	//light = new LightRender(MeshType::kSphere, camera);
	//light->setProgram(flatShaderProgram);
	//light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

/// Texture loader and Mesh rederer implemented.  todo Implement Bullet Physics:
// Adding Bullet Physics Chapter7 p.213 


void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1.0);
	
	// Draw game objects down here
	//light->draw();
	Sphere->draw();
}

static void glfwError(int id, const char* description)
{
	std::cout << description << std::endl;
}

int main(int argc, char** argv)
{
	glfwSetErrorCallback(&glfwError);
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL ", NULL, NULL);

	glfwMakeContextCurrent(window);
	glewInit();
	initGame();

	// initialize the chrono clock:
	// this is a chrono::steady_clock::time_point type, auto catch the type so you don't need to specify.
	auto previousTime = std::chrono::high_resolution_clock::now();

	while (!glfwWindowShouldClose(window))
	{	
		// in this loop all renders will ocure
		// init time:
		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();
		dynamicsWorld->stepSimulation(dt);
		renderScene();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	delete camera;
	delete Sphere;
	//delete light;
	return 0;
}