#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem.h>

#include <Shader/shader.h>
#include <Camera/camera.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <Common/Jugador.h>
#include <Common/Lugar.h>
#include "include/rapidjson/document.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/ostreamwrapper.h"

GLFWwindow* initWindow();
void ProcesarArchivo(int frame);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const double maxFPS = 50.0;
const double maxPeriod = 1.0 / maxFPS;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
std::vector<Jugador> list_personas;


int main()
{
	GLFWwindow* window = initWindow();
    Shader ourShader("7.4.camera.vs", "7.4.camera.fs");
    Shader modelShader("resources/shaders/model_light.vs", "resources/shaders/model_light.fs");

    Lugar lugar;


    int frameJSON = 0;

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    while (!glfwWindowShouldClose(window))
    {
    	glm::mat4 view = camera.GetViewMatrix();

    	float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;

    	if( deltaTime >= maxPeriod ) {
    		lastFrame = currentFrame;
    		ProcesarArchivo(frameJSON);
    		frameJSON += 1;
    	}

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        glm::mat4 model=glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.0f,1.4f,12.0f));
        model = glm::scale(model, glm::vec3(2.2f,2.2f,1.0f));
        for (unsigned int i = 0; i < list_personas.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
        	Jugador temp = list_personas[i];
			ourShader.setMat4("model", model);
        	temp.Draw(ourShader);
        }

        // Inicio - RENDER LUGAR

        model=glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
        modelShader.use();
        modelShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        modelShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
        modelShader.setVec3("lightPos", 1.0f, 2.0f, 10.0f);
        modelShader.setMat4("projection", projection);
		modelShader.setMat4("view", view);
		modelShader.setMat4("model", model);
        lugar.Draw(modelShader);

		// Fin - RENDER LUGAR

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

void ProcesarArchivo(int frame){
	using namespace rapidjson;
	float relaciones[] = {1,2, 2,3, 3,4, 1,5,5,6,6,7, 1,8, 8,9, 9,10, 1,11, 11,12, 12, 13 };
	std::string path = "";
	std::string String = "";
	String = static_cast<std::ostringstream*>( &(std::ostringstream() << frame) )->str();
	path = "";
	path.append("/home/rober/Test/output_tenis_dos_4/pruebados");
	if(frame < 10){
		path.append("_00000000000");
	} else if (frame < 100) {
		path.append("_0000000000");
	} else if (frame < 1000) {
		path.append("_000000000");
	} else {
		path.append("_00000000");
	}
	path.append(String);
	path.append("_keypoints.json");
	std::ifstream ifs { path.c_str() };
	if ( !ifs.is_open() )
	{
		return;
	}
	IStreamWrapper isw { ifs };
	Document doc {};
	doc.ParseStream( isw );
	Value& personas = doc["people"];
    assert(personas.IsArray());


	float parent;
	float child;
	int rel;
	list_personas.clear();

	for (SizeType i = 0; i < personas.Size(); i++){
		using namespace rapidjson;
		Jugador eJugador;
		parent = 0;
		child = 0;
		rel = 0;
		Value& keypoints = personas[i]["pose_keypoints_2d"];
		for(int j=0; j<24; j += 2){
			parent = relaciones[j];
			child = relaciones[j+1];
			if(keypoints[parent*3+2].GetFloat() >= 0.1f){
				eJugador.vertices[rel] = keypoints[parent*3].GetFloat();
				eJugador.vertices[rel+1] = keypoints[parent*3+1].GetFloat()*(-1);
			}
			eJugador.vertices[rel+2] = 0.0f;
			eJugador.vertices[rel+3] = 1.0f;
			eJugador.vertices[rel+4] = 0.0f;
			eJugador.vertices[rel+5] = 0.0f;
			rel += 6;

			if(keypoints[child*3+2].GetFloat() >= 0.1f){
				eJugador.vertices[rel] = keypoints[child*3].GetFloat();
				eJugador.vertices[rel+1] = keypoints[child*3+1].GetFloat()*(-1);
			}
			eJugador.vertices[rel+2] = 0.0f;
			eJugador.vertices[rel+3] = 1.0f;
			eJugador.vertices[rel+4] = 0.0f;
			eJugador.vertices[rel+5] = 0.0f;
			rel += 6;
		}
		list_personas.push_back(eJugador);
	}
}

GLFWwindow* initWindow(){
	// glfw: initialize and configure
	    // ------------------------------
	    glfwInit();
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

	    // glfw window creation
	    // --------------------
	    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	    if (window == NULL)
	    {
	        std::cout << "Failed to create GLFW window" << std::endl;
	        glfwTerminate();
	        return nullptr;
	    }
	    glfwMakeContextCurrent(window);
	    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	    glfwSetCursorPosCallback(window, mouse_callback);
	    glfwSetScrollCallback(window, scroll_callback);

	    // tell GLFW to capture our mouse
	    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	    // glad: load all OpenGL function pointers
	    // ---------------------------------------
	    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	    {
	        std::cout << "Failed to initialize GLAD" << std::endl;
	        return nullptr;
	    }

	    // configure global opengl state
	    // -----------------------------
	    glEnable(GL_DEPTH_TEST);
	    return window;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
