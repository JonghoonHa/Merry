#pragma once

#include "MerryDoc.h"
#include "MerryView.h"
#include "MainFrm.h"
#include "afxwin.h"

// SaveExpressionDlg 대화 상자입니다.

class SaveExpressionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SaveExpressionDlg)

public:
	SaveExpressionDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SaveExpressionDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	CString str;
	CEdit expressionName;
};
