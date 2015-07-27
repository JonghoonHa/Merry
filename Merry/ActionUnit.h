#pragma once

#include <gl/glew.h>
#include <gl/wglew.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <algorithm>
#include <vector>

using namespace std;

class ActionUnit
{
public:
	ActionUnit(void);
	~ActionUnit(void);

	int auNum;
	vector <int> actionPoint;
	vector <glm::vec3> moveVector;
	vector <float> distLimit;

};

