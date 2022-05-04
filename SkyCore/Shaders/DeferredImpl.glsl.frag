#version 450



layout (location = 0) out vec4 Color;
//out vec4 Color;

in vec2 Tex;

uniform sampler2D AlbedoSpec;
uniform sampler2D Normals;
uniform sampler2D WorldPos;



void main()
{
   Color = vec4(texture(AlbedoSpec, Tex).xyz, 1.0f);
   //Color = vec4(1.0f);
}