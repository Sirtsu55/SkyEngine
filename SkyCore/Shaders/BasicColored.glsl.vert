#version 450

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTex;

uniform mat4 MVP;
uniform mat4 Transform;

out vec3 Norms;
out vec2 Tex;

void main()
{
	Norms = aNorm;
	Tex = aTex;
	gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}