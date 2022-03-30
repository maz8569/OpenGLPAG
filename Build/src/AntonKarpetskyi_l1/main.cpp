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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);
unsigned int loadCubemap(vector<std::string> faces);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 direction;

glm::mat4 view;
glm::mat4 punktLightpos;
unsigned int texture1, texture2, traincubesTexture;

GLFWwindow* window = nullptr;
std::shared_ptr<Shader> ourShader = nullptr;
std::shared_ptr<Shader> lightSourceShader = nullptr;

int fps = 0;

double frame_time = 1.0 / 60.0;
glm::vec3 p_pos = { 1, 0, 1 };
glm::mat4 model_s;

int shinyyy = 32;

float p_const = 1.0f;
float p_lin = 0.09f;
float p_qua = 0.032f;
float p_ambient = 0.3f;
float p_diffuse = 1.0f;
float p_specular = 1.0f;

std::shared_ptr<SceneNode> root = nullptr;
std::shared_ptr<SceneNode> spunkt = nullptr;

unsigned int VBO, VAO;
unsigned int lightSource_VBO, lightSource_VAO;


float vertices[] = {
        -0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,  0.0f, -1.0f,
        
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

glm::vec3 pLightColor(1.0f, 1.0f, 1.0f);
float a = 0.0f;

void input()
{
    processInput(window);
    view = camera.GetViewMatrix();

}

void update(float dt)
{
    ourShader->setMat4("view", view); 
    spunkt->update(root->get_transform(), false);
    model_s = spunkt->get_transform().m_world_matrix;

}



void activate_lights(std::shared_ptr<Shader> shader)
{
    shader->setFloat("shininess", shinyyy);
    shader->setVec3("viewPos", camera.Position);
    glm::vec3 position = model_s * glm::vec4(1.0f);
    shader->setVec3("pointLight.position", position);
    shader->setVec3("pointLight.ambient", pLightColor * p_ambient);
    shader->setVec3("pointLight.diffuse", pLightColor * p_diffuse);
    shader->setVec3("pointLight.specular", pLightColor * p_specular);
    shader->setFloat("pointLight.constant", p_const);
    shader->setFloat("pointLight.linear", p_lin);
    shader->setFloat("pointLight.quadratic", p_qua);

}

void render()
{
    // render
// ------
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    // activate shader
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 model(1.0f);
    glm::mat4 model2(1.0f);
    model = glm::translate(model, { -2.0f, 0.0f, 0.0f });
    model2 = glm::translate(model2, { 2.0f, 0.0f, 0.0f });

    ourShader->use();
    ourShader->setMat4("view", view);
    ourShader->setMat4("projection", projection);
    activate_lights(ourShader);
    ourShader->setInt("texture1", 0);
    ourShader->setMat4("model", model);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    ourShader->setMat4("model", model2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, traincubesTexture);
    
    lightSourceShader->use();
    lightSourceShader->setMat4("view", view);
    lightSourceShader->setMat4("projection", projection);
    //model = glm::scale(glm::mat4(1.0f), { 0.1, 0.1, 0.1 });

    lightSourceShader->setMat4("model",spunkt->get_transform().m_world_matrix);

    lightSourceShader->setVec4("aColor", glm::vec4(pLightColor, 0.0f));

    glBindVertexArray(lightSource_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void render_gui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        ImGui::Begin("hello world");                          // Create a window called "Hello, world!" and append into it.
        if (ImGui::SliderFloat("point light height", &p_height, -2, 2))
        {
            spunkt->set_local_position({ 0, p_height, 0 });
        }
        ImGui::End();
    }
    // Rendering
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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
    ourShader = std::make_shared<Shader>(Shader("../../res/shaders/basic.vert", "../../res/shaders/basic.frag"));
    lightSourceShader = std::make_shared<Shader>(Shader("../../res/shaders/lightsource.vert", "../../res/shaders/lightsource.frag"));
    activate_lights(ourShader);

    model_s = glm::mat4(1.0f);
    model_s = glm::scale(model_s, { 0.1f, 0.1f, 0.1f });

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsDark();

    ourShader->use();
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    ourShader->setMat4("projection", projection);
    //instancedShader->setMat4("projection", projection);
    
    double last_time = glfwGetTime();
    double unprocessed_time = 0.0;
    float a = 0;
    bool should_render = false;

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

    glBindVertexArray(0);

    root = std::make_shared<SceneNode>(SceneNode());
    spunkt = std::make_shared<SceneNode>(SceneNode());
    spunkt->set_local_scale({ 0.1, 0.1, 0.1 });
    spunkt->set_local_position({ 0, 0, 0 });
    root->add_child(spunkt);
    root->update(root->get_transform(), true);

    // load and create a texture 
    // -------------------------
    stbi_set_flip_vertically_on_load(true);
    texture1 = loadTexture(std::string("../../res/textures/domek.jpg").c_str());
    texture2 = loadTexture(std::string("../../res/textures/roof.jpg").c_str());
    traincubesTexture = loadTexture(std::string("../../res/textures/torus.png").c_str());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, { 0, 0, 0 });
    ourShader->setMat4("model", model);
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

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, passed_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, passed_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, passed_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, passed_time);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

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