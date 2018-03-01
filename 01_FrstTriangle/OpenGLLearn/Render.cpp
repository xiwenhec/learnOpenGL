#pragma once
#include"Render.h"
#include "glcommon.h"
#include "glUtils.h"
#include "vertexData.h"


void Render::init() {
	
	CreateGUPProgram();

	GLfloat vertices[] = {
		0.5f,	0.5f,  0.0f,  1.0f, 0.0f, 0.0f,  // 右上角
		0.5f,	-0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// 右下角
		-0.5f,	-0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// 左下角
	};

	GLuint indices[] = {
		0,1,2
	};



	//创建VAO对象
	glGenVertexArrays(1, &VAO);
	//创建一个VBO对象
	glGenBuffers(1, &VBO);
	//创建EBO
	glGenBuffers(1, &EBO);



	//绑定VAO
	glBindVertexArray(VAO);

	//绑定EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//将内存中的顶点数据，传入到显卡中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//获取GPU程序中pos属性变量的位置
	int posLocation = glGetAttribLocation(glProgram, "vPos");
	int colorLocation = glGetAttribLocation(glProgram, "vColor");
	
	//告诉GPU如何解释传入显卡中的内存数据
	//GL_FLOAT表示的是，GLSL里面pos变量属性是用什么组成的显然，这个变量是用
	//vec3表示使用的是float类型数据。
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(posLocation);

	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(colorLocation);

	//解绑缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//当目标是GL_ELEMENT_ARRAY_BUFFER时，VAO会存储glBindBuffer的调用，因此一定要在
	//解绑VAO之后在解绑EBO的调用，否则配置的EBO无法再VAO里生效
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