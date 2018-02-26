#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoord;

out vec4 vertexColor;
out vec2 texCoord;
uniform mat4 transForm;
void main(){
	gl_Position = transForm * vec4(vPos,1.0);
	vertexColor = vec4(vColor,1.0);
	texCoord = vec2(vTexCoord.x,1.0-vTexCoord.y);
}