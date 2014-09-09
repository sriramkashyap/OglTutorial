#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexColor;
layout(location = 0) out vec3 Color;

uniform float rotation;

vec3 RotateAboutOrigin(vec3 src, float theta)
{
	//Cheap 2d rotation function
	float net_rotation = atan(src.y, src.x) - theta;
	return (vec3(cos(net_rotation), sin(net_rotation), 0.0) * length(src));
}

void main()
{
	Color = VertexColor;
	vec3 final_pos = RotateAboutOrigin(VertexPosition,rotation);
	gl_Position = vec4( final_pos, 1.0 );
}