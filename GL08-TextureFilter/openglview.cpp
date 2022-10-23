#include "openglview.h"
#include <QImage>
#include <QDebug>

OpenGLView::OpenGLView(QWidget *parent)
    : QOpenGLWidget(parent)
    , vao(0)
    , vbo(0)
    , ebo(0)
    , faceTexture(nullptr)
{
}

OpenGLView::~OpenGLView() {
    if (isValid()) {
        makeCurrent();
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        delete faceTexture;
        doneCurrent();
    }
}

void OpenGLView::setMinificationFilter(QOpenGLTexture::Filter filter)
{
    qDebug() << filter;
    makeCurrent();
    faceTexture->bind();
    faceTexture->setMinificationFilter(filter);
    faceTexture->release();
    doneCurrent();
    update();
}

void OpenGLView::setMagnificationFilter(QOpenGLTexture::Filter filter)
{
    qDebug() << filter;
    makeCurrent();
    faceTexture->bind();
    faceTexture->setMagnificationFilter(filter);
    faceTexture->release();
    doneCurrent();
    update();
}

void OpenGLView::initializeGL()
{
    // 初始化 OpenGL 的函数
    initializeOpenGLFunctions();

    // 着色器
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shape.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shape.frag");
    bool success = shaderProgram.link();
    if (!success) {
        qCritical() << "Err: " << shaderProgram.log();
    }

    // 生成 VAO 和 VBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // 绑定 VAO 和 VBO
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // 顶点数据
    GLfloat vertices[] = {
        -0.8f, 0.8f, 0.0f, 0.45f, 0.55f,  // top-left
        0.8f, 0.8f, 0.0f, 0.55f, 0.55f,   // top-right
        0.8f, -0.8f, 0.0f, 0.55f, 0.45f,  // bottom-right
        -0.8f, -0.8f, 0.0f, 0.45f, 0.45f, // bottom-left
    };
    // 初始 VBO 化数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const GLint location = 0; // 在顶点着色程序代码中，声明的 aPos 位置是 0, layout (location = 0) in vec3 aPos;
    // 告知显示如何解析缓冲里的数据
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    // 开启 VAO 管理的第一个属性值
    glEnableVertexAttribArray(location);

    // layout (location = 1) in vec3 aTexCoord;
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // 解绑 VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 索引数据
    GLuint indices[] = {
        0, 1, 2,    // 右上角三角形
        0, 2, 3,    // 左下角三角形
    };
    // 生成 EBO
    glGenBuffers(1, &ebo);
    // 绑定 EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // 初始化 EBO 数据
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 加载纹理
    faceTexture = new QOpenGLTexture(QImage(":/images/awesomeface.png").mirrored());
    faceTexture->generateMipMaps();

    shaderProgram.bind();
    shaderProgram.setUniformValue("faceTexture", 0);
    shaderProgram.release();

    // 开启透明
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 解绑
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OpenGLView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLView::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    faceTexture->bind();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
