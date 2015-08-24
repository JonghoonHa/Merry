#include "stdafx.h"
#include "Emotion.h"
#include "ControllerView.h"
#include "MerryView.h"


Emotion::Emotion(void){
	
	Expression temp;
	temp.name = "00. default";
	temp.weight[0] = 0.0;
	temp.weight[1] = 0.0;
	temp.weight[2] = 0.0;
	temp.weight[3]= 0.0;
	temp.weight[4] = 0.0;
	temp.weight[5] = 0.0;
	temp.weight[6] = 0.0;
	temp.weight[7] = 0.0;
	temp.weight[8] = 0.0;
	temp.weight[9] = 0.0;
	temp.weight[10] = 0.0;
	temp.weight[11] = 0.0;
	temp.weight[12] = 0.0;
	temp.weight[13] = 0.0;
	temp.weight[14] = 0.0;
	temp.weight[15] = 0.0;
	saveEmotion(temp);

	temp.name = "���";
	temp.weight[0] = 30.0;
	temp.weight[1] = 0.0;
	temp.weight[2] = 30.0;
	temp.weight[3]= 100.0;
	temp.weight[4] = 60.0;
	temp.weight[5] = 5.0;
	temp.weight[6] = 20.0;
	temp.weight[7] = 0.0;
	temp.weight[8] = 30.0;
	temp.weight[9] = 30.0;
	temp.weight[10] = 0.0;
	temp.weight[11] = 100.0;
	temp.weight[12] = 30.0;
	temp.weight[13] = 0.0;
	temp.weight[14] = 0.0;
	temp.weight[15] = 0.0;
	saveEmotion(temp);

	
}


Emotion::~Emotion(void)
{
}

Expression Emotion::getEmotion(){
	
	// Ư�� ��ȣ(�޺��ڽ����� �����ϸ� index ���� int)�� �ش��ϴ� ǥ���� �����´�.
	// ����ڰ� ������ Button View���� ������ emotion�� index�� ������ emotion[index]�� �ش��ϴ� Expression instance�� ��ȯ�ϴ� �Լ�
	
	CMainFrame* pFrame1 = (CMainFrame *)AfxGetMainWnd();
	pFrame1->m_wndSplitter.SetActivePane(0, 1);
	ControllerView* controller = (ControllerView*)pFrame1->GetActiveView();

	CMainFrame* pFrame2 = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame2->m_wndSplitterSub.GetPane(0, 0);
	
	CString name;
	controller->GetDlgItemText(IDC_COMBO1, name);

	int id;
	for(int i=0;i<pView->emotion.emotions.size();i++){

		if(name == pView->emotion.emotions[i].name){
			id = i;
			break;
		}
	}	

	return pView->emotion.emotions[id];
}

void Emotion::saveEmotion(Expression exp){
	// ���� Expression�� MerryDoc�� emotions�� �߰��Ѵ�.
	// ����ڰ�  Slider Control�� ���Ͽ� ���ϴ� ����ǥ���� ����� �� ��, ADD��ư�� ������, ����ڰ� �Է��� name�� �� ��Ʈ�� ���� value������ Expression�� �ϳ��� instance�� ����� emotion������ �߰�.
	emotions.push_back(exp);
}