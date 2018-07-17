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
#include <Common/Partido.h>
#include <Common/WrapperCV.h>


GLFWwindow* initWindow();
void ProcesarArchivo(int frame);
void ProcesarArchivo3dPose(int frame);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 2.0f, 14.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float currentFrame = 0.0f;


int main()
{
	WrapperCV configCV;
	configCV.ObtenerHomografia("");
	GLFWwindow* window = initWindow();

	Partido partido;


    int frameJSON = 0;
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    while (!glfwWindowShouldClose(window))
    {
    	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			frameJSON = 0;
    	currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		if( deltaTime >= maxPeriod ) {
			lastFrame = currentFrame;
			partido.LoadPlayers(frameJSON);
			frameJSON += 10;
		}

    	glm::mat4 view = camera.GetViewMatrix();





        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        partido.DrawAll();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
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
	    //glfwSetCursorPosCallback(window, mouse_callback);
	    //glfwSetScrollCallback(window, scroll_callback);

	    // tell GLFW to capture our mouse
	    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
