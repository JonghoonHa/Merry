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

	float emotionWeight_flat;
	float emotionWeight_event;
	vector<float> emotionWeight;

	void setEmotion(void);
	void setPronounciation(void);
	void blendingFunction(void);

private:
	void setEmotionWeight();
};

