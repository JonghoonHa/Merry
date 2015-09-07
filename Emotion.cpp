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

	//return this->emotions[controller->selectedEmotionIdx];

	return finalExpression;
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

	int currBlockNum = diff/speed, i, j;
	float weight, weightSum = 0.0;

	Expression basicEmotion = this->emotions[controller->selectedEmotionIdx];
	Expression tagEmotion;

	if(currBlockNum >= 0 && currBlockNum < transSentence.size() + introBlockNum*2){
		
		for(i=-3; i<3; i++){ // �ش� ��� ��, �ڷ� �� ĭ���� Ž���Ͽ� ǥ�� �±׸� �˻�
			
			if(currBlockNum+i >= introBlockNum && currBlockNum+i < transSentence.size() + introBlockNum-1){
				
				if(transSentence[currBlockNum-introBlockNum+i+1]<0){

					weight = 0.0;

					// �ð� ��ȭ�� ���� ����ġ ���
					if(i>=0)	weight = (float)diff/(3*speed) - (float)(currBlockNum+i-2)/3;
					else	weight = (float)(-1)*diff/(3*speed) + (float)(currBlockNum+i+4)/3 ;

					weightSum += weight;

					// �˻��� ǥ�� �±׸� ���� tagEmotion ����
					for(j=0; j<pDoc->units.size(); j++)
							tagEmotion.weight[j] += this->emotions[abs(transSentence[currBlockNum-introBlockNum+i+1])].weight[j] * weight;
				
				}

			}
		
		}

		// �⺻ ǥ���� ���� �±� ǥ���� blending
		if(weightSum > 1.0)	weightSum = 1.0;

		for(i=0; i<pDoc->units.size(); i++)
			finalExpression.weight[i] = basicEmotion.weight[i] * (1.0 - weightSum) + tagEmotion.weight[i] * weightSum;

	}

}
