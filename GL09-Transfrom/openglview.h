#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>

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
    GLuint ebo;
//    GLuint shaderProgram;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture *wallTexture;
    QOpenGLTexture *faceTexture;

    // 旋转矩阵
    QMatrix4x4 tranMatrix;
};

#endif // OPENGLVIEW_H
