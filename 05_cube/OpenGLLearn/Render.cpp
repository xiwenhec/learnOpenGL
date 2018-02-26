#pragma once
#include"Render.h"
#include "glcommon.h"
#include "glUtils.h"
#include "vertexData.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#define GLM_FORCE_CXX11 
#include "include\glm\gtc\matrix_transform.hpp"
#include"include\glm\gtc\constants.hpp"
#include"include\glm\gtc\type_ptr.hpp"
void Render::init() {
	CreateGUPProgram();
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};




	//����VAO����
	glGenVertexArrays(1, &VAO);
	//����һ��VBO����
	glGenBuffers(1, &VBO);

	//��VAO
	glBindVertexArray(VAO);
	//��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//���ڴ��еĶ������ݣ����뵽�Կ���
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//��ȡGPU������pos���Ա�����λ��
	int posLocation = glGetAttribLocation(glProgram, "vPos");
	int textureLocation = glGetAttribLocation(glProgram, "vTexCoord");

	//����GPU��ν��ʹ����Կ��е��ڴ�����
	//GL_FLOAT��ʾ���ǣ�GLSL����pos������������ʲô��ɵ���Ȼ�������������
	//vec3��ʾʹ�õ���float�������ݡ�
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(posLocation);

	glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(textureLocation);

	//��󻺳����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




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
	GLubyte *data = stbi_load("E:/github/learnOpengl/05_cube/OpenGLLearn/res/girl.jpg", &width, &height, &nrChannels, 0);
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

	data = stbi_load("E:/github/learnOpengl/05_cube/OpenGLLearn/res/floor.jpg", &width, &height, &nrChannels, 0);
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


	glm::mat4 trans;
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3(1.5f, 1.5f, 1.5f));

	glUseProgram(glProgram);
	transFormMatrixLocation = glGetUniformLocation(glProgram, "transForm");
	glUniformMatrix4fv(transFormMatrixLocation, 1, GL_FALSE, glm::value_ptr(trans));
	glUseProgram(0);


	//��ȡuniform������λ���ǲ���Ҫʹ��program�ģ���������program��ֵ������Ҫ��ʹ��program
	glUseProgram(glProgram);
	// define model matrix
	glm::mat4 model;
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	 modelMatrixLoc = glGetUniformLocation(glProgram, "model");
	glUniformMatrix4fv(modelMatrixLoc,1,GL_FALSE,glm::value_ptr(model));

	int viewMatrixPos = glGetUniformLocation(glProgram, "view");
	glUniformMatrix4fv(viewMatrixPos, 1, GL_FALSE, glm::value_ptr(view));

	int projectionMatrixPos = glGetUniformLocation(glProgram, "projection");
	glUniformMatrix4fv(projectionMatrixPos, 1, GL_FALSE, glm::value_ptr(projection));

	glUseProgram(0);



	glEnable(GL_DEPTH_TEST);
}

void Render::draw() {

	glClearColor(0.2f, 0.3f, 0.3f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);


	glm::mat4 model;
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));


	glUseProgram(glProgram);
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
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