#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec3.hpp>
#include <string>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <stb_image.h>
#include "Shader.h"
#include "Camera.h"
#include "SceneGraph.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <dr_wav.h>
#include <rapidjson/document.h>     // rapidjson's DOM-style API
#include <rapidjson/prettywriter.h> // for stringify JSON
#include <ft2build.h>
#include "InputManager.h"
#include "Player.h"
#include "Collision.h"
#include <Courier.h>
#include "WindowManager.h"
#include FT_FREETYPE_H

using namespace GameEngine;

#define OpenAL_ErrorCheck(message)\
{\
	ALenum error = alGetError();\
	if( error != AL_NO_ERROR)\
	{\
		std::cerr << "OpenAL Error: " << error << " with call for " << #message << std::endl;\
	}\
}

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};
std::map<char, Character> Characters;

#define alec(FUNCTION_CALL)\
FUNCTION_CALL;\
OpenAL_ErrorCheck(FUNCTION_CALL)

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);
unsigned int loadCubemap(vector<std::string> faces);
void RenderText(std::shared_ptr<Shader> s, std::string text, float x, float y, float scale, glm::vec3 color);
void renderQuad();

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;
float p_height = 0.0f;
// timing
double passed_time = 0.0;
double current_time = 0.0;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float ftime = 0.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 lightPos(0.0f, 0.0f, -1.0f);

glm::vec3 direction;

glm::mat4 view;
glm::mat4 punktLightpos;

glm::mat4 lightProjection, lightView;
glm::mat4 lightSpaceMatrix;
float near_plane = 1.0f, far_plane = 7.5f;
unsigned int texture1, texture2, traincubesTexture;

GLFWwindow* window = nullptr;
std::shared_ptr<Shader> ourShader = nullptr;
//std::shared_ptr<Shader> lightSourceShader = nullptr;
std::shared_ptr<Shader> GUIShader = nullptr;
std::shared_ptr<Shader> shadowMap = nullptr;
std::shared_ptr<Shader> debugDepth = nullptr;

std::shared_ptr<Collision> colMan = nullptr;

int fps = 0;

double frame_time = 1.0 / 60.0;
glm::vec3 p_pos = { 1, 0, 1 };
glm::mat4 model_s;
glm::mat4 ortho;

int shinyyy = 32;

float p_const = 1.0f;
float p_lin = 0.09f;
float p_qua = 0.032f;
float p_ambient = 0.3f;
float p_diffuse = 1.0f;
float p_specular = 1.0f;

int score = 1000;

std::shared_ptr<SceneNode> root = nullptr;
std::shared_ptr<SceneNode> spunkt = nullptr;
std::shared_ptr<SceneNode> scena = nullptr;
std::shared_ptr<SceneNode> skier = nullptr;
std::shared_ptr<SceneNode> twodOrbit = nullptr;
std::shared_ptr<SceneNode> twod = nullptr;
std::shared_ptr<SceneNode> twod2 = nullptr;

std::shared_ptr<InputManager> inputManager = nullptr;

std::shared_ptr<Player> player;
std::shared_ptr<Courier> courier;

unsigned int VBO, VAO;
unsigned int lightSource_VBO, lightSource_VAO;
unsigned int GUI_VBO, GUI_VAO;

unsigned int depthMapFBO, depthMap;

float vertices[] = {
    /*
        -0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,  0.0f, -1.0f,
     */   
         0.5f,  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,


        -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.5f, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 1.0f,  0.0f,  0.0f,

         0.5f, -0.5f, -0.5f,  0.5f, 0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.5f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.5f, 0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.5f, 0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.5f, 0.5f,  0.0f,  1.0f,  0.0f,
};

float lights_vertices[] = {
    // positions          // normals           
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
};

float twoDD[] = {
             0.5f,  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f
};

glm::vec3 pLightColor(1.0f, 1.0f, 1.0f);
float a = 0.0f;

void input()
{
    processInput(window);
    view = camera.GetViewMatrix();
    inputManager->getInput();

}

void update(float dt)
{
    ourShader->setMat4("view", view); 
    model_s = spunkt->get_transform().m_world_matrix;
    twodOrbit->set_local_rotation({0, twodOrbit->get_transform().m_rotation.y + 1, 0});
    twodOrbit->update(root->get_transform(), true);
    //twod->update(root->get_transform(), true);


    if (ftime > 1)
    {
        if (score < 3000)
        {
            score += 100;
        }
        else
        {
            score = 1000;
        }

        ftime = 0;
    }
    else
    {
        ftime += dt;
    }

    player->Move();
    courier->Move();
    camera.Move();
    colMan->CollisionCheck();
}

void activate_lights(std::shared_ptr<Shader> shader)
{
    shader->setFloat("shininess", shinyyy);
    shader->setVec3("viewPos", camera.Position);
    /*
    glm::vec3 position = model_s * glm::vec4(1.0f);
    shader->setVec3("pointLight.position", {0, 2, -1});
    shader->setVec3("pointLight.ambient", pLightColor * p_ambient);
    shader->setVec3("pointLight.diffuse", pLightColor * p_diffuse);
    shader->setVec3("pointLight.specular", pLightColor * p_specular);
    shader->setFloat("pointLight.constant", p_const);
    shader->setFloat("pointLight.linear", p_lin);
    shader->setFloat("pointLight.quadratic", p_qua);
    */

    glm::vec3 dirLightColor = { 1, 1, 0.9f };
    shader->setVec3("dirLight.direction", lightPos);
    shader->setVec3("dirLight.ambient", dirLightColor * 0.2f);
    shader->setVec3("dirLight.diffuse", dirLightColor * 0.5f);
    shader->setVec3("dirLight.specular", dirLightColor * 0.5f);

}

void RenderScene(std::shared_ptr<Shader> shader)
{
    player->render();
    courier->render();

    shader->setInt("texture1", 0);
    shader->setMat4("model", spunkt->get_transform().m_world_matrix);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture1);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    shader->setMat4("model", twod->get_transform().m_world_matrix);
    glBindTexture(GL_TEXTURE_2D, traincubesTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    shader->setMat4("model", twod2->get_transform().m_world_matrix);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void render()
{
    // render
// ------
    glClearColor(0.8f, 0.8f, 1.f, 0.6f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    // activate shader
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    shadowMap->use();
    shadowMap->setMat4("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE1);
    RenderScene(shadowMap);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ourShader->use();

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ourShader->setVec3("color", { 1, 1, 1 });
    ourShader->setMat4("view", view);
    ourShader->setMat4("projection", projection);
    activate_lights(ourShader);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    RenderScene(ourShader);

    debugDepth->use();
    debugDepth->setFloat("near_plane", near_plane);
    debugDepth->setFloat("far_plane", far_plane);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    renderQuad();
    /*
    //ourShader->setMat4("view", model2);
    ourShader->setMat4("model", model2);
    ourShader->setMat4("view", model);
    ourShader->setVec3("pointLight.position", {0, 0, -1});

    glBindTexture(GL_TEXTURE_2D, texture2);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glm::mat4 model5(1.0f);
    model5 = glm::translate(model5, { -0.30, -0.13, 0.0 });
    model5 = glm::scale(model5, { 0.15 * score * 0.001, 0.01 , 1.0 });
    glm::vec3 color;

    if (score < 2000)
    {
        color = { 1, 0, 0 };
    }
    else
    {
        if (score < 2500)
        {
            color = { 1, 1, 0 };
        }
        else
        {
            color = { 0, 1, 0 };
        }
    }
    ourShader->setMat4("model", model5);
    ourShader->setVec3("color", color);
    glBindTexture(GL_TEXTURE_2D, traincubesTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    ourShader->setVec3("color", { 1, 1, 1 });


    glBindVertexArray(0);


    lightSourceShader->use();
    //lightSourceShader->setMat4("view", view);
    lightSourceShader->setMat4("projection", projection);
    //model = glm::scale(glm::mat4(1.0f), { 0.1, 0.1, 0.1 });

    lightSourceShader->setMat4("model",spunkt->get_transform().m_world_matrix);

    lightSourceShader->setVec4("aColor", glm::vec4(pLightColor, 0.0f));

    glBindVertexArray(lightSource_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    */

}

void render_gui()
{
    //GUIShader->use();
    //GUIShader->setMat4("projection", ortho);
    //RenderText(GUIShader, "Score: " + std::to_string(inputManager->getHorizontal()) + " " + std::to_string(inputManager->getVertical()), 10.0f, 60.0f, 0.5f, glm::vec3(1.0, 0.8f, 1.0f));
}

int main()
{
    const char* glsl_version = "#version 460";
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    inputManager = std::make_shared<InputManager>(window);
    colMan = std::make_shared<Collision>();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------

    std::shared_ptr<Model> b = std::make_shared<Model>(Model("res/models/cube/cube.obj"));
    std::shared_ptr<Model> bu = std::make_shared<Model>(Model("res/models/statek/untitled.obj"));
    std::shared_ptr<Model> scene = std::make_shared<Model>(Model("res/models/scene/scene.obj"));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // find the default audio device
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const ALCchar* defaultDeviceString = alcGetString(/*device*/nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
    ALCdevice* device = alcOpenDevice(defaultDeviceString);
    if (!device)
    {
        std::cerr << "failed to get the default device for OpenAL" << std::endl;
        return -1;
    }
    std::cout << "OpenAL Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;
    //OpenAL_ErrorCheck(device);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create an OpenAL audio context from the device
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ALCcontext* context = alcCreateContext(device, /*attrlist*/ nullptr);
    //OpenAL_ErrorCheck(context);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Activate this context so that OpenAL state modifications are applied to the context
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (!alcMakeContextCurrent(context))
    {
        std::cerr << "failed to make the OpenAL context the current context" << std::endl;
        return -1;
    }
    //OpenAL_ErrorCheck("Make context current");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create a listener in 3d space (ie the player); (there always exists as listener, you just configure data on it)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    alec(alListener3f(AL_POSITION, 0.f, 0.f, 0.f));
    alec(alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f));
    ALfloat forwardAndUpVectors[] = {
        /*forward = */ 1.f, 0.f, 0.f,
        /* up = */ 0.f, 1.f, 0.f
    };
    alec(alListenerfv(AL_ORIENTATION, forwardAndUpVectors));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create buffers that hold our sound data; these are shared between contexts and ar defined at a device level
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct ReadWavData
    {
        unsigned int channels = 0;
        unsigned int sampleRate = 0;
        drwav_uint64 totalPCMFrameCount = 0;
        std::vector<uint16_t> pcmData;
        drwav_uint64 getTotalSamples() { return totalPCMFrameCount * channels; }
    };
    ReadWavData monoData;
    {
        drwav_int16* pSampleData = drwav_open_file_and_read_pcm_frames_s16("Sounds/TestSound.wav", &monoData.channels, &monoData.sampleRate, &monoData.totalPCMFrameCount, nullptr);
        if (pSampleData == NULL) {
            std::cerr << "failed to load audio file" << std::endl;
            drwav_free(pSampleData, nullptr); //todo use raii to clean this up
            return -1;
        }
        if (monoData.getTotalSamples() > drwav_uint64(std::numeric_limits<size_t>::max()))
        {
            std::cerr << "too much data in file for 32bit addressed vector" << std::endl;
            drwav_free(pSampleData, nullptr);
            return -1;
        }
        monoData.pcmData.resize(size_t(monoData.getTotalSamples()));
        std::memcpy(monoData.pcmData.data(), pSampleData, monoData.pcmData.size() * /*twobytes_in_s16*/2);
        drwav_free(pSampleData, nullptr);
    }

    ALuint monoSoundBuffer;
    alec(alGenBuffers(1, &monoSoundBuffer));
    alec(alBufferData(monoSoundBuffer, monoData.channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, monoData.pcmData.data(), monoData.pcmData.size() * 2 /*two bytes per sample*/, monoData.sampleRate));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // load a stereo file into a buffer
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ReadWavData stereoData;
    {
        drwav_int16* pSampleData = drwav_open_file_and_read_pcm_frames_s16("Sounds/TestSound.wav", &stereoData.channels, &stereoData.sampleRate, &stereoData.totalPCMFrameCount, nullptr);
        if (pSampleData == NULL) {
            std::cerr << "failed to load audio file" << std::endl;
            return -1;
        }
        if (stereoData.getTotalSamples() > drwav_uint64(std::numeric_limits<size_t>::max()))
        {
            std::cerr << "too much data in file for 32bit addressed vector" << std::endl;
            return -1;
        }
        stereoData.pcmData.resize(size_t(stereoData.getTotalSamples()));
        std::memcpy(stereoData.pcmData.data(), pSampleData, stereoData.pcmData.size() * /*twobytes_in_s15*/2);
        drwav_free(pSampleData, nullptr);
    }

    ALuint stereoSoundBuffer;
    alec(alGenBuffers(1, &stereoSoundBuffer));
    alec(alBufferData(stereoSoundBuffer, stereoData.channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, stereoData.pcmData.data(), stereoData.pcmData.size() * 2 /*two bytes per sample*/, stereoData.sampleRate));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // create a sound source that plays our mono sound (from the sound buffer)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ALuint monoSource;
    alec(alGenSources(1, &monoSource));
    alec(alSource3f(monoSource, AL_POSITION, 1.f, 0.f, 0.f));
    alec(alSource3f(monoSource, AL_VELOCITY, 0.f, 0.f, 0.f));
    alec(alSourcef(monoSource, AL_PITCH, 1.f));
    alec(alSourcef(monoSource, AL_GAIN, 1.f));
    alec(alSourcei(monoSource, AL_LOOPING, AL_FALSE));
    alec(alSourcei(monoSource, AL_BUFFER, monoSoundBuffer));


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // create a sound source for our stereo sound; note 3d positioning doesn't work with stereo files because
    // stereo files are typically used for music. stereo files come out of both ears so it is hard to know
    // what the sound should be doing based on 3d position data.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ALuint stereoSource;
    alec(alGenSources(1, &stereoSource));
    //alec(alSource3f(stereoSource, AL_POSITION, 0.f, 0.f, 1.f)); //NOTE: this does not work like mono sound positions!
    //alec(alSource3f(stereoSource, AL_VELOCITY, 0.f, 0.f, 0.f)); 
    alec(alSourcef(stereoSource, AL_PITCH, 1.f));
    alec(alSourcef(stereoSource, AL_GAIN, 1.f));
    alec(alSourcei(stereoSource, AL_LOOPING, AL_FALSE));
    alec(alSourcei(stereoSource, AL_BUFFER, stereoSoundBuffer));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // play the mono sound source
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    alec(alSourcePlay(monoSource));
    ALint sourceState;
    alec(alGetSourcei(monoSource, AL_SOURCE_STATE, &sourceState));
    //while (sourceState == AL_PLAYING)
   // {
    //    //basically loop until we're done playing the mono sound source
    //    alec(alGetSourcei(monoSource, AL_SOURCE_STATE, &sourceState));
    //}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // play the stereo sound source after the mono!
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    alec(alSourcePlay(stereoSource));
    alec(alGetSourcei(stereoSource, AL_SOURCE_STATE, &sourceState));
    //basically loop until we're done playing the mono sound source

    ////////////////////////////////////////////////////////////////////////////
    // 1. Parse a JSON text string to a document.

    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    printf("Original JSON:\n %s\n", json);

    rapidjson::Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.

    if (document.Parse(json).HasParseError())
        return 1;

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "Fonts/PressStart2P.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return -1;
    }


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    ourShader = std::make_shared<Shader>(Shader("res/shaders/basic.vert", "res/shaders/basic.frag"));
    //lightSourceShader = std::make_shared<Shader>(Shader("res/shaders/lightsource.vert", "res/shaders/lightsource.frag"));
    GUIShader = std::make_shared<Shader>(Shader("res/shaders/GUI.vert", "res/shaders/GUI.frag"));
    shadowMap = std::make_shared<Shader>("res/shaders/shadowmapping.vert", "res/shaders/shadowmapping.frag");
    debugDepth = std::make_shared<Shader>("res/shaders/debugdepth.vert", "res/shaders/debugdepth.frag");
    activate_lights(ourShader);

    model_s = glm::mat4(1.0f);
    model_s = glm::scale(model_s, { 0.1f, 0.1f, 0.1f });

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // Setup Dear ImGui binding
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsDark();

    ourShader->use();
    ourShader->setInt("shadowMap", 1);
    ourShader->setInt("ourTexture", 0);

    debugDepth->use();
    debugDepth->setInt("depthMap", 0);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    ourShader->setMat4("projection", projection);
    //instancedShader->setMat4("projection", projection);
    

    float a = 0;
    bool should_render = false;

    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenVertexArrays(1, &lightSource_VAO);
    glGenBuffers(1, &lightSource_VBO);

    glBindVertexArray(lightSource_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, lightSource_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lights_vertices), lights_vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &GUI_VAO);
    glGenBuffers(1, &GUI_VBO);
    glBindVertexArray(GUI_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, GUI_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(0);

    root = std::make_shared<SceneNode>(SceneNode());
    spunkt = std::make_shared<SceneNode>(SceneNode());
    skier = std::make_shared<SceneNode>(SceneNode());
    twodOrbit = std::make_shared<SceneNode>(SceneNode());
    twod = std::make_shared<SceneNode>(SceneNode());
    twod2 = std::make_shared<SceneNode>(SceneNode());
    //spunkt->set_local_scale({ 0.1, 0.1, 0.1 });
    spunkt->set_local_position({ 0, 0, -2 });
    spunkt->set_local_scale({ 20, 20, 1 });
    twodOrbit->set_local_position({ 0, 0, 0 });
    twodOrbit->set_local_rotation({ 0, 0, 0 });
    twod->set_local_position({ 0, 0, 4 });
    twod2->set_local_position({ 0, 0, -4 });
    twod2->set_local_rotation({ 0, 180, 0 });
    root->add_child(spunkt);
    root->add_child(twodOrbit);
    twodOrbit->add_child(twod);
    twodOrbit->add_child(twod2);


    player = std::make_shared<Player>(inputManager, b, ourShader, colMan);
    courier = std::make_shared<Courier>(bu, ourShader, colMan);
    //player->set_render_AABB(true);
    //courier->set_render_AABB(true);
    //courier->set_color({ 0.6, 0.6, 0.6 });
    root->add_child(player);
    root->add_child(courier);
    player->add_parent(root);
    courier->add_parent(root);
    root->update(root->get_transform(), true);

    camera.player = player;
    camera.courier = courier;
    // load and create a texture 
    // -------------------------
    stbi_set_flip_vertically_on_load(true);
    texture1 = loadTexture(std::string("res/textures/domek.jpg").c_str());
    texture2 = loadTexture(std::string("res/textures/crate.png").c_str());
    traincubesTexture = loadTexture(std::string("res/textures/torus.png").c_str());

    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(-lightPos, glm::vec3(0.0f, 0.f, -0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, { 0, 0, 0 });
    ourShader->setMat4("model", model);

    double last_time = glfwGetTime();
    double unprocessed_time = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        current_time = glfwGetTime();
        passed_time = current_time - last_time;

        last_time = current_time;
        unprocessed_time += passed_time;


        input();

        while (unprocessed_time >= frame_time)
        {
            should_render = true;
            unprocessed_time -= frame_time;

            update(frame_time);
            alec(alGetSourcei(stereoSource, AL_SOURCE_STATE, &sourceState));

        }

        
        if (should_render)
        {
            should_render = false;
            render();
            render_gui();

            glfwPollEvents();
            glfwSwapBuffers(window);
        } 
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteVertexArrays(1, &lightSource_VAO);
    glDeleteBuffers(1, &lightSource_VBO);

    glDeleteVertexArrays(1, &GUI_VAO);
    glDeleteBuffers(1, &GUI_VBO);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // clean up our resources!
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    alec(alDeleteSources(1, &monoSource));
    alec(alDeleteSources(1, &stereoSource));
    alec(alDeleteBuffers(1, &monoSoundBuffer));
    alec(alDeleteBuffers(1, &stereoSoundBuffer));
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}

void processInput(GLFWwindow* window)
{
    //if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        //glfwSetWindowShouldClose(window, true);
    /*
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, passed_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, passed_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, passed_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, passed_time);
    */
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    /*
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
    */
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.ProcessMouseScroll(yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

unsigned int loadCubemap(vector<std::string> faces)
{
    stbi_set_flip_vertically_on_load(false);
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void RenderText(std::shared_ptr<Shader> s, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state	
    s->use();
    glUniform3f(glGetUniformLocation(s->ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(GUI_VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, GUI_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
             0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
             0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f,  0.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
