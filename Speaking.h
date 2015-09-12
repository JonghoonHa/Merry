#pragma once

#include "Expression.h"
#include "MerryDoc.h"
#include "MainFrm.h"
class Speaking
{
public:	
	vector<Expression> pronounciations;
	vector<char> sentence;
	vector<int> transSentence;
	
	void initialUpdate(float speed, int introBlockNum);
	Expression getPronounciation(void);
	void transSentenceToIdx(void);
	int matchPronounciationIdx(char letter);
	void setCharAtTime(DWORD diff);	
	void setWeightAtTime(DWORD diff);
	void calCurrLook(void);

	Speaking(void);
	~Speaking(void);

private:
	int preIdx, currIdx;
	float preWeight, currWeight;
	int introBlockNum;
	float speed;
	bool emotionTagFlag;
	bool this_condition_end;
	Expression nowLook;
};

