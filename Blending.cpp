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

void Blending::blendingFunction(DWORD diff){

	// emotion�� pronounciation�� blending��Ű�� �˰����� ���� ���� ǥ���� �����Ͽ� ��ȯ���ִ� �Լ�

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	vector<float> emotionWeight = setEmotionWeight(diff);
	float tempFinalExpWeight;

	for(int i=0;i<pDoc->units.size();i++){

		// ���� - �Ÿ� ���� ����
		// ���� �ٸ� �� AU�� ���� ���谡 180���� ��������,
		// Animation �۵��� Emotion�� �ش��ϴ� AU�� ����ġ�� ��������.

		if(pronounciation.weight[i] > 0.0){
			for(int j=i;j<pDoc->units.size();j++)
				emotion.weight[j] *= pDoc->directionTable[i][j];		
		}
	}

	//////////////////////////////////////////////////////////////////////////////

	/*----------------------------
	�������� ȿ�� �ڵ�
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

	// �����κ��� �Ÿ��� ���� Emotion Expression�� flat/event�� ����ġ ��ȭ ����
	// �����κ��� �ּ��� animation �۵��� flat�� (animation�� �����ϰ� AU����)
	// �԰� �������� animation �۵��� event�� (animation���� ���� ����ġ�� AU ����)

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	vector<float> emotionWeight;

	// emotionWeight �ʱ�ȭ
	for(int i=0; i<pDoc->units.size(); i++){
		emotionWeight.push_back(0.0);
	}

	for(int i=0; i<pDoc->units.size(); i++){

		if(diff < pView->speaking.speed * (pView->speaking.introBlockNum -1)){

			// ó�� ~ ���� ���� �� ��
			emotionWeight[i] = 1.0;
		
		}else if( (diff >= pView->speaking.speed * (pView->speaking.introBlockNum -1))  && (diff < pView->speaking.speed * pView->speaking.introBlockNum)){

			// ���ϱ� �ٷ� �� ��
			emotionWeight[i] = 1.0 - abs(((diff - (pView->speaking.introBlockNum-1)* pView->speaking.speed) * (1.0 - pDoc->units[i].distFromMouth)) / pView->speaking.speed);
		

		}else if(diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size()) * pView->speaking.speed
			&& diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed ){

			// �� ���� �ٷ� ���� ��
			emotionWeight[i] = 1.0 - abs(((diff - (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1)* pView->speaking.speed) * (1.0 - pDoc->units[i].distFromMouth)) / pView->speaking.speed);

		}else if(diff >= (pView->speaking.introBlockNum + pView->speaking.sentence.size() + 1) * pView->speaking.speed
			/*&& diff < (pView->speaking.introBlockNum + pView->speaking.sentence.size() + pView->speaking.introBlockNum -1) * pView->speaking.speed*/){
					
			// �� ���� �� �� ~ ��
			emotionWeight[i] = 1.0;

		}else{

			// ���ϴ� ����
			emotionWeight[i] = pDoc->units[i].distFromMouth;
		}

	}

	return emotionWeight;
}

void Blending::BlendWithEyeClosed(DWORD diff, vector<float> emotionWeight) {

	/*

	�������� �ڵ�------------------------------------------

	���� emotionǥ���� eyeclosedǥ���� �ð��� ������ ���� �ֱ������� ����(5�ʸ���)

	eyeStatus = (emotion.weight[]*emotion_event)
	emotion_withEyeclose.weight[] = w1*eyeStatus + w2*eyeclosed.weight[];

	(����)-------------------------------------------------
	(emotion.weight[5]*emotion_event) ���� �����̱� ������,
	�ֱⰡ ���۵Ǵ� ������ (emotion.weight[5]*emotion_event) ���� eyeStatus������ �����Ͽ� ����� ��ȯ.
	��, eyeStatus�� ������ ����ǥ�� emotion.weight[5]�� �뺯�ϴ� ��
	���� eyeClosed.weight[5],[6]���� �׻� 100���� ���

	w1,w2���� ��ȭ���� �������� ȿ�� ����(�ΰ��� ǥ���� ����)

	�׻� ������ ��(weight[5])����

	*/
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	Expression eyeClosed = pView->emotion.emotions[0];

	for (int i = 0;i < pDoc->units.size();i++) {
		emotion_withEyeclose.weight[i] = emotion.weight[i] * emotionWeight[i];
	}

	if (diff - preDiff >= 5000 && eyeClosedOn == 0) {

		eyeClosedOn = 1;	//�������� ȿ�� ����
		eyeStatus = emotion.weight[5] * emotionWeight[5];
	}

	if (eyeClosedOn == 1) {

		//eyeStatus�� �������� ǥ�� ����			
		emotion_withEyeclose.weight[5] = w1*eyeStatus + w2*eyeClosed.weight[5];
		emotion_withEyeclose.weight[6] = w1*eyeStatus + w2*eyeClosed.weight[6];
		w1 -= 0.1;
		w2 += 0.1;

		if (w2 >= 1.0) {
			// �� �߱�� ��ȯ
			emotion_withEyeclose.weight[5] = eyeClosed.weight[5];	//weight���� 1.0�Ѿ ��� 1.0����!
			emotion_withEyeclose.weight[6] = eyeClosed.weight[6];
			eyeClosedOn = 2;
		}

	}
	else if (eyeClosedOn == 2) {

		//�� �߱�
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