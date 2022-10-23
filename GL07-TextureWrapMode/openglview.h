#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class OpenGLView : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    OpenGLView(QWidget *parent = nullptr);
    ~OpenGLView();

    void setTextureWrapMode(QOpenGLTexture::WrapMode wrapMode);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture *faceTexture;
};

#endif // OPENGLVIEW_H
