#include "stdafx.h"
#include "Blending.h"
#include "MerryView.h"
#include "ControllerView.h"


Blending::Blending(void)
{
	// 16 = AU의 크기. AU 수가 바뀌면 수정해 주어야 함.
	for(int i=0; i<16; i++){
		emotionWeight.push_back(0.0);
	}
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

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	setEmotionWeight();

	for(int i=0;i<pDoc->units.size();i++){

		// 방향 - 거리 관계 적용
		// 서로 다른 두 AU의 방향 관계가 180도에 가까울수록,
		// Animation 작동시 Emotion에 해당하는 AU의 가중치가 낮아진다.
		if(pronounciation.weight[i] > 0.0){
			for(int j=0;j<pDoc->units.size();j++){

				emotion.weight[j] *= pDoc->directionTable[i][j];
			}
		}
	}

	for(int i=0;i<pDoc->units.size();i++){

		// (입으로부터의 거리) 일반화 과정 적용
		finalExpression.weight[i] = pronounciation.weight[i] * 1.0 + emotion.weight[i] * emotionWeight[i];

	}
}

void Blending::setEmotionWeight(void){

	// 입으로부터 거리에 따른 Emotion Expression의 flat/event형 가중치 변화 적용
	// 입으로부터 멀수록 animation 작동시 flat형 (animation과 무관하게 AU적용)
	// 입과 가까울수록 animation 작동시 event형 (animation보다 낮은 가중치로 AU 적용)

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	for(int i=0; i<pDoc->units.size(); i++){

		if(pView->diff < pView->speaking.speed * (pView->speaking.introBlockNum -1)){

			// 처음 ~ 문장 시작 전 블럭
			emotionWeight[i] = 1.0;
		
		}else if( (pView->diff >= pView->speaking.speed * (pView->speaking.introBlockNum -1))  && (pView->diff < pView->speaking.speed * pView->speaking.introBlockNum)){

			// 말하기 바로 전 블럭
			emotionWeight[i] = 1.0 - abs(((pView->diff - (pView->speaking.introBlockNum-1)* pView->speaking.speed) * (1.0 - pDoc->units[i].distFromMouth)) / pView->speaking.speed);
		

		}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size()) * pView->speaking.speed
			&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed ){

			// 말 끝난 바로 다음 블럭
			emotionWeight[i] = 1.0 - abs(((pView->diff - (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1)* pView->speaking.speed) * (1.0 - pDoc->units[i].distFromMouth)) / pView->speaking.speed);

		}else if(pView->diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed
			&& pView->diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum -1) * pView->speaking.speed){
					
			// 말 끝난 후 블럭 ~ 끝
			emotionWeight[i] = 1.0;

		}else{

			// 말하는 동안
			emotionWeight[i] = pDoc->units[i].distFromMouth;
		}

	}

}