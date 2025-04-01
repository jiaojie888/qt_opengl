#include "myopenglwidget.h"


GLuint shaderProgram, shaderProgram2;

GLuint VAOs[2], VBOs[2];

// float vertices[] = {
//     -0.9f, -0.5f, 0.0f,
//     -0.0f, -0.5f, 0.0f,
//     -0.45f, 0.5f, 0.0f,

//     0.0f, -0.5f, 0.0f,
//     0.9f, -0.5f, 0.0f,
//     0.45f, 0.5f, 0.0f,
// };

float t1[] = {
    -0.9f, -0.5f, 0.0f,
    -0.0f, -0.5f, 0.0f,
    -0.45f, 0.5f, 0.0f,
};


float t2[] = {
    0.0f, -0.5f, 0.0f,
    0.9f, -0.5f, 0.0f,
    0.45f, 0.5f, 0.0f,
};


const char *vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}

)";

const char *fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

)";

const char *fragmentShaderSource2 = R"(
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}

)";

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(t1), t1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(t2), t2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // check
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }

    // 片段着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    // check
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
    }
    // 片段着色器2
    GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);
    glCompileShader(fragmentShader2);
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    // check
    if(!success) {
        glGetShaderInfoLog(fragmentShader2, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
    }


    // 链接
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
    }

    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    // check
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram2, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}
