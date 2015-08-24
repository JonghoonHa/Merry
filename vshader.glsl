#version 150 

in vec3 vp;
in vec4 color;
in vec3 vNormal;
in vec2 texCoord;

uniform mat4 proj;
uniform mat4 cam;
uniform mat4 Model;

out vec4 pos;
out vec4 normal;
out vec4 colors2;
out vec2 TexCoord;


void main()
{
	vec4 position = vec4(vp, 1.0);
	colors2 = color;	
	 
	pos = cam * Model * position;
	normal = cam * Model * vec4(vNormal,0.0);

	gl_Position = proj * pos;

	TexCoord = texCoord;
} 