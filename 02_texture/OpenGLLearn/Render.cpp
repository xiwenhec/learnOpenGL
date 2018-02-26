#pragma once

#include"Render.h"
#include "glcommon.h"
#include "glUtils.h"
#include "vertexData.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

void Render::init() {
	
	CreateGUPProgram();

	float vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // ����
	};

	GLuint indices[] = {
		0,1,3,
		1,2,3
	};

	GLfloat texCoords[] = {
		1.0f,1.0f,
		1.0f,-1.0f,
		0.0f,0.0f
	};


	//����VAO����
	glGenVertexArrays(1, &VAO);
	//����һ��VBO����
	glGenBuffers(1, &VBO);
	//����EBO
	glGenBuffers(1, &EBO);


	//��VAO
	glBindVertexArray(VAO);
	//��EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//���ڴ��еĶ������ݣ����뵽�Կ���
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//��ȡGPU������pos���Ա�����λ��
	int posLocation = glGetAttribLocation(glProgram, "vPos");
	int colorLocation = glGetAttribLocation(glProgram, "vColor");
	int textureLocation = glGetAttribLocation(glProgram, "vTexCoord");

	//����GPU��ν��ʹ����Կ��е��ڴ�����
	//GL_FLOAT��ʾ���ǣ�GLSL����pos������������ʲô��ɵ���Ȼ�������������
	//vec3��ʾʹ�õ���float�������ݡ�
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(posLocation);

	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(colorLocation);

	glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(textureLocation);

	//��󻺳����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//��Ŀ����GL_ELEMENT_ARRAY_BUFFERʱ��VAO��洢glBindBuffer�ĵ��ã����һ��Ҫ��
	//���VAO֮���ڽ��EBO�ĵ��ã��������õ�EBO�޷���VAO����Ч
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	//--------------------texture--------------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	//���û��Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//���ù��˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	GLubyte *data = stbi_load("E:/study/C++/vs/02����/OpenGLLearn/res/girl.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "faile load texture" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	data = stbi_load("E:/study/C++/vs/02����/OpenGLLearn/res/floor.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB,GL_UNSIGNED_BYTE,data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "texture2 failed load " << std::endl;
	}
	stbi_image_free(data);
	GLuint texture1Loacaton = glGetUniformLocation(glProgram, "texture1");
	GLuint texture2Loacaton = glGetUniformLocation(glProgram, "texture2");
	glUseProgram(glProgram);
	glUniform1i(texture1Loacaton, 0);
	glUniform1i(texture2Loacaton, 1);
	glUseProgram(0);

}

void Render::draw() {

	glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUseProgram(glProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
	glBindVertexArray(0);
	glUseProgram(0);
}


void Render::CreateGUPProgram() {
	const char *vertexShaderRes = loadFileContent("vertex.vs");
	const char *fragmentShaderRes = loadFileContent("fragment.fs");
	GLint vertextShader = createShader(vertexShaderRes, GL_VERTEX_SHADER);
	GLint fragmentShader = createShader(fragmentShaderRes, GL_FRAGMENT_SHADER);
	if (vertextShader == -1 || fragmentShader == -1) {
		std::cout << "get shader error" << std::endl;
		return;
	}
	glProgram = createProgram(vertextShader, fragmentShader);
	if (glProgram == -1) {
		return;
	}
}