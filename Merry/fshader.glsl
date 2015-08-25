#version 150 

in vec4 pos;
in vec4 normal;
in vec4 colors2;
in vec2 TexCoord;

out vec4 fColor;

uniform vec4 lightPosition;
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform float lightShineness;
uniform mat4 cam;
uniform sampler2D tex;

uniform sampler2D skin;
uniform sampler2D rEye;
uniform sampler2D lEye;
uniform sampler2D gum;
uniform sampler2D teeth;

uniform float item;

void main() 
{ 

	vec3 L = normalize((cam*lightPosition - pos).xyz);
    vec3 E = normalize(-pos.xyz);
    vec3 N = normalize(normal.xyz);
	vec3 R = normalize( -reflect(L,N));

	//vec4 ambient = colors2 * lightAmbient;
	vec4 ambient = lightAmbient;

	float kd = max(dot(L,N), 0.0);
	//vec4 diffuse = kd*colors2*lightDiffuse;
	vec4 diffuse = kd*lightDiffuse;

	float Ks = pow( max(dot(R, E), 0.0), lightShineness);
    vec4 specular = Ks * vec4(1.0, 1.0, 1.0, 1.0)*lightSpecular;
	
	if( dot(L, N) < 0.0 ) {
		specular = vec4(0.0, 0.0, 0.0, 1.0);
    } 


	//fColor = ambient+diffuse+specular; //내가 생략시키고
	//fColor = texture(tex, TexCoord);

	fColor = texture(tex, TexCoord) * (ambient+diffuse+specular);//새로 넣음

	fColor.w = 1.0;

	//fColor = vec4 (1.0, 0.0, 0.0, 1.0);
} 