#pragma once

#include "Expression.h"
#include "MerryDoc.h"
#include "MainFrm.h"

class Blending
{
public:
	Blending(void);
	Blending(float _speed, int _introBlockNum);
	~Blending(void);

	Expression emotion;
	Expression emotion_withEyeclose;
	Expression pronounciation;

	Expression finalExpression;

	void setEmotion();
	void setPronounciation(void);
	void BlendWithEyeClosed(DWORD diff, vector<float> emotionWeight);
	void blendingFunction(DWORD diff);

private:

	float speed;
	int introBlockNum;

	int eyeClosedOn;
	float eyeStatus;
	DWORD preDiff;
	float w1, w2;
	vector<float> setEmotionWeight(DWORD diff);
};

