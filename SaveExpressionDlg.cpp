// SaveExpressionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Merry.h"
#include "SaveExpressionDlg.h"
#include "afxdialogex.h"


// SaveExpressionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(SaveExpressionDlg, CDialogEx)

SaveExpressionDlg::SaveExpressionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(SaveExpressionDlg::IDD, pParent)
{

}

SaveExpressionDlg::~SaveExpressionDlg()
{
}

void SaveExpressionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, expressionName);
}


BEGIN_MESSAGE_MAP(SaveExpressionDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SaveExpressionDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SaveExpressionDlg 메시지 처리기입니다.


void SaveExpressionDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	GetDlgItemText(IDD_DIALOG3, str);

	expressionName.GetWindowText(str);

	
	CDialogEx::OnOK();
}


BOOL SaveExpressionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str("Merry");
	this->SetWindowTextW(str);

	return true;
}
