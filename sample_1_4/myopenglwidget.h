#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>             // GLFW
#include <QOpenGLFunctions_3_3_Core> // GLAD

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:
};

#endif // MYOPENGLWIDGET_H
