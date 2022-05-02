#version 450

in vec3 Norms;
in vec2 Tex;
out vec4 col;
uniform vec3 Color;
uniform sampler2D AlbedoTex;

void main()
{
   col = texture(AlbedoTex, Tex);
}