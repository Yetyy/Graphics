#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

GLFWwindow* window;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
    }
}

float points1[] = {
    -0.5f,  0.5f, 0.0f,  // вершина 1
     1.0f,  1.0f, 0.0f,  // цвет вершины 1 (желтый)
     0.5f, -0.5f, 0.0f,  // вершина 2
     0.0f,  1.0f, 0.0f,  // цвет вершины 2 (зелёный)
    -0.5f, -0.5f, 0.0f,  // вершина 3
     1.0f,  0.0f, 0.0f,  // цвет вершины 3 (красный)
};

float points2[] = {
    -0.5f,  0.5f, 0.0f,  // вершина 1
     1.0f,  1.0f, 0.0f,  // цвет вершины 1 (желтый)
     0.5f, -0.5f, 0.0f,  // вершина 2
     0.0f,  1.0f, 0.0f,  // цвет вершины 2 (зелёный)
     0.5f,  0.5f, 0.0f,  // вершина 3
     1.0f,  0.0f, 1.0f   // цвет вершины 3 (фиолетовый)
};

void triang(int test) {
    GLuint vbo = 0;
    GLuint vao = 0;

    const char* vertex_shader =
        "#version 400\n"
        "in vec3 vp;"
        "in vec3 color;"
        "out vec3 vertexColor;"
        "void main() {"
        "  gl_Position = vec4(vp, 1.0);"
        "  vertexColor = color;"
        "}";

    const char* fragment_shader =
        "#version 400\n"
        "in vec3 vertexColor;"
        "out vec4 frag_colour;"
        "void main() {"
        "  frag_colour = vec4(vertexColor, 1.0);"
        "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint shader_programme = glCreateProgram();

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    if (test == 1)
        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points1, GL_STATIC_DRAW);
    else
        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points2, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    glUseProgram(shader_programme);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glfwSetKeyCallback(window, key_callback);
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "GLFW + GLAD", NULL, NULL);

    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        triang(1);
        triang(2);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
