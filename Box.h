#pragma once

#include <gl/glew.h>
#include <gl/wglew.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <algorithm>
#include <vector>
#include "EffectedAU.h"

using namespace std;

class Box
{
public:

	GLuint VAO;
	GLuint VBO[2];

	vector <glm::vec3> originalPos;
	vector <glm::vec3> currentPos;
	vector <GLuint> face;
	vector <glm::vec3> m_Normals;
	vector <glm::vec2> texCoord;
	vector<vector<EffectedAU>> pointInfo;

	Box(void);
	~Box(void);
};

