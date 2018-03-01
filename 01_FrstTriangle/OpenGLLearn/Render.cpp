#pragma once
#include"Render.h"
#include "glcommon.h"
#include "glUtils.h"
#include "vertexData.h"


void Render::init() {
	
	CreateGUPProgram();

	GLfloat vertices[] = {
		0.5f,	0.5f,  0.0f,  1.0f, 0.0f, 0.0f,  // ���Ͻ�
		0.5f,	-0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// ���½�
		-0.5f,	-0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// ���½�
	};

	GLuint indices[] = {
		0,1,2
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
	
	//����GPU��ν��ʹ����Կ��е��ڴ�����
	//GL_FLOAT��ʾ���ǣ�GLSL����pos������������ʲô��ɵ���Ȼ�������������
	//vec3��ʾʹ�õ���float�������ݡ�
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(posLocation);

	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(colorLocation);

	//��󻺳����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//��Ŀ����GL_ELEMENT_ARRAY_BUFFERʱ��VAO��洢glBindBuffer�ĵ��ã����һ��Ҫ��
	//���VAO֮���ڽ��EBO�ĵ��ã��������õ�EBO�޷���VAO����Ч
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Render::draw() {

	glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(glProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void *)0);
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