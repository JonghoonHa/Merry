#include "stdafx.h"
#include "Emotion.h"
#include "ControllerView.h"
#include "MerryView.h"


Emotion::Emotion(void){

	float tWeight0[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	Expression tTemp0("00. 눈감음", tWeight0);
	emotions.push_back(tTemp0);

	float tWeight1[16] = {50.0, 50.0, 0.0, 0.0, 0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	Expression tTemp1("01. default", tWeight1);
	emotions.push_back(tTemp1);

	float tWeight2[16] = {30.0, 0.0, 30.0, 100.0, 60.0, 5.0, 20.0, 0.0, 30.0, 30.0, 0.0, 100.0, 30.0, 0.0, 0.0, 0.0};
	Expression tTemp2("02. 썩소", tWeight2);
	emotions.push_back(tTemp2);

	float tWeight3[16] = {100.0, 100.0, 0.0, 0.0, 100.0, 15.0, 15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 80.0, 65.0, 0.0, 25.0};
	Expression tTemp3("03. 생각", tWeight3);
	emotions.push_back(tTemp3);

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
	
	int idx = 0;
	CString name;
	controller->GetDlgItemText(IDC_COMBO1, name);

	for(idx=0; idx<pView->emotion.emotions.size(); idx++){

		if(name == pView->emotion.emotions[idx].name)	break;
		
	}

	return pView->emotion.emotions[idx];
}

void Emotion::saveEmotion(Expression exp){
	// 만든 Expression을 MerryDoc의 emotions에 추가한다.
	// 사용자가  Slider Control을 통하여 원하는 감정표정을 만들고 난 후, ADD버튼을 누르면, 사용자가 입력한 name과 각 컨트롤 바의 value값들이 Expression의 하나의 instance로 만들어 emotion변수에 추가.
	emotions.push_back(exp);
}

void Emotion::setEmotionAtTime(DWORD diff){
	// 해당 순간(block)의 근처에 표정 값이 있는지 판단한다.
	// 문장 속 표정 태그(음수)가 있다면 가까이 있을수록 큰 표정 값을 가진다.


}