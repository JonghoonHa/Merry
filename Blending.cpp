#include "stdafx.h"
#include "Blending.h"
#include "MerryView.h"
#include "ControllerView.h"


Blending::Blending(void)
{
	eyeClosedOn = 0;
	eyeStatus = 0.0f;
	preDiff = 0;

	w1 = 1.0;
	w2 = 0.0;
}


Blending::~Blending(void)
{
}


void Blending::setEmotion()
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

void Blending::blendingFunction(DWORD diff){

	// emotion과 pronounciation을 blending시키는 알고리즘을 통해 최종 표정을 결정하여 반환해주는 함수

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	vector<float> emotionWeight = setEmotionWeight(diff);
	float tempFinalExpWeight;

	for(int i=0;i<pDoc->units.size();i++){

		// 방향 - 거리 관계 적용
		// 서로 다른 두 AU의 방향 관계가 180도에 가까울수록,
		// Animation 작동시 Emotion에 해당하는 AU의 가중치가 낮아진다.

		if(pronounciation.weight[i] > 0.0){
			for(int j=i;j<pDoc->units.size();j++)
				emotion.weight[j] *= pDoc->directionTable[i][j];		
		}
	}

	//////////////////////////////////////////////////////////////////////////////

	/*----------------------------
	눈깜빡임 효과 코드
	---------------------------*/
	BlendWithEyeClosed(diff, emotionWeight);

	//////////////////////////////////////////////////////////////////////////////


	for (int i = 0;i<pDoc->units.size();i++) {

		tempFinalExpWeight = pronounciation.weight[i] * 1.0 + emotion_withEyeclose.weight[i];

		if(tempFinalExpWeight > 100.0)	tempFinalExpWeight = 100.0;
		else if(tempFinalExpWeight < 0.0)	tempFinalExpWeight = 0.0;

		finalExpression.weight[i] = tempFinalExpWeight;
	}
}

vector<float> Blending::setEmotionWeight(DWORD diff){

	// 입으로부터 거리에 따른 Emotion Expression의 flat/event형 가중치 변화 적용
	// 입으로부터 멀수록 animation 작동시 flat형 (animation과 무관하게 AU적용)
	// 입과 가까울수록 animation 작동시 event형 (animation보다 낮은 가중치로 AU 적용)

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	vector<float> emotionWeight;

	// emotionWeight 초기화
	for(int i=0; i<pDoc->units.size(); i++){
		emotionWeight.push_back(0.0);
	}

	for(int i=0; i<pDoc->units.size(); i++){

		if(diff < pView->speaking.speed * (pView->speaking.introBlockNum -1)){

			// 처음 ~ 문장 시작 전 블럭
			emotionWeight[i] = 1.0;
		
		}else if( (diff >= pView->speaking.speed * (pView->speaking.introBlockNum -1))  && (diff < pView->speaking.speed * pView->speaking.introBlockNum)){

			// 말하기 바로 전 블럭
			emotionWeight[i] = 1.0 - abs(((diff - (pView->speaking.introBlockNum-1)* pView->speaking.speed) * (1.0 - pDoc->units[i].distFromMouth)) / pView->speaking.speed);
		

		}else if(diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size()) * pView->speaking.speed
			&& diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed ){

			// 말 끝난 바로 다음 블럭
			emotionWeight[i] = 1.0 - abs(((diff - (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1)* pView->speaking.speed) * (1.0 - pDoc->units[i].distFromMouth)) / pView->speaking.speed);

		}else if(diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed
			/*&& diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum -1) * pView->speaking.speed*/){
					
			// 말 끝난 후 블럭 ~ 끝
			emotionWeight[i] = 1.0;

		}else{

			// 말하는 동안
			emotionWeight[i] = pDoc->units[i].distFromMouth;
		}

	}

	return emotionWeight;
}

void Blending::BlendWithEyeClosed(DWORD diff, vector<float> emotionWeight) {

	/*

	눈깜빡임 코드------------------------------------------

	현재 emotion표정과 eyeclosed표정을 시간이 지남에 따라 주기적으로 블렌딩(5초마다)

	eyeStatus = (emotion.weight[]*emotion_event)
	emotion_withEyeclose.weight[] = w1*eyeStatus + w2*eyeclosed.weight[];

	(설명)-------------------------------------------------
	(emotion.weight[5]*emotion_event) 값이 변수이기 때문에,
	주기가 시작되는 순간의 (emotion.weight[5]*emotion_event) 값을 eyeStatus값으로 저장하여 상수로 변환.
	즉, eyeStatus는 현재의 감정표정 emotion.weight[5]를 대변하는 값
	또한 eyeClosed.weight[5],[6]값은 항상 100으로 상수

	w1,w2값을 변화시켜 눈깜빡임 효과 생성(두가지 표정의 블렌딩)

	항상 오른쪽 눈(weight[5])기준

	*/
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	Expression eyeClosed = pView->emotion.emotions[0];

	for (int i = 0;i < pDoc->units.size();i++) {
		emotion_withEyeclose.weight[i] = emotion.weight[i] * emotionWeight[i];
	}

	if (diff - preDiff >= 5000 && eyeClosedOn == 0) {

		eyeClosedOn = 1;	//눈깜빡임 효과 시작
		eyeStatus = emotion.weight[5] * emotionWeight[5];
	}

	if (eyeClosedOn == 1) {

		//eyeStatus와 눈깜빡임 표정 블렌딩			
		emotion_withEyeclose.weight[5] = w1*eyeStatus + w2*eyeClosed.weight[5];
		emotion_withEyeclose.weight[6] = w1*eyeStatus + w2*eyeClosed.weight[6];
		w1 -= 0.1;
		w2 += 0.1;

		if (w2 >= 1.0) {
			// 눈 뜨기로 전환
			emotion_withEyeclose.weight[5] = eyeClosed.weight[5];	//weight값이 1.0넘어갈 경우 1.0으로!
			emotion_withEyeclose.weight[6] = eyeClosed.weight[6];
			eyeClosedOn = 2;
		}

	}
	else if (eyeClosedOn == 2) {

		//눈 뜨기
		w1 += 0.1;
		w2 -= 0.1;
		emotion_withEyeclose.weight[5] = w1*eyeStatus + w2*eyeClosed.weight[5];
		emotion_withEyeclose.weight[6] = w1*eyeStatus + w2*eyeClosed.weight[6];


		if (emotion_withEyeclose.weight[5] < emotion.weight[5] * emotionWeight[5]) {

			emotion_withEyeclose.weight[5] = emotion.weight[5] * emotionWeight[5];
			emotion_withEyeclose.weight[6] = emotion.weight[6] * emotionWeight[6];
			eyeClosedOn = 0;

			preDiff = diff;
		}
	}

}