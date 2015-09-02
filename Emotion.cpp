#include "stdafx.h"
#include "Emotion.h"
#include "ControllerView.h"
#include "MerryView.h"


Emotion::Emotion(void){

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

}


Emotion::~Emotion(void)
{
}

Expression Emotion::getEmotion(){
	
	// Ư�� ��ȣ(�޺��ڽ����� �����ϸ� index ���� int)�� �ش��ϴ� ǥ���� �����´�.
	// ����ڰ� ������ Button View���� ������ emotion�� index�� ������ emotion[index]�� �ش��ϴ� Expression instance�� ��ȯ�ϴ� �Լ�
	
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	ControllerView* controller = (ControllerView*)pFrame->GetActiveView();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	
	int idx = 0;
	CString name;
	controller->GetDlgItemText(IDC_COMBO1, name);

	for(idx=0; idx<pView->emotion.emotions.size(); idx++){

		if(name == pView->emotion.emotions[idx].name)	break;
		
	}

	return pView->emotion.emotions[idx];
}

void Emotion::saveEmotion(Expression exp){
	// ���� Expression�� MerryDoc�� emotions�� �߰��Ѵ�.
	// ����ڰ�  Slider Control�� ���Ͽ� ���ϴ� ����ǥ���� ����� �� ��, ADD��ư�� ������, ����ڰ� �Է��� name�� �� ��Ʈ�� ���� value������ Expression�� �ϳ��� instance�� ����� emotion������ �߰�.
	emotions.push_back(exp);
}

void Emotion::setEmotionAtTime(DWORD diff){
	// �ش� ����(block)�� ��ó�� ǥ�� ���� �ִ��� �Ǵ��Ѵ�.
	// ���� �� ǥ�� �±�(����)�� �ִٸ� ������ �������� ū ǥ�� ���� ������.


}