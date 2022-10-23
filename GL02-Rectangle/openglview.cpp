#include "openglview.h"

OpenGLView::OpenGLView(QWidget *parent)
    : QOpenGLWidget(parent)
    , vao(0)
    , vbo(0)
    , ebo(0)
    , shaderProgram(0)
{
}

OpenGLView::~OpenGLView() {
    if (isValid()) {
        makeCurrent();
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteProgram(shaderProgram);
        doneCurrent();
    }
}

void OpenGLView::initializeGL()
{
    // 初始化 OpenGL 的函数
    initializeOpenGLFunctions();

    // 生成 VAO 和 VBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // 绑定 VAO 和 VBO
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // 顶点数据
    GLfloat vertices[] = {
        -0.5f, 0.5f, 0.0f,  // top-left
        0.5f, 0.5f, 0.0f,   // top-right
        0.5f, -0.5f, 0.0f,  // bottom-right
        -0.5f, -0.5f, 0.0f, // bottom-left
    };
    // 初始 VBO 化数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 告知显示如何解析缓冲里的数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    // 开启 VAO 管理的第一个属性值
    glEnableVertexAttribArray(0);

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

    // 编译顶点着色器
    const GLchar* vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,  &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    // 编译片段着色器
    const GLchar* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
})";
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    // 链接着色器
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 完成编译链接后，删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 设置绘制模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OpenGLView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLView::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
