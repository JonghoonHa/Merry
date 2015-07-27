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
	// Emotion 클래스의 getEmotion()의 반환 값을 인자로 받아와 emotion변수 값으로 설정해주는 함수
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);

	emotion = pView->emotion.getEmotion();
}


void Blending::setPronounciation(void){

	// Speaking 클래스의 getPronounciation()의 반환 값을 인자로 받아와 pronounciation변수 값으로 설정해주는 함수
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);

	pronounciation = pView->speaking.getPronounciation();
}

void Blending::blendingFunction(void){

	// emotion과 pronounciation을 blending시키는 알고리즘을 통해 최종 표정을 결정하여 반환해주는 함수

	CMainFrame* pFrame1 = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame1->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame1->GetActiveDocument();

	//Event형 blending 함수---------------------------------------------------------------------------

	if(pView->diff < pView->speaking.speed){

		// 맨 처음 block 
		emotionWeight_event = - (abs( (float)(pView->diff%(int)pView->speaking.speed) - (pView->speaking.speed) ) * 1.0/(pView->speaking.speed)) + 1.0; // 이 식은 모르겠다!!
		
	}else if( (pView->diff >= pView->speaking.speed) && (pView->diff < pView->speaking.speed * 9) ){

		// 두번 째 block ~ 9번 째 block
		emotionWeight_event = 1.0;
		

	}else if( (pView->diff >= pView->speaking.speed * 9)  && (pView->diff < pView->speaking.speed * 10)){

		// 10번 째 block(?) 왜 열 번째만 따로 관리하지?
		emotionWeight_event = - (abs( (float)(pView->diff%(int)pView->speaking.speed*2)) * 1.0/(pView->speaking.speed*2)) + 1.0;
		

	}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size()) * pView->speaking.speed
		&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed ){

		// 말 끝난 바로 다음 블럭						
		emotionWeight_event = - (abs( (float)(pView->diff%(int)pView->speaking.speed*2)) * 1.0/(pView->speaking.speed*2)) + 1.0;
		
	}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed
		&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum -1) * pView->speaking.speed){
					
		// 말 끝난 후 블럭
		emotionWeight_event = 1.0;
		


	}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum -1) * pView->speaking.speed
		&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum ) * pView->speaking.speed ){
					
		// 맨마지막 블럭
		emotionWeight_event = - (abs( (float)(pView->diff%(int)pView->speaking.speed)) * 1.0/(pView->speaking.speed)) + 1.0;
		

	}else{

		//말하는 동안
		emotionWeight_event = 0.5;

	}


	//flat형 event함수--------------------------------------------------------------------------

	if(pView->diff < pView->speaking.speed){

		// 맨 처음 block 		
		emotionWeight_flat = - (abs( (float)(pView->diff%(int)pView->speaking.speed) - (pView->speaking.speed) ) * 1.0/(pView->speaking.speed)) + 1.0;

	}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum -1) * pView->speaking.speed
		&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum ) * pView->speaking.speed ){
					
		// 맨마지막 블럭
		
		emotionWeight_flat = - (abs( (float)(pView->diff%(int)pView->speaking.speed)) * 1.0/(pView->speaking.speed)) + 1.0;
		

	}else{

		//나머지 블럭	
		emotionWeight_flat = 1.0;

	}




	//////////////////////////////////////////////////////////////////////////////

	for(int i=0;i<pDoc->units.size();i++){

		// 방향 - 거리 관계
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

		// 입 주변 

		if(i>=7 && i<=15){
			//이벤트성 ( 입주변 부분 )
			finalExpression.weight[i] = pronounciation.weight[i] * 1.0 + emotion.weight[i] * emotionWeight_event;
		
		}else{
			//flat성 ( 입제외 부분 )
			finalExpression.weight[i] = pronounciation.weight[i] * 1.0 + emotion.weight[i] * emotionWeight_flat;
		
		}


		/*if(finalExpression.weight[i] >= 1.0){

			finalExpression.weight[i] = 1.0;

		}*/

	}
}
