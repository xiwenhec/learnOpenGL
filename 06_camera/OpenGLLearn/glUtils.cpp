#define  _CRT_SECURE_NO_WARNINGS
#include "glUtils.h"
#include"glcommon.h"
const char* loadFileContent(const char* filePath) {
	FILE *fp = fopen(filePath, "rb");
	if (fp) {
		fseek(fp, 0, SEEK_END);
		int len = ftell(fp);
		rewind(fp);
		char *buffer = new char[len +1];
		memset(buffer, 0, len+1);
		fread(buffer, len+1, len, fp);
		fclose(fp);
		return buffer;
	}
	else {
		std::cout << "文件打开失失败，path:" << filePath << std::endl;
	}
}


//创建shader
GLint createShader(const char *res, GLuint type) {
	GLint shader = glCreateShader(type);
	glShaderSource(shader, 1, &res, NULL);
	glCompileShader(shader);
	int success = -1;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "compile shader error\n" << infoLog << std::endl;
		return -1;
	}
	return shader;
}

//创建着色器程序
GLint createProgram(GLint vertexShader, GLint fragmentShader) {
	GLint glProgram = glCreateProgram();
	glAttachShader(glProgram, vertexShader);
	glAttachShader(glProgram, fragmentShader);
	glLinkProgram(glProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(glProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(glProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return glProgram;
}



