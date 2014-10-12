#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec3 VertexColor;
layout(location = 3) in vec2 VertexTexcoord;

out vec3 worldpos;
out vec3 worldnormal;
out vec3 color;
out vec2 texcoord;

uniform mat4 transform;

void main()
{
	worldpos	= VertexPosition;
	worldnormal = VertexNormal;
	color		= VertexColor;
	texcoord	= VertexTexcoord;

	gl_Position = transform * vec4(VertexPosition,1.0);
}