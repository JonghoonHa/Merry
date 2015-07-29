#pragma once

#include "Speaking.h"
#include "MerryView.h"

// TextEditView �� ���Դϴ�.

class TextEditView : public CFormView
{
	DECLARE_DYNCREATE(TextEditView)

protected:
	TextEditView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString editText;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};


