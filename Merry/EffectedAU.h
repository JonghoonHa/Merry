#pragma once
#include <gl/glew.h>
#include <gl/wglew.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <algorithm>
#include <vector>

using namespace std;

class EffectedAU
{
public:

	int auNum;
	glm::vec3 moveVector;
	float weight;	
	
	EffectedAU(void);
	~EffectedAU(void);

};

