#include "stdafx.h"
#include "Expression.h"
#include "MainFrm.h"
#include "MerryDoc.h"


Expression::Expression(void)
{
	name = _T("");

	for(int i=0; i<sizeof(weight)/sizeof(float); i++){
		weight[i] = 0.0f;
	}
}

Expression::Expression(char* tName, float* tWeight)
{
	name = tName;

	for(int i=0; i<sizeof(weight)/sizeof(float); i++){
		weight[i] = tWeight[i];
	}
}


Expression::~Expression(void)
{
}
