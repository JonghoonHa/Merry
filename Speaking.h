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
	
	int preIdx, currIdx, nextIdx;
	float preWeight, currWeight, nextWeight;

	

	//bool this_condition_end;

	Expression getPronounciation(void);

	void transSentenceToIdx(void);
	std::string matchPronounciationIdx(vector<char> word);
	void setCharAtTime(DWORD diff);	
	void setWeightAtTime(DWORD diff);
	void calCurrLook(void);

	/*실제소리*/	
	static UINT voice(LPVOID IParam);

	Speaking(void);
	Speaking(float _speed, int _introBlockNum);
	~Speaking(void);

private:
	int introBlockNum;
	float speed;
};

