
// MerryView.h : CMerryView Ŭ������ �������̽�
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
protected: // serialization������ ��������ϴ�.
	CMerryView();
	DECLARE_DYNCREATE(CMerryView)

// Ư���Դϴ�.
public:
	CMerryDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	CDC* m_pDC;
    HGLRC m_hRC;
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMerryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

public:

	GLuint pro;
	GLuint textures[5];

	//ī�޶󺯼�
	GLfloat pos[3];
	GLfloat lookAt[3];
	GLfloat up[3];

	// ī�޶� ���� ��ȯ
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

	// �� ����
	GLfloat lightPosition[4];
	GLfloat lightAmbient[4];
	GLfloat lightDiffuse[4];
	GLfloat lightSpecular[4];
	GLfloat lightShineness;

	// opengl ����
	bool makecontext(void);
	bool initglew(void);
	bool newopengl(void);
	bool setopengl(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void Perspective(const GLfloat fovy, const GLfloat aspect,  const GLfloat zNear, const GLfloat zFar, GLfloat* mat);

	// ���� read
	char* ReadFromFile(char* filename);
	void ReadfromObj(void);
	
	virtual void OnInitialUpdate();	
	void relocate(Expression totalExpression);
	void putAUInfo();

	// ����
	vector <Box> box;
	GLdouble M_PI;

	//---------------------
	Emotion emotion;
	Speaking speaking;
	Blending blending;
	//---------------------
	
	
	// �ִϸ��̼�
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

#ifndef _DEBUG  // MerryView.cpp�� ����� ����
inline CMerryDoc* CMerryView::GetDocument() const
   { return reinterpret_cast<CMerryDoc*>(m_pDocument); }
#endif

