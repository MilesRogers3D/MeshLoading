#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"

#include <iostream>

using namespace glm;

void OnWindowResize(GLFWwindow* window, int width, int height);
void OnTick(GLFWwindow *window);

void LoadModel();

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

const vec3 CAMERA_POS = vec3(0.0F, 0.0F, -1000.0F);

Model* turret;
Shader* shader;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Mesh Loading", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, OnWindowResize);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    LoadModel();

    while (!glfwWindowShouldClose(window))
    {
        OnTick(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        turret->Draw(*shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void LoadModel()
{
    mat4 view = mat4(1.0F);
    view = translate(view, CAMERA_POS);

    mat4 projection = perspective(
            radians(45.0F),
            ((float) WIDTH / (float) HEIGHT),
            0.1F,
            100.0F
    );

    shader = new Shader(
            "assets/shaders/shader.vs",
            "assets/shaders/shader.fs"
    );

    shader->SetMat4("view", view);
    shader->SetMat4("projection", projection);

    turret = new Model("assets/models/sm_turret.fbx");
}

void OnWindowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OnTick(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
