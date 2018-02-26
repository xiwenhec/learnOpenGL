#pragma once
#ifndef RENDER_H
#define RENDER_H
#include"glcommon.h"

#include "vertexData.h"
class Render {
public:
	GLint glProgram;
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	GLint vertexColorLocation;

public:
	void init();
	void draw();
private:
	void CreateGUPProgram();
};


#endif // !RENDER_H
