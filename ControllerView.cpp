// ControllerView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Merry.h"
#include "ControllerView.h"
#include "SaveExpressionDlg.h"
#include <string>
#include <string.h>




// ControllerView

IMPLEMENT_DYNCREATE(ControllerView, CFormView)

ControllerView::ControllerView()
	: CFormView(ControllerView::IDD)
{

}

ControllerView::~ControllerView()
{
}

void ControllerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SLIDER1, innerBrowRaiserR);
	DDX_Control(pDX, IDC_SLIDER2, innerBrowRaiserL);
	DDX_Control(pDX, IDC_SLIDER3, outerBrowRaiserR);
	DDX_Control(pDX, IDC_SLIDER4, outerBrowRaiserL);
	DDX_Control(pDX, IDC_SLIDER5, browLowerer);
	DDX_Control(pDX, IDC_SLIDER6, eyeCloseR);
	DDX_Control(pDX, IDC_SLIDER7, eyeCloseL);
	DDX_Control(pDX, IDC_SLIDER8, cheekRaiserR);
	DDX_Control(pDX, IDC_SLIDER9, cheekRaiserL);
	DDX_Control(pDX, IDC_SLIDER10, noseWrinkler);
	DDX_Control(pDX, IDC_SLIDER11, lipCornerPullerR);
	DDX_Control(pDX, IDC_SLIDER12, lipCornerPullerL);
	DDX_Control(pDX, IDC_SLIDER13, chinRaiser);
	DDX_Control(pDX, IDC_SLIDER14, lipPuckerer);
	DDX_Control(pDX, IDC_SLIDER15, lipsPart);
	DDX_Control(pDX, IDC_SLIDER16, stickOutLowerLip);
	DDX_Control(pDX, IDC_COMBO1, expressionList);


	
}

BEGIN_MESSAGE_MAP(ControllerView, CFormView)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &ControllerView::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ControllerView::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// ControllerView �����Դϴ�.

#ifdef _DEBUG
void ControllerView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ControllerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ControllerView �޽��� ó�����Դϴ�.


void ControllerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	innerBrowRaiserR.SetRange(0,100);	//slider ��ü ũ��
	innerBrowRaiserR.SetPos(0);		//slider �ʱ� ��ġ

	innerBrowRaiserL.SetRange(0,100);
	innerBrowRaiserL.SetPos(0);

	outerBrowRaiserR.SetRange(0, 100);
	outerBrowRaiserR.SetPos(0);

	outerBrowRaiserL.SetRange(0, 100);
	outerBrowRaiserL.SetPos(0);

	browLowerer.SetRange(0, 100);
	browLowerer.SetPos(0);

	eyeCloseR.SetRange(0, 100);
	eyeCloseR.SetPos(0);

	eyeCloseL.SetRange(0, 100);
	eyeCloseL.SetPos(0);

	cheekRaiserR.SetRange(0, 100);
	cheekRaiserR.SetPos(0);

	cheekRaiserL.SetRange(0, 100);
	cheekRaiserL.SetPos(0);	

	noseWrinkler.SetRange(0, 100);
	noseWrinkler.SetPos(0);

	lipCornerPullerL.SetRange(0, 100);
	lipCornerPullerL.SetPos(0);

	lipCornerPullerR.SetRange(0, 100);
	lipCornerPullerR.SetPos(0);

	chinRaiser.SetRange(0, 100);
	chinRaiser.SetPos(0);

	lipPuckerer.SetRange(0, 100);
	lipPuckerer.SetPos(0);	

	lipsPart.SetRange(0, 100);
	lipsPart.SetPos(0);

	stickOutLowerLip.SetRange(0, 100);
	stickOutLowerLip.SetPos(0);

	//----------------------------------------------------------------------emotion �̸� ����
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
		
	for(int i=0;i<pView->emotion.emotions.size();i++){
		
		/*
		������ǥ���� ��� ������ �ʰ� ��(i==1)
		*/

		if (i != 1) {
			Expression temp = pView->emotion.emotions[i];
			expressionList.AddString(temp.name);
		}
	}

	expressionList.SetCurSel(0);


	
	//---------------------------------------------------------------------------


}


void ControllerView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();
		
	if(pScrollBar){
		
		// � �����̴����� �˻�
		if(pScrollBar == (CScrollBar*)&innerBrowRaiserR){

			nPos = innerBrowRaiserR.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[0] = (float)nPos;
			pView->relocate(tempExpression);
						
		}else if(pScrollBar == (CScrollBar*)&innerBrowRaiserL){

			nPos = innerBrowRaiserL.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[1] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&outerBrowRaiserR){

			nPos = outerBrowRaiserR.GetPos(); //�����̴��� ��ġ�� �˻�
		
			tempExpression.weight[2] = (float)nPos;
			pView->relocate(tempExpression);
						
		}else if(pScrollBar == (CScrollBar*)&outerBrowRaiserL){

			nPos = outerBrowRaiserL.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[3] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&browLowerer){

			nPos = browLowerer.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[4] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&eyeCloseR){

			nPos = eyeCloseR.GetPos(); //�����̴��� ��ġ�� �˻�
		
			tempExpression.weight[5] = (float)nPos;
			pView->relocate(tempExpression);
						
		}else if(pScrollBar == (CScrollBar*)&eyeCloseL){

			nPos = eyeCloseL.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[6] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&cheekRaiserR){

			nPos = cheekRaiserR.GetPos(); //�����̴��� ��ġ�� �˻�
		
			tempExpression.weight[7] = (float)nPos;
			pView->relocate(tempExpression);
						
		}else if(pScrollBar == (CScrollBar*)&cheekRaiserL){

			nPos = cheekRaiserL.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[8] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&noseWrinkler){

			nPos = noseWrinkler.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[9] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&lipCornerPullerR){

			nPos = lipCornerPullerR.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[10] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&lipCornerPullerL){

			nPos = lipCornerPullerL.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[11] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&chinRaiser){

			nPos = chinRaiser.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[12] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&lipPuckerer){

			nPos = lipPuckerer.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[13] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&lipsPart){

			nPos = lipsPart.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[14] = (float)nPos;
			pView->relocate(tempExpression);

		}else if(pScrollBar == (CScrollBar*)&stickOutLowerLip){

			nPos = stickOutLowerLip.GetPos(); //�����̴��� ��ġ�� �˻�

			tempExpression.weight[15] = (float)nPos;
			pView->relocate(tempExpression);

		}
	}

	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void ControllerView::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);

	SaveExpressionDlg dialog;
	boolean flag = dialog.DoModal();

	if(flag){
		
		tempExpression.name = dialog.str;
		pView->emotion.saveEmotion(tempExpression);

		int size = pView->emotion.emotions.size();
		expressionList.AddString(dialog.str);
		expressionList.SetCurSel(size-1);
	
		addEmotionFlag = true;

	}
}


void ControllerView::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	CString name;
	GetDlgItemText(IDC_COMBO1, name);

	int id;
	for(int i=0;i<pView->emotion.emotions.size();i++){

		if(name == pView->emotion.emotions[i].name){
			id = i;
			break;
		}
	}	

	innerBrowRaiserR.SetPos(pView->emotion.emotions[id].weight[0]);
	innerBrowRaiserL.SetPos(pView->emotion.emotions[id].weight[1]);
	outerBrowRaiserR.SetPos(pView->emotion.emotions[id].weight[2]);
	outerBrowRaiserL.SetPos(pView->emotion.emotions[id].weight[3]);
	browLowerer.SetPos(pView->emotion.emotions[id].weight[4]);
	eyeCloseR.SetPos(pView->emotion.emotions[id].weight[5]);
	eyeCloseL.SetPos(pView->emotion.emotions[id].weight[6]);
	cheekRaiserR.SetPos(pView->emotion.emotions[id].weight[7]);
	cheekRaiserL.SetPos(pView->emotion.emotions[id].weight[8]);
	noseWrinkler.SetPos(pView->emotion.emotions[id].weight[9]);
	lipCornerPullerR.SetPos(pView->emotion.emotions[id].weight[10]);
	lipCornerPullerL.SetPos(pView->emotion.emotions[id].weight[11]);
	chinRaiser.SetPos(pView->emotion.emotions[id].weight[12]);
	lipPuckerer.SetPos(pView->emotion.emotions[id].weight[13]);
	lipsPart.SetPos(pView->emotion.emotions[id].weight[14]);
	stickOutLowerLip.SetPos(pView->emotion.emotions[id].weight[15]);
	

	for(int i=0; i<sizeof(pView->emotion.emotions[0].weight)/sizeof(float);i++){
		tempExpression.weight[i] = pView->emotion.emotions[id].weight[i];
	}

	pView->relocate(tempExpression);

	
}

