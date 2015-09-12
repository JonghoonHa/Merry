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
	Expression emotion_withEyeclose;
	Expression pronounciation;
	Expression finalExpression;

	void initialUpdate(float speed, int introBlockNum);
	void setEmotion(void);
	void setPronounciation(void);
	void blendingFunction(DWORD diff);

private:

	float speed;
	int introBlockNum;
	int eyeClosedOn;
	float eyeStatus;
	DWORD preDiff;
	float w1, w2;

	vector<float> setEmotionWeight(DWORD diff);
	void BlendWithEyeClosed(DWORD diff, vector<float> emotionWeight);
	
};

