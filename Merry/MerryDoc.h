
// MerryDoc.h : CMerryDoc 클래스의 인터페이스
//
#include"ActionUnit.h"
#include"Expression.h"
#include"EffectedAU.h"

#pragma once


class CMerryDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMerryDoc();
	DECLARE_DYNCREATE(CMerryDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMerryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	float speed;
	vector<ActionUnit> units;
	vector<vector<float>> directionTable;
	
	vector<char> sentence;
	bool animationFlag;

//	void makeDirTable(vector <glm::vec3> position);
//
//private:
//	float getLength(glm::vec3 vector);
//	float getInnerProduct(glm::vec3 vec1, glm::vec3 vec2);
};
