#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace glm;

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 640, "Star with Texture", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();


    const int numVertices = 10; // Number of vertices for the star
    float star_points[numVertices * 3] = {
        -0.09f, 0.18f, 0.0f, // Vertex 2 (left top)
        0.0f, 0.5f, 0.0f,    // Vertex 1 (top)
        0.09f, 0.18f, 0.0f,   // Vertex 10 (right top)
         0.5f, 0.18f, 0.0f,   // Vertex 9 (right)
        -0.3f, -0.5f, 0.0f,  // Vertex 5 (bottom)
        -0.1f, 0.12f, 0.0f,// Vertex 4 (left bottom)
        -0.5f, 0.18f, 0.0f,  // Vertex 3 (left)
        0.3f, -0.5f, 0.0f,   // Vertex 7 (bottom)
        0.09f, 0.18f, 0.0f,   // Vertex 10 (right top)
        0.3f, -0.5f, 0.0f,   // Vertex 7 (bottom)

       
    };

    // Texture coordinates for the star
    float texture_coords[numVertices *2] = {
    0.5f, 0.0f,  // Texture coordinates for vertex 1 (top)
    0.14f, 0.75f, // Texture coordinates for vertex 4 (left bottom)
    0.25f, 1.0f,  // Texture coordinates for vertex 5 (bottom)
    0.5f, 0.9f,   // Texture coordinates for vertex 6 (right bottom)
    
    1.0f, 0.45f,  // Texture coordinates for vertex 9 (right)
    0.31f, 0.38f, // Texture coordinates for vertex 2 (left top)
    0.75f, 1.0f,  // Texture coordinates for vertex 7 (bottom)
    0.86f, 0.75f, // Texture coordinates for vertex 8 (right bottom)
     
    0.0f, 0.45f,  // Texture coordinates for vertex 3 (left)
    };




    GLuint vbo[2];
    glGenBuffers(2, vbo);
    GLuint points_vbo = vbo[0];
    GLuint texture_vbo = vbo[1];

    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(float), star_points, GL_STATIC_DRAW);

    int texture_width, texture_height, num_channels;
    unsigned char* texture_data = stbi_load("texture.png", &texture_width, &texture_height, &num_channels, 0);
    if (!texture_data) {
        fprintf(stderr, "ERROR: could not load texture image\n");
        return 1;
    }

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
    stbi_image_free(texture_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * numVertices * sizeof(float), texture_coords, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    const char* vertex_shader =
        "#version 330 core\n"
        "in vec3 vertex_position;"
        "in vec2 vertex_texture_coord;"
        "out vec2 texture_coord;"
        "uniform mat4 model;"
        "void main() {"
        "    texture_coord = vertex_texture_coord;"
        "    gl_Position = model * vec4(vertex_position, 1.0);"
        "}";

    const char* fragment_shader =
        "#version 330 core\n"
        "in vec2 texture_coord;"
        "out vec4 frag_colour;"
        "uniform sampler2D texture_sampler;"
        "void main() {"
        "    vec4 tex_colour = texture(texture_sampler, texture_coord);"
        "    frag_colour = tex_colour;"
        "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 model = mat4(1.0f);

        GLuint location = glGetUniformLocation(shader_programme, "model");
        if (location >= 0) {
            glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(model));
        }

        // Activate texture unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glUniform1i(glGetUniformLocation(shader_programme, "texture_sampler"), 0);

        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

