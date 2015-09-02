
// MerryView.h : CMerryView 클래스의 인터페이스
//

#pragma once
#include <gl/glew.h>
#include <gl/wglew.h>

#include "Box.h"
#include "EffectedAU.h"
#include "Emotion.h"
#include "Speaking.h"
#include "resource.h"
#include "Blending.h"

using namespace std;
class CMerryDoc;

class CMerryView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMerryView();
	DECLARE_DYNCREATE(CMerryView)

// 특성입니다.
public:
	CMerryDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	CDC* m_pDC;
    HGLRC m_hRC;
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMerryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:

	GLuint pro;
	GLuint textures[5];

	//카메라변수
	GLfloat pos[3];
	GLfloat lookAt[3];
	GLfloat up[3];

	// 카메라 시점 변환
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	bool lButton;
	bool mButton;
	bool rButton;
	CPoint mouse_point;

	// 빛 변수
	GLfloat lightPosition[4];
	GLfloat lightAmbient[4];
	GLfloat lightDiffuse[4];
	GLfloat lightSpecular[4];
	GLfloat lightShineness;

	// opengl 설정
	bool makecontext(void);
	bool initglew(void);
	bool newopengl(void);
	bool setopengl(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void Perspective(const GLfloat fovy, const GLfloat aspect,  const GLfloat zNear, const GLfloat zFar, GLfloat* mat);

	// 파일 read
	char* ReadFromFile(char* filename);
	void ReadfromObj(void);
	
	virtual void OnInitialUpdate();	
	void relocate(Expression totalExpression);
	void putAUInfo();

	// 선언
	vector <Box> box;
	GLdouble M_PI;

	//---------------------
	Emotion emotion;
	Speaking speaking;
	Blending blending;
	//---------------------
	
	
	// 애니메이션
	bool getStartTime;
	bool animationFlag;
	bool firstDrawFlag;

	DWORD startTime;
	DWORD nowTime;
	DWORD diff;

private:	
	void moveLips(int point, int au, glm::vec3 vector);
	void setDirTable();

	float getLength(glm::vec3 vector);
	float getInnerProduct(glm::vec3 vec1, glm::vec3 vec2);

	void setDistFromMouth();
	glm::vec3 getMidPoint(vector<int> points);
	float getDistance(glm::vec3 p1, glm::vec3 p2);
};

#ifndef _DEBUG  // MerryView.cpp의 디버그 버전
inline CMerryDoc* CMerryView::GetDocument() const
   { return reinterpret_cast<CMerryDoc*>(m_pDocument); }
#endif

