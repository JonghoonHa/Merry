#include "stdafx.h"
#include "Emotion.h"
#include "ControllerView.h"
#include "MerryView.h"


Emotion::Emotion(void)
{

	float tWeight0[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	Expression tTemp0("00. 눈감음", tWeight0);
	emotions.push_back(tTemp0);

	float tWeight1[16] = {50.0, 50.0, 0.0, 0.0, 0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	Expression tTemp1("01. 기본", tWeight1);
	emotions.push_back(tTemp1);

	float tWeight2[16] = {100.0, 100.0, 0.0, 0.0, 0.0, 10.0, 10.0, 100.0, 100.0, 30.0, 85.0, 85.0, 35.0, 0.0, 0.0, 0.0};
	Expression tTemp2("02. 미소", tWeight2);
	emotions.push_back(tTemp2);
	
	float tWeight3[16] = {30.0, 0.0, 30.0, 100.0, 60.0, 5.0, 20.0, 0.0, 30.0, 30.0, 0.0, 100.0, 30.0, 0.0, 0.0, 0.0};
	Expression tTemp3("03. 썩소", tWeight3);
	emotions.push_back(tTemp3);

	float tWeight4[16] = {100.0, 100.0, 25.0, 25.0, 60.0, 15.0, 15.0, 100.0, 100.0, 65.0, 100.0, 100.0, 0.0, 0.0, 45.0, 0.0};
	Expression tTemp4("04. 웃음", tWeight4);
	emotions.push_back(tTemp4);

	float tWeight5[16] = {100.0, 100.0, 0.0, 0.0, 100.0, 15.0, 15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 80.0, 65.0, 0.0, 25.0};
	Expression tTemp5("05. 생각", tWeight5);
	emotions.push_back(tTemp5);

	float tWeight6[16] = {25.0, 25.0, 100.0, 100.0, 75.0, 10.0, 10.0, 50.0, 50.0, 100.0, 0.0, 0.0, 75.0, 20.0, 0.0, 30.0};
	Expression tTemp6("06. 분노", tWeight6);
	emotions.push_back(tTemp6);
}

Emotion::~Emotion(void)
{
}

void Emotion::initialUpdate(float speed, int introBlockNum){

	this->speed = speed;
	this->introBlockNum = introBlockNum;

}

Expression Emotion::getEmotion(){
	
	// 특정 번호(콤보박스에서 선택하면 index 값이 int)에 해당하는 표정을 가져온다.
	// 사용자가 선택한 Button View에서 선택한 emotion의 index를 가져와 emotion[index]에 해당하는 Expression instance를 반환하는 함수
	
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	ControllerView* controller = (ControllerView*)pFrame->GetActiveView();

	//return this->emotions[controller->selectedEmotionIdx];

	return finalExpression;
}
 
void Emotion::saveEmotion(Expression exp){
	// 만든 Expression을 MerryDoc의 emotions에 추가한다.
	// 사용자가  Slider Control을 통하여 원하는 감정표정을 만들고 난 후, ADD버튼을 누르면, 사용자가 입력한 name과 각 컨트롤 바의 value값들이 Expression의 하나의 instance로 만들어 emotion변수에 추가.
	
	emotions.push_back(exp);
}

void Emotion::setEmotionWeightAtTime(DWORD diff, vector<int> transSentence){
	// 해당 순간(block)의 근처에 표정 값이 있는지 판단한다.
	// 문장 속 표정 태그(음수)가 있다면 가까이 있을수록 큰 표정 값을 가진다.

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	ControllerView* controller = (ControllerView*)pFrame->GetActiveView();	
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	int currBlockNum = diff/speed, i, j;
	float weight, weightSum = 0.0;

	Expression basicEmotion = this->emotions[controller->selectedEmotionIdx];
	Expression tagEmotion;

	if(currBlockNum >= 0 && currBlockNum < transSentence.size() + introBlockNum*2){
		
		for(i=-3; i<3; i++){ // 해당 블록 앞, 뒤로 세 칸까지 탐색하여 표정 태그를 검색
			
			if(currBlockNum+i >= introBlockNum && currBlockNum+i < transSentence.size() + introBlockNum-1){
				
				if(transSentence[currBlockNum-introBlockNum+i+1]<0){

					weight = 0.0;

					// 시간 변화에 따른 가중치 계산
					if(i>=0)	weight = (float)diff/(3*speed) - (float)(currBlockNum+i-2)/3;
					else	weight = (float)(-1)*diff/(3*speed) + (float)(currBlockNum+i+4)/3 ;

					weightSum += weight;

					// 검색한 표정 태그를 합쳐 tagEmotion 생성
					for(j=0; j<pDoc->units.size(); j++)
							tagEmotion.weight[j] += this->emotions[abs(transSentence[currBlockNum-introBlockNum+i+1])].weight[j] * weight;
				
				}

			}
		
		}

		// 기본 표정과 문장 태그 표정의 blending
		if(weightSum > 1.0)	weightSum = 1.0;

		for(i=0; i<pDoc->units.size(); i++)
			finalExpression.weight[i] = basicEmotion.weight[i] * (1.0 - weightSum) + tagEmotion.weight[i] * weightSum;

	}

}
