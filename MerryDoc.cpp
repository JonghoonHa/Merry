
// MerryDoc.cpp : CMerryDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Merry.h"
#endif

#include "MerryDoc.h"
#include <math.h>

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMerryDoc

IMPLEMENT_DYNCREATE(CMerryDoc, CDocument)

BEGIN_MESSAGE_MAP(CMerryDoc, CDocument)
END_MESSAGE_MAP()


// CMerryDoc 생성/소멸

CMerryDoc::CMerryDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

	speed = 0.0f;

	//-----------------------------------------------------------------
	ActionUnit temp;

	// units[0] : innerBrowRaiserR
	// 안쪽 눈썹 오른쪽
	temp.auNum = 0;

	temp.actionPoint.push_back(1346); // 눈썹
	temp.moveVector.push_back(glm::vec3(2.0, 5.0, 2.0));
	temp.distLimit.push_back(700.0);

	temp.actionPoint.push_back(1347); //  미간
	temp.moveVector.push_back(glm::vec3(0.0, 0.0, 0.0));
	temp.distLimit.push_back(0.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[1] : innerBrowRaiserL
	// 안쪽 눈썹 왼쪽
	temp.auNum = 1;

	temp.actionPoint.push_back(442); // 눈썹
	temp.moveVector.push_back(glm::vec3(-2.0, 5.0, 2.0));
	temp.distLimit.push_back(700.0);

	temp.actionPoint.push_back(1347); //  미간
	temp.moveVector.push_back(glm::vec3(0.0, 0.0, 0.0));
	temp.distLimit.push_back(0.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[2] : outerBrowRaiserR
	// 바깥쪽 눈썹 오른쪽
	temp.auNum = 2;

	temp.actionPoint.push_back(1164); // 눈썹
	temp.moveVector.push_back(glm::vec3(-2.0, 6.0, -1.0));
	temp.distLimit.push_back(800.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[3] : outerBrowRaiserL
	// 바깥쪽 눈썹 왼쪽
	temp.auNum = 3;

	temp.actionPoint.push_back(274); // 눈썹
	temp.moveVector.push_back(glm::vec3(2.0, 6.0, -1.0));
	temp.distLimit.push_back(800.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[4] : browLowerer
	// 양 눈썹
	temp.auNum = 4;

	temp.actionPoint.push_back(1346); // 안쪽 눈썹 오른쪽
	temp.moveVector.push_back(glm::vec3(7.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(442); // 안쪽 눈썹 왼쪽
	temp.moveVector.push_back(glm::vec3(-7.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(1164); // 바깥쪽 눈썹 오른쪽
	temp.moveVector.push_back(glm::vec3(7.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(274); // 바깥쪽 눈썹 왼쪽
	temp.moveVector.push_back(glm::vec3(-7.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(1347); // 미간
	temp.moveVector.push_back(glm::vec3(0.0, 0.0, 0.0));
	temp.distLimit.push_back(0.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[5] : eyeCloseR
	// 오른쪽 눈
	temp.auNum = 5;

	// 바깥쪽에서
	temp.actionPoint.push_back(1227);
	temp.moveVector.push_back(glm::vec3(0.0,-2.5,0.0));
	temp.distLimit.push_back(25.0);

	temp.actionPoint.push_back(1228);
	temp.moveVector.push_back(glm::vec3(0.0,-6.0,0.0));
	temp.distLimit.push_back(25.0);

	temp.actionPoint.push_back(1229);
	temp.moveVector.push_back(glm::vec3(0.0,-11.7,0.0));
	temp.distLimit.push_back(25.0);

	temp.actionPoint.push_back(1230);
	temp.moveVector.push_back(glm::vec3(0.0,-12.3,0.0));
	temp.distLimit.push_back(25.0);

	temp.actionPoint.push_back(1231);
	temp.moveVector.push_back(glm::vec3(0.0,-5.7,0.0));
	temp.distLimit.push_back(25.0);

	// 안쪽으로
	temp.actionPoint.push_back(1232);
	temp.moveVector.push_back(glm::vec3(0.0,-3.0,0.0));
	temp.distLimit.push_back(25.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[6] : eyeCloseL
	// 오른쪽 눈
	temp.auNum = 6;

	// 바깥쪽에서
	temp.actionPoint.push_back(387);
	temp.moveVector.push_back(glm::vec3(0.0,-2.5,0.0));
	temp.distLimit.push_back(25.0);

	temp.actionPoint.push_back(388);
	temp.moveVector.push_back(glm::vec3(0.0,-6.0,0.0));
	temp.distLimit.push_back(25.0);

	temp.actionPoint.push_back(389);
	temp.moveVector.push_back(glm::vec3(0.0,-11.7,0.0));
	temp.distLimit.push_back(25.0);

	temp.actionPoint.push_back(390);
	temp.moveVector.push_back(glm::vec3(0.0,-12.3,0.0));
	temp.distLimit.push_back(25.0);

	temp.actionPoint.push_back(391);
	temp.moveVector.push_back(glm::vec3(0.0,-5.7,0.0));
	temp.distLimit.push_back(25.0);

	// 안쪽으로
	temp.actionPoint.push_back(392);
	temp.moveVector.push_back(glm::vec3(0.0,-3.0,0.0));
	temp.distLimit.push_back(25.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[7] : cheekRaiserR
	// 오른쪽 볼
	temp.auNum = 7;
	temp.actionPoint.push_back(1148);
	temp.moveVector.push_back(glm::vec3(2.0,6.0,3.0));
	temp.distLimit.push_back(600.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[8] : cheekRaiserL
	// 왼쪽 볼
	temp.auNum = 8;
	temp.actionPoint.push_back(287);
	temp.moveVector.push_back(glm::vec3(-2.0,6.0,3.0));
	temp.distLimit.push_back(600.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[9] : noseWrinkler
	// 콧볼과 눈썹 안쪽
	temp.auNum = 9;

	temp.actionPoint.push_back(863); // 오른쪽 콧볼
	temp.moveVector.push_back(glm::vec3(2.0, 7.0, 0.0));
	temp.distLimit.push_back(750.0);

	temp.actionPoint.push_back(53); // 왼쪽 콧볼
	temp.moveVector.push_back(glm::vec3(-2.0, 7.0, 0.0));
	temp.distLimit.push_back(750.0);

	temp.actionPoint.push_back(1346); // 오른쪽 눈썹 안쪽
	temp.moveVector.push_back(glm::vec3(0.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(442); // 왼쪽 눈썹 안쪽
	temp.moveVector.push_back(glm::vec3(0.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(1347); // 미간
	temp.moveVector.push_back(glm::vec3(0.0, 0.0, 0.0));
	temp.distLimit.push_back(0.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[10] : lipCornerPullerR
	// 오른쪽 입꼬리
	temp.auNum = 10;
	temp.actionPoint.push_back(877);
	temp.moveVector.push_back(glm::vec3(-6.0,4.0,0.0));
	temp.distLimit.push_back(300.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[11] : lipCornerPullerL
	// 왼쪽 입꼬리
	temp.auNum = 11;
	temp.actionPoint.push_back(69);
	temp.moveVector.push_back(glm::vec3(6.0,4.0,0.0));
	temp.distLimit.push_back(300.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[12] : chin raiser
	// 턱
	temp.auNum = 12;
	temp.actionPoint.push_back(1598);
	temp.moveVector.push_back(glm::vec3(0.0,5.0,0.0));
	temp.distLimit.push_back(1400.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[13] : lip puckerer
	// 입
	temp.auNum = 13;

	temp.actionPoint.push_back(877);
	temp.moveVector.push_back(glm::vec3(6.0,0.0,-3.0));
	temp.distLimit.push_back(800.0);

	temp.actionPoint.push_back(877);
	temp.moveVector.push_back(glm::vec3(8.0,0.0,6.0));
	temp.distLimit.push_back(600.0);

	temp.actionPoint.push_back(431);
	temp.moveVector.push_back(glm::vec3(-8.0,0.0,6.0));
	temp.distLimit.push_back(600.0);

	temp.actionPoint.push_back(431);
	temp.moveVector.push_back(glm::vec3(-6.0,0.0,-3.0));
	temp.distLimit.push_back(800.0);

	temp.actionPoint.push_back(1203);
	temp.moveVector.push_back(glm::vec3(0.0,-2.0,0.0));
	temp.distLimit.push_back(300.0);

	temp.actionPoint.push_back(1253);
	temp.moveVector.push_back(glm::vec3(0.0,5.0,5.0));
	temp.distLimit.push_back(300.0);

	temp.actionPoint.push_back(1253);
	temp.moveVector.push_back(glm::vec3(0.0,0.0,5.0));
	temp.distLimit.push_back(300.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[14] : lipsPart
	// 입
	temp.auNum = 14;

	// 오른쪽 입꼬리
	temp.actionPoint.push_back(877);
	temp.moveVector.push_back(glm::vec3(0.0,10.0,5.0));
	temp.distLimit.push_back(600.0);

	// 왼쪽 입꼬리
	temp.actionPoint.push_back(69);
	temp.moveVector.push_back(glm::vec3(0.0,10.0,5.0));
	temp.distLimit.push_back(600.0);
		
	temp.actionPoint.push_back(1203);
	temp.moveVector.push_back(glm::vec3(0.0,-20.0,-5.0));
	temp.distLimit.push_back(4900.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[15] : stickOutLowerLip
	// 어디?
	temp.auNum = 15;
	temp.actionPoint.push_back(1289);
	temp.moveVector.push_back(glm::vec3(0.0,8.0,10.0));
	temp.distLimit.push_back(800.0);

	units.push_back(temp);

	// 초기화
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	//// units[16] : 
	//// 어디?
	//temp.auNum = ;
	//temp.actionPoint.push_back();
	//temp.moveVector.push_back(glm::vec3());
	//temp.distLimit.push_back();

	//units.push_back(temp);

	//// 초기화
	//temp.actionPoint.clear();
	//temp.distLimit.clear();
	//temp.moveVector.clear();



	

}

CMerryDoc::~CMerryDoc()
{
}

BOOL CMerryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMerryDoc serialization

void CMerryDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMerryDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMerryDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMerryDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMerryDoc 진단

#ifdef _DEBUG
void CMerryDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMerryDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMerryDoc 명령


//void CMerryDoc::makeDirTable(vector <glm::vec3> position){
//
//	//CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
//	//CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
//
//	// table 생성
//	int auSize = units.size();
//
//	for(int i=0; i<auSize;i++){
//		vector<float> row;
//		for(int j=0; j<auSize;j++){
//			float column = 1.0f;
//			row.push_back(column);
//		}
//		directionTable.push_back(row);
//	}
//
//	// 여기부터 본격적으로 table에 값을 채우는 내용
//
//	for(int i=0; i<auSize; i++){
//		for(int j=i+1; j<auSize; j++){
//
//			for(int p=0; p<units[i].actionPoint.size(); p++){
//				for(int q=0; q< units[j].actionPoint.size(); q++){
//
//					glm::vec3 pt1 = position[units[i].actionPoint[p]];
//					glm::vec3 pt2 = position[units[j].actionPoint[q]];
//
//					float distance = sqrt(getInnerProduct(pt1, pt2));
//
//					if(distance <= 30){
//
//						// 두 벡터를 내적
//						float vResult = getInnerProduct(units[i].moveVector[p], units[j].moveVector[q]);
//
//						// 두 벡터의 길이 곱
//						float vLength = getLength(units[i].moveVector[p]) * getLength(units[j].moveVector[q]);
//
//						// 두 벡터의 사이각의 cosine값
//						double cosine = vResult / vLength;
//						float radian = acos(cosine);
//
//						float result = cos(radian/2);
//					
//						if(directionTable[i][j] > result){
//							directionTable[i][j] = result;
//							directionTable[j][i] = result;
//						}
//					}
//
//				}
//			}
//
//		}
//	}
//}
//
//float CMerryDoc::getLength(glm::vec3 vector){
//
//	float value = vector.x * vector.x;
//	value += vector.y * vector.y;
//	value += vector.z * vector.z;
//
//	value = sqrt(value);
//
//	return value;
//
//}
//
//float CMerryDoc::getInnerProduct(glm::vec3 vec1, glm::vec3 vec2){
//
//	float value = vec1.x * vec2.x;
//	value = vec1.y * vec2.y;
//	value = vec1.z * vec2.z;
//
//	return value;
//}
