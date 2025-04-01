#include "myopenglwidget.h"

GLuint VAO, VBO, EBO;

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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    bool ok;
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/res/shader/shapes.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/res/shader/shapes.frag");
    ok = shaderProgram.link();
    if(!ok) {
        qDebug() << "ERROR:" << shaderProgram.log();
    }
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    shaderProgram.bind();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

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
