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
	std::string matchPronounciationIdx(vector<char> word);
	void setCharAtTime(DWORD diff);	
	void setWeightAtTime(DWORD diff);
	void calCurrLook(void);

	/*실제소리*/
	static UINT voice(LPVOID IParam);

	Speaking(void);
	~Speaking(void);

private:
	int preIdx, currIdx;
	float preWeight, currWeight;
	int introBlockNum;
	float speed;
	Expression nowLook;
};

