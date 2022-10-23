#include "openglview.h"

OpenGLView::OpenGLView(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

OpenGLView::~OpenGLView()
{
    if (isValid()) {
        glDeleteVertexArrays(2, vao);
        glDeleteBuffers(2, vbo);
        glDeleteProgram(shaderProgram[0]);
        glDeleteProgram(shaderProgram[1]);
    }
}

void OpenGLView::initializeGL()
{
    // 初始化 OpenGL 的函数
    initializeOpenGLFunctions();

    // 左边三角形的顶点数据
    GLfloat leftTriangle[] = {
        -0.4f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.8f, -0.5f, 0.0f,
    };
    // 右边三角形的基点数据
    GLfloat rightTriangle[] = {
        0.4f, 0.5f, 0.0f,
        0.8f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
    };

    // 生成 VAO 和 VBO
    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);

    // 绑定第一个 VAO、 VBO
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    // 初始化左边三角形数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(leftTriangle), leftTriangle, GL_STATIC_DRAW);

    // 告知显示如何解析缓冲里的数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    // 开启第一个VAO 管理的第一个属性
    glEnableVertexAttribArray(0);

    // 绑定第二个 VAO、VBO
    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    // 初始化右边三角数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(rightTriangle), rightTriangle, GL_STATIC_DRAW);
    // 告知显示如何解析缓冲里的数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    // 开启第二个 VAO 管理的第一个属性
    glEnableVertexAttribArray(0);

    // 解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    const GLchar* fragmentShaderSrc1 = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
})";
    GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSrc1, NULL);
    glCompileShader(fragmentShader1);

    // 链接着色器
    shaderProgram[0] = glCreateProgram();
    glAttachShader(shaderProgram[0], vertexShader);
    glAttachShader(shaderProgram[0], fragmentShader1);
    glLinkProgram(shaderProgram[0]);

    const GLchar* fragmentShaderSrc2 = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.8f, 0.2f, 1.0f);
})";
    GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSrc2, NULL);
    glCompileShader(fragmentShader2);

    // 链接着色器
    shaderProgram[1] = glCreateProgram();
    glAttachShader(shaderProgram[1], vertexShader);
    glAttachShader(shaderProgram[1], fragmentShader2);
    glLinkProgram(shaderProgram[1]);

    // 完成编译链接后，删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);
}

void OpenGLView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLView::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 绘制左边的三角形
    glUseProgram(shaderProgram[0]);
    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 绘制右边的三角形
    glUseProgram(shaderProgram[1]);
    glBindVertexArray(vao[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
