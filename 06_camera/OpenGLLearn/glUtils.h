#ifndef GL_UTILS_H
#define GL_UTILS_H
#include"glcommon.h"

//读取shader的源码
const char* loadFileContent(const char *filePath);

//创建shader
GLint createShader(const char *res, GLuint type);

//创建着色器程序
GLint createProgram(GLint vertexShader, GLint FragmentShader);



#endif // !GL_UTILS_H
