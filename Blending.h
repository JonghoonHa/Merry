#pragma once

#include "Expression.h"
#include "MerryDoc.h"
#include "MainFrm.h"

class Blending
{
public:
	Blending(void);
	~Blending(void);

	Expression emotion;
	Expression pronounciation;

	Expression finalExpression;

	void setEmotion(void);
	void setPronounciation(void);
	void blendingFunction(void);

private:
	vector<float> setEmotionWeight();
};

