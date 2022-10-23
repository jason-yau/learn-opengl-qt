#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class OpenGLView : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    OpenGLView(QWidget *parent = nullptr);
    ~OpenGLView();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    GLuint vao;
    GLuint vbo;
    GLuint shaderProgram;
};

#endif // OPENGLVIEW_H
