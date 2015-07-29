#pragma once

#include "Speaking.h"
#include "MerryView.h"

// TextEditView 폼 뷰입니다.

class TextEditView : public CFormView
{
	DECLARE_DYNCREATE(TextEditView)

protected:
	TextEditView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~TextEditView();

public:
	enum { IDD = IDD_DIALOG2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString editText;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};


