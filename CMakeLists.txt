cmake_minimum_required(VERSION 3.16)

project(OpenGLDemo VERSION 0.1 LANGUAGES CXX)

# VAO 和 VAO 的使用
add_subdirectory(GL01-Triangle)

# EBO 的使用
add_subdirectory(GL02-Rectangle)

# 两个 VBO 和 两个 VAO 一起使用
add_subdirectory(GL03-TwoTriangle)

# QOpenGLShaderProgram 的使用
add_subdirectory(GL04-ShaderProgram)

# 多属性使用
add_subdirectory(GL05-ColorfulRectangle)

# 纹理的使用
add_subdirectory(GL06-Texture)

# 纹理环绕方式
add_subdirectory(GL07-TextureWrapMode)

# 纹理过滤方式
add_subdirectory(GL08-TextureFilter)
