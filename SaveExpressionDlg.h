#pragma once

#include "MerryDoc.h"
#include "MerryView.h"
#include "MainFrm.h"
#include "afxwin.h"

// SaveExpressionDlg ��ȭ �����Դϴ�.

class SaveExpressionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SaveExpressionDlg)

public:
	SaveExpressionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SaveExpressionDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	CString str;
	CEdit expressionName;
};
