#version 450

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;



in vec3 Norms;
in vec2 Tex;
uniform vec3 Color;
uniform sampler2D AlbedoTex;





void main()
{
   //gAlbedoSpec = vec4(1.0f);
   gAlbedoSpec.rgb = texture(AlbedoTex, Tex).rgb;
   gAlbedoSpec.a = 1.0f;
   gNormal = vec3(1.0f);
}