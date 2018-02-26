#ifndef GL_UTILS_H
#define GL_UTILS_H
#include"glcommon.h"

//��ȡshader��Դ��
const char* loadFileContent(const char *filePath);

//����shader
GLint createShader(const char *res, GLuint type);

//������ɫ������
GLint createProgram(GLint vertexShader, GLint FragmentShader);



#endif // !GL_UTILS_H
