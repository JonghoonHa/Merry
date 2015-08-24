
// MerryDoc.h : CMerryDoc Ŭ������ �������̽�
//
#include"ActionUnit.h"
#include"Expression.h"
#include"EffectedAU.h"

#pragma once


class CMerryDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMerryDoc();
	DECLARE_DYNCREATE(CMerryDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMerryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	float speed;
	vector<ActionUnit> units;
	vector<vector<float>> directionTable;
	
	vector<char> sentence;
	bool animationFlag;

};
