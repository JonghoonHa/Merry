#include "stdafx.h"
#include "Emotion.h"
#include "ControllerView.h"
#include "MerryView.h"


Emotion::Emotion(void){
	
	Expression temp;
	temp.name = "00. default";
	temp.weight[0] = 50.0;
	temp.weight[1] = 50.0;
	temp.weight[5] = 10.0;
	temp.weight[6] = 10.0;
	saveEmotion(temp);

	temp.name = "01. 썩쏘";
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

	temp.name = "02. 생각중";
	temp.weight[0] = 100.0;
	temp.weight[1] = 100.0;
	temp.weight[2] = 0.0;
	temp.weight[3] = 0.0;
	temp.weight[4] = 100.0;
	temp.weight[5] = 15.0;
	temp.weight[6] = 15.0;
	temp.weight[7] = 0.0;
	temp.weight[8] = 0.0;
	temp.weight[9] = 0.0;
	temp.weight[10] = 0.0;
	temp.weight[11] = 0.0;
	temp.weight[12] = 80.0;
	temp.weight[13] = 65.0;
	temp.weight[14] = 0.0;
	temp.weight[15] = 25.0;
	saveEmotion(temp);

}


Emotion::~Emotion(void)
{
}

Expression Emotion::getEmotion(){
	
	// 특정 번호(콤보박스에서 선택하면 index 값이 int)에 해당하는 표정을 가져온다.
	// 사용자가 선택한 Button View에서 선택한 emotion의 index를 가져와 emotion[index]에 해당하는 Expression instance를 반환하는 함수
	
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	ControllerView* controller = (ControllerView*)pFrame->GetActiveView();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	
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
	// 만든 Expression을 MerryDoc의 emotions에 추가한다.
	// 사용자가  Slider Control을 통하여 원하는 감정표정을 만들고 난 후, ADD버튼을 누르면, 사용자가 입력한 name과 각 컨트롤 바의 value값들이 Expression의 하나의 instance로 만들어 emotion변수에 추가.
	emotions.push_back(exp);
}