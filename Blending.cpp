#include "stdafx.h"
#include "Blending.h"
#include "MerryView.h"
#include "ControllerView.h"


Blending::Blending(void)
{
	// 16 = AU�� ũ��. AU ���� �ٲ�� ������ �־�� ��.
	for(int i=0; i<16; i++){
		emotionWeight.push_back(0.0);
	}
}


Blending::~Blending(void)
{
}


void Blending::setEmotion(void)
{
	// Emotion Ŭ������ getEmotion()�� ��ȯ ���� ���ڷ� �޾ƿ� emotion���� ������ �������ִ� �Լ�
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);

	emotion = pView->emotion.getEmotion();
}


void Blending::setPronounciation(void){

	// Speaking Ŭ������ getPronounciation()�� ��ȯ ���� ���ڷ� �޾ƿ� pronounciation���� ������ �������ִ� �Լ�
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);

	pronounciation = pView->speaking.getPronounciation();
}

void Blending::blendingFunction(void){

	// emotion�� pronounciation�� blending��Ű�� �˰����� ���� ���� ǥ���� �����Ͽ� ��ȯ���ִ� �Լ�

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	setEmotionWeight();

	for(int i=0;i<pDoc->units.size();i++){

		// ���� - �Ÿ� ���� ����
		// ���� �ٸ� �� AU�� ���� ���谡 180���� ��������,
		// Animation �۵��� Emotion�� �ش��ϴ� AU�� ����ġ�� ��������.
		if(pronounciation.weight[i] > 0.0){
			for(int j=0;j<pDoc->units.size();j++){

				emotion.weight[j] *= pDoc->directionTable[i][j];
			}
		}
	}

	for(int i=0;i<pDoc->units.size();i++){

		// (�����κ����� �Ÿ�) �Ϲ�ȭ ���� ����
		finalExpression.weight[i] = pronounciation.weight[i] * 1.0 + emotion.weight[i] * emotionWeight[i];

	}
}

void Blending::setEmotionWeight(void){

	// �����κ��� �Ÿ��� ���� Emotion Expression�� flat/event�� ����ġ ��ȭ ����
	// �����κ��� �ּ��� animation �۵��� flat�� (animation�� �����ϰ� AU����)
	// �԰� �������� animation �۵��� event�� (animation���� ���� ����ġ�� AU ����)

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	for(int i=0; i<pDoc->units.size(); i++){

		if(pView->diff < pView->speaking.speed * (pView->speaking.introBlockNum -1)){

			// ó�� ~ ���� ���� �� ��
			emotionWeight[i] = 1.0;
		
		}else if( (pView->diff >= pView->speaking.speed * (pView->speaking.introBlockNum -1))  && (pView->diff < pView->speaking.speed * pView->speaking.introBlockNum)){

			// ���ϱ� �ٷ� �� ��
			emotionWeight[i] = 1.0 - abs(((pView->diff - (pView->speaking.introBlockNum-1)* pView->speaking.speed) * (1.0 - pDoc->units[i].distFromMouth)) / pView->speaking.speed);
		

		}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size()) * pView->speaking.speed
			&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed ){

			// �� ���� �ٷ� ���� ��
			emotionWeight[i] = 1.0 - abs(((pView->diff - (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1)* pView->speaking.speed) * (1.0 - pDoc->units[i].distFromMouth)) / pView->speaking.speed);

		}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed
			&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum -1) * pView->speaking.speed){
					
			// �� ���� �� �� ~ ��
			emotionWeight[i] = 1.0;

		}else{

			// ���ϴ� ����
			emotionWeight[i] = pDoc->units[i].distFromMouth;
		}

	}

}