#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
out vec4 vertexColor;
void main(){
	gl_Position = vec4(vPos.x,vPos.y,vPos.z,1.0);
	vertexColor = vec4(vColor,1.0);
}