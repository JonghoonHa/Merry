// TextEditView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Merry.h"
#include "TextEditView.h"


// TextEditView

IMPLEMENT_DYNCREATE(TextEditView, CFormView)

TextEditView::TextEditView()
	: CFormView(TextEditView::IDD)
	,editText(_T(""))
{

}

TextEditView::~TextEditView()
{
}

void TextEditView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(TextEditView, CFormView)
	ON_BN_CLICKED(IDCANCEL, &TextEditView::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &TextEditView::OnBnClickedOk)
END_MESSAGE_MAP()


// TextEditView 진단입니다.

#ifdef _DEBUG
void TextEditView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void TextEditView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// TextEditView 메시지 처리기입니다.


void TextEditView::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	editText="";
	UpdateData(false);

	Invalidate(FALSE);
}



void TextEditView::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	//CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	GetDlgItemText(IDC_EDIT1, editText);

	UpdateData(TRUE);

	if(editText.GetLength() !=0){

		for(int i=0;i<editText.GetLength();i++){		
			pView->speaking.sentence.push_back(editText[i]);
		}

		pView->animationFlag = true;

		pView->Invalidate(FALSE);

	}
}
