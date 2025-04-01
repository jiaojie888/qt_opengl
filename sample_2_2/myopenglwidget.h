#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>             // GLFW
#include <QOpenGLFunctions_3_3_Core> // GLAD
#include <QOpenGLShaderProgram>

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    enum Shape {None, Rect, Circle, Triangle};

    explicit MyOpenGLWidget(QWidget *parent = nullptr);
    ~MyOpenGLWidget();

    void drawShape(Shape shape);

    void setWireFrame(bool wireframe);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:

private:
    Shape m_shape;
    QOpenGLShaderProgram shaderProgram;
};

#endif // MYOPENGLWIDGET_H
