#pragma once

#include "Expression.h"
#include "MerryDoc.h"
#include "MainFrm.h"

class Emotion
{
public:
	Emotion(void);
	Emotion(float _speed, int _introBlockNum);
	~Emotion(void);

	vector<Expression> emotions;
	Expression finalExpression;

	Expression getEmotion();
	void saveEmotion(Expression exp);
	void setEmotionWeightAtTime(DWORD diff, vector<int> transSentence);
	

private:
	float speed;
	int introBlockNum;
	
};

