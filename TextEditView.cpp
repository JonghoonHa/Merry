// TextEditView.cpp : ���� �����Դϴ�.
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


// TextEditView �����Դϴ�.

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


// TextEditView �޽��� ó�����Դϴ�.


void TextEditView::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	editText="";
	UpdateData(false);

	Invalidate(FALSE);
}



void TextEditView::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
