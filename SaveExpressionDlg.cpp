// SaveExpressionDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Merry.h"
#include "SaveExpressionDlg.h"
#include "afxdialogex.h"


// SaveExpressionDlg ��ȭ �����Դϴ�.

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


// SaveExpressionDlg �޽��� ó�����Դϴ�.


void SaveExpressionDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
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
