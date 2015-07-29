#include "stdafx.h"
#include "Expression.h"
#include "MainFrm.h"
#include "MerryDoc.h"


Expression::Expression(void)
{
	name = _T("");

	for(int i=0; i<sizeof(weight)/sizeof(weight[0]); i++){
		weight[i] = 0.0f;
	}
}


Expression::~Expression(void)
{
}
