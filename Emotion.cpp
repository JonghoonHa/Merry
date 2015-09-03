#include "stdafx.h"
#include "Emotion.h"
#include "ControllerView.h"
#include "MerryView.h"


Emotion::Emotion(void)
{
}

Emotion::Emotion(float _speed, int _introBlockNum){

	float tWeight0[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	Expression tTemp0("00. ������", tWeight0);
	emotions.push_back(tTemp0);

	float tWeight1[16] = {50.0, 50.0, 0.0, 0.0, 0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	Expression tTemp1("01. default", tWeight1);
	emotions.push_back(tTemp1);

	float tWeight2[16] = {30.0, 0.0, 30.0, 100.0, 60.0, 5.0, 20.0, 0.0, 30.0, 30.0, 0.0, 100.0, 30.0, 0.0, 0.0, 0.0};
	Expression tTemp2("02. ���", tWeight2);
	emotions.push_back(tTemp2);

	float tWeight3[16] = {100.0, 100.0, 0.0, 0.0, 100.0, 15.0, 15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 80.0, 65.0, 0.0, 25.0};
	Expression tTemp3("03. ����", tWeight3);
	emotions.push_back(tTemp3);

	speed = _speed;
	introBlockNum = _introBlockNum;

}

Emotion::~Emotion(void)
{
}

Expression Emotion::getEmotion(){
	
	// Ư�� ��ȣ(�޺��ڽ����� �����ϸ� index ���� int)�� �ش��ϴ� ǥ���� �����´�.
	// ����ڰ� ������ Button View���� ������ emotion�� index�� ������ emotion[index]�� �ش��ϴ� Expression instance�� ��ȯ�ϴ� �Լ�
	
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	ControllerView* controller = (ControllerView*)pFrame->GetActiveView();

	return this->emotions[controller->selectedEmotionIdx];
}
 
void Emotion::saveEmotion(Expression exp){
	// ���� Expression�� MerryDoc�� emotions�� �߰��Ѵ�.
	// ����ڰ�  Slider Control�� ���Ͽ� ���ϴ� ����ǥ���� ����� �� ��, ADD��ư�� ������, ����ڰ� �Է��� name�� �� ��Ʈ�� ���� value������ Expression�� �ϳ��� instance�� ����� emotion������ �߰�.
	
	emotions.push_back(exp);
}

void Emotion::setEmotionWeightAtTime(DWORD diff, vector<int> transSentence){
	// �ش� ����(block)�� ��ó�� ǥ�� ���� �ִ��� �Ǵ��Ѵ�.
	// ���� �� ǥ�� �±�(����)�� �ִٸ� ������ �������� ū ǥ�� ���� ������.

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	ControllerView* controller = (ControllerView*)pFrame->GetActiveView();	
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	int currBlockNum = diff/speed-1;
	float weight = 0.0;

	//Expression basicEmotion = this->emotions[controller->selectedEmotionIdx];
	Expression tagEmotion;

	if(currBlockNum >= introBlockNum && currBlockNum < transSentence.size() + introBlockNum*2){

		for(int i=currBlockNum-2; i<=currBlockNum+2; i++){
	
			if(i-introBlockNum >=0 && transSentence[i-introBlockNum] < 0){

				if(i <= currBlockNum)	weight = (diff - i*speed) / (2*speed);
				else	weight = (diff - (i+4)*speed) / ((-2)*speed);
			
				for(int j=0; j<pDoc->units.size(); j++)
					tagEmotion.weight[j] += this->emotions[abs(transSentence[i-introBlockNum])].weight[j] * weight;
			}

		}

	}

}
