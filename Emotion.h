#pragma once

#include "Expression.h"
#include "MerryDoc.h"
#include "MainFrm.h"

class Emotion
{
public:
	Emotion(void);
	~Emotion(void);

	vector<Expression> emotions;

	Expression getEmotion(int spkIdx);
	void saveEmotion(Expression exp);

};

