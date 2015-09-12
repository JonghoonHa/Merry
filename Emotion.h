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
	
	void initialUpdate(float speed, int introBlockNum);
	Expression getEmotion();
	void saveEmotion(Expression exp);
	void setEmotionWeightAtTime(DWORD diff, vector<int> transSentence);
	

private:
	float speed;
	int introBlockNum;
	Expression finalExpression;
	
};

