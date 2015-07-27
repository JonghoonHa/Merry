#include "stdafx.h"
#include "Blending.h"
#include "MerryView.h"
#include "ControllerView.h"


Blending::Blending(void)
{
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

	CMainFrame* pFrame1 = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame1->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame1->GetActiveDocument();

	//Event�� blending �Լ�---------------------------------------------------------------------------

	if(pView->diff < pView->speaking.speed){

		// �� ó�� block 
		emotionWeight_event = - (abs( (float)(pView->diff%(int)pView->speaking.speed) - (pView->speaking.speed) ) * 1.0/(pView->speaking.speed)) + 1.0; // �� ���� �𸣰ڴ�!!
		
	}else if( (pView->diff >= pView->speaking.speed) && (pView->diff < pView->speaking.speed * 9) ){

		// �ι� ° block ~ 9�� ° block
		emotionWeight_event = 1.0;
		

	}else if( (pView->diff >= pView->speaking.speed * 9)  && (pView->diff < pView->speaking.speed * 10)){

		// 10�� ° block(?) �� �� ��°�� ���� ��������?
		emotionWeight_event = - (abs( (float)(pView->diff%(int)pView->speaking.speed*2)) * 1.0/(pView->speaking.speed*2)) + 1.0;
		

	}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size()) * pView->speaking.speed
		&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed ){

		// �� ���� �ٷ� ���� ��						
		emotionWeight_event = - (abs( (float)(pView->diff%(int)pView->speaking.speed*2)) * 1.0/(pView->speaking.speed*2)) + 1.0;
		
	}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed
		&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum -1) * pView->speaking.speed){
					
		// �� ���� �� ��
		emotionWeight_event = 1.0;
		


	}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum -1) * pView->speaking.speed
		&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum ) * pView->speaking.speed ){
					
		// �Ǹ����� ��
		emotionWeight_event = - (abs( (float)(pView->diff%(int)pView->speaking.speed)) * 1.0/(pView->speaking.speed)) + 1.0;
		

	}else{

		//���ϴ� ����
		emotionWeight_event = 0.5;

	}


	//flat�� event�Լ�--------------------------------------------------------------------------

	if(pView->diff < pView->speaking.speed){

		// �� ó�� block 		
		emotionWeight_flat = - (abs( (float)(pView->diff%(int)pView->speaking.speed) - (pView->speaking.speed) ) * 1.0/(pView->speaking.speed)) + 1.0;

	}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum -1) * pView->speaking.speed
		&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum ) * pView->speaking.speed ){
					
		// �Ǹ����� ��
		
		emotionWeight_flat = - (abs( (float)(pView->diff%(int)pView->speaking.speed)) * 1.0/(pView->speaking.speed)) + 1.0;
		

	}else{

		//������ ��	
		emotionWeight_flat = 1.0;

	}




	//////////////////////////////////////////////////////////////////////////////

	for(int i=0;i<pDoc->units.size();i++){

		// ���� - �Ÿ� ����
		if(pronounciation.weight[i] > 0.0){
			for(int j=0;j<pDoc->units.size();j++){
				if(i == 13){
					printf("");
				}
				emotion.weight[j] *= pDoc->directionTable[i][j];
			}
		}
	}

	for(int i=0;i<pDoc->units.size();i++){

		// �� �ֺ� 

		if(i>=7 && i<=15){
			//�̺�Ʈ�� ( ���ֺ� �κ� )
			finalExpression.weight[i] = pronounciation.weight[i] * 1.0 + emotion.weight[i] * emotionWeight_event;
		
		}else{
			//flat�� ( ������ �κ� )
			finalExpression.weight[i] = pronounciation.weight[i] * 1.0 + emotion.weight[i] * emotionWeight_flat;
		
		}


		/*if(finalExpression.weight[i] >= 1.0){

			finalExpression.weight[i] = 1.0;

		}*/

	}
}
