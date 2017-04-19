#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 texInput;
out vec2 texcoord;

uniform mat4 transform;
uniform vec2 texOffset = vec2(0.0,0.0);
uniform vec2 texScale  = vec2(1.0,1.0);

void main()
{
	texcoord = texInput * texScale + texOffset;
	gl_Position = transform * vec4(VertexPosition,1.0);
}