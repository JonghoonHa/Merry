#pragma once

#include <vector>

using namespace std;

class Expression
{
public:
	Expression(void);
	Expression(char* tName, float* tWeight);
	~Expression(void);

	CString name;
	float weight[16];

};

