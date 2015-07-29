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

	Expression nowLook;
	int introBlockNum;
	int introTime;

	int preIdx, currIdx, nextIdx;
	float preWeight, currWeight, nextWeight;

	
	float speed;

	bool this_condition_end;

	Expression getPronounciation(void);

	void transSentenceToIdx(void);
	int matchPronounciationIdx(char letter);
	void setCharAtTime(DWORD diff);	
	void setWeightAtTime(DWORD diff);
	void calCurrLook(void);

	Speaking(void);
	~Speaking(void);
};

