#include "openglview.h"
#include <QTime>
#include <QDebug>

OpenGLView::OpenGLView(QWidget *parent)
    : QOpenGLWidget(parent)
    , vao(0)
    , vbo(0)
    , ebo(0)
{
}

OpenGLView::~OpenGLView() {
    if (isValid()) {
        makeCurrent();
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        doneCurrent();
    }
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
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top-left red
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-right green
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right blue
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,// bottom-left yellow
    };
    // 初始 VBO 化数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // layout(location = 0) in vec3 aPos;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    // 开启 VAO 管理的第一个属性值
    glEnableVertexAttribArray(0);

    // layout(location = 1) in vec3 aColor;
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    // 开启 VAO 管理的第二个属性值
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

    // 解绑
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 设置绘制模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // 我们声明的顶点属性数量是有上限的，可能通过以下代码获取最大的顶点属性数据是多少
    GLint nAttrs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttrs);
    qDebug() << "nAttrs = " << nAttrs;

    // 通过下面的代码可以获取顶点着色器中的属性位置
    GLuint program = shaderProgram.programId();
    GLint attrLocation = glGetAttribLocation(program, "aPos"); // 也就是 GLSL 中声明的 layout(location=0)
    qDebug() << "posLocation = " << attrLocation;
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
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

