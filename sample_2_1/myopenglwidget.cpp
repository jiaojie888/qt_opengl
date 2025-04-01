#include "myopenglwidget.h"

GLuint VAO, VBO, EBO;
GLuint shaderProgram;

float vertices[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};

unsigned int indices[] = {
    0,1,2,
    1,2,3,
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

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    doneCurrent();
}

void MyOpenGLWidget::drawShape(Shape shape)
{
    m_shape = shape;
    update();
}

void MyOpenGLWidget::setWireFrame(bool wireframe)
{
    makeCurrent();
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    update();
    doneCurrent();
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    switch (m_shape) {
    case Rect:
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        break;
    case Triangle:
        glDrawArrays(GL_TRIANGLES, 0, 3);
        break;
    default:
        break;
    }

}
