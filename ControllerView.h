#pragma once
#include "afxcmn.h"

//#include "SelectEmotionView.h"
//#include "MakeEmotionView.h"

#include "MerryDoc.h"
#include "MerryView.h"
#include "MainFrm.h"
#include "afxwin.h"


// ControllerView �� ���Դϴ�.

class ControllerView : public CFormView
{
	DECLARE_DYNCREATE(ControllerView)

protected:
	ControllerView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~ControllerView();

public:
	enum { IDD = IDD_DIALOG1 };
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
	
	Expression tempExpression;
	virtual void OnInitialUpdate();
	bool addEmotionFlag;
	int selectedEmotionIdx;
	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton1();

	CSliderCtrl speed;

	CSliderCtrl innerBrowRaiserR;
	CSliderCtrl innerBrowRaiserL;
	CSliderCtrl outerBrowRaiserR;
	CSliderCtrl outerBrowRaiserL;
	CSliderCtrl browLowerer;
	CSliderCtrl eyeCloseR;
	CSliderCtrl eyeCloseL;
	CSliderCtrl cheekRaiserR;
	CSliderCtrl cheekRaiserL;
	CSliderCtrl noseWrinkler;
	CSliderCtrl lipCornerPullerR;
	CSliderCtrl lipCornerPullerL;
	CSliderCtrl chinRaiser;
	CSliderCtrl lipPuckerer;
	CSliderCtrl lipsPart;
	CSliderCtrl stickOutLowerLip;
	CComboBox expressionList;

	afx_msg void OnCbnSelchangeCombo1();
};


