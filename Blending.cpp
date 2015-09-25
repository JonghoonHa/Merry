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

void Blending::initialUpdate(float speed, int introBlockNum){

	this->speed = speed;
	this->introBlockNum = introBlockNum;

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

	for(int i=0;i<pDoc->units.size();i++){

		// ���� ���� ����
		// ���� �ٸ� �� AU�� ���� ���谡 180���� ��������,
		// Animation �۵��� Emotion�� �ش��ϴ� AU�� ����ġ�� ��������.

		if(pronounciation.weight[i] > 0.0){

			for(int j=0;j<pDoc->units.size();j++){

				emotion.weight[j] *= pDoc->directionTable[i][j];		
			}

			// ���ϴ� AU�� ��-�Ÿ� model ����
			emotion_withEyeclose.weight[i] = emotion.weight[i] * emotionWeight[i];		
		}else{

			// �� ���ϴ� AU�� ��-�Ÿ� model ������
			emotion_withEyeclose.weight[i] = emotion.weight[i];
		}
	}

	// �������� ȿ��
	BlendWithEyeClosed(diff);

	for (int i = 0;i<pDoc->units.size();i++) {

		finalExpression.weight[i] = pronounciation.weight[i] + emotion_withEyeclose.weight[i];

		if(finalExpression.weight[i] > 100.0)	finalExpression.weight[i] = 100.0;
		else if(finalExpression.weight[i] < 0.0)	finalExpression.weight[i] = 0.0;

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

	for(int i=0; i<pDoc->units.size(); i++){

		emotionWeight.push_back(0.0); // emotionWeight �ʱ�ȭ

		if(diff < speed * (introBlockNum -1)){

			// ó�� ~ ���� ���� �� ��
			emotionWeight[i] = 1.0;
		
		}else if( (diff >= speed * (introBlockNum -1))  && (diff < speed * introBlockNum)){

			// ���ϱ� �ٷ� �� ��
			emotionWeight[i] = 1.0 - abs(((diff - (introBlockNum-1)* speed) * (1.0 - pDoc->units[i].distFromMouth)) / speed);
		

		}else if(diff >= (introBlockNum + pView->speaking.sentence.size()) * speed
			&& diff < (introBlockNum + pView->speaking.sentence.size() + 1) * speed ){

			// �� ���� �ٷ� ���� ��
			emotionWeight[i] = 1.0 - abs(((diff - (introBlockNum + pView->speaking.sentence.size() + 1)* speed) * (1.0 - pDoc->units[i].distFromMouth)) / speed);

		}else if(diff >= (introBlockNum + pView->speaking.sentence.size() + 1) * speed){
					
			// �� ���� �� �� ~ ��
			emotionWeight[i] = 1.0;

		}else{

			// ���ϴ� ����
			emotionWeight[i] = pDoc->units[i].distFromMouth;
		}

	}

	return emotionWeight;
}

void Blending::BlendWithEyeClosed(DWORD diff) {

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

	Expression eyeClosed = pView->emotion.emotions[0];
	
	if (diff - preDiff >= 3000 && eyeClosedOn == 0) {

		eyeClosedOn = 1;	//�������� ȿ�� ����
		eyeStatus = emotion.weight[5];
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


		if (emotion_withEyeclose.weight[5] < emotion.weight[5]) {

			emotion_withEyeclose.weight[5] = emotion.weight[5];
			emotion_withEyeclose.weight[6] = emotion.weight[6];
			eyeClosedOn = 0;

			preDiff = diff;
		}
	}

}