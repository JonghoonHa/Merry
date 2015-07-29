
// MerryDoc.cpp : CMerryDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CMerryDoc ����/�Ҹ�

CMerryDoc::CMerryDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

	speed = 0.0f;

	//-----------------------------------------------------------------
	ActionUnit temp;

	// units[0] : innerBrowRaiserR
	// ���� ���� ������
	temp.auNum = 0;

	temp.actionPoint.push_back(1346); // ����
	temp.moveVector.push_back(glm::vec3(2.0, 5.0, 2.0));
	temp.distLimit.push_back(700.0);

	temp.actionPoint.push_back(1347); //  �̰�
	temp.moveVector.push_back(glm::vec3(0.0, 0.0, 0.0));
	temp.distLimit.push_back(0.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[1] : innerBrowRaiserL
	// ���� ���� ����
	temp.auNum = 1;

	temp.actionPoint.push_back(442); // ����
	temp.moveVector.push_back(glm::vec3(-2.0, 5.0, 2.0));
	temp.distLimit.push_back(700.0);

	temp.actionPoint.push_back(1347); //  �̰�
	temp.moveVector.push_back(glm::vec3(0.0, 0.0, 0.0));
	temp.distLimit.push_back(0.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[2] : outerBrowRaiserR
	// �ٱ��� ���� ������
	temp.auNum = 2;

	temp.actionPoint.push_back(1164); // ����
	temp.moveVector.push_back(glm::vec3(-2.0, 6.0, -1.0));
	temp.distLimit.push_back(800.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[3] : outerBrowRaiserL
	// �ٱ��� ���� ����
	temp.auNum = 3;

	temp.actionPoint.push_back(274); // ����
	temp.moveVector.push_back(glm::vec3(2.0, 6.0, -1.0));
	temp.distLimit.push_back(800.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[4] : browLowerer
	// �� ����
	temp.auNum = 4;

	temp.actionPoint.push_back(1346); // ���� ���� ������
	temp.moveVector.push_back(glm::vec3(7.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(442); // ���� ���� ����
	temp.moveVector.push_back(glm::vec3(-7.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(1164); // �ٱ��� ���� ������
	temp.moveVector.push_back(glm::vec3(7.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(274); // �ٱ��� ���� ����
	temp.moveVector.push_back(glm::vec3(-7.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(1347); // �̰�
	temp.moveVector.push_back(glm::vec3(0.0, 0.0, 0.0));
	temp.distLimit.push_back(0.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[5] : eyeCloseR
	// ������ ��
	temp.auNum = 5;

	// �ٱ��ʿ���
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

	// ��������
	temp.actionPoint.push_back(1232);
	temp.moveVector.push_back(glm::vec3(0.0,-3.0,0.0));
	temp.distLimit.push_back(25.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[6] : eyeCloseL
	// ������ ��
	temp.auNum = 6;

	// �ٱ��ʿ���
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

	// ��������
	temp.actionPoint.push_back(392);
	temp.moveVector.push_back(glm::vec3(0.0,-3.0,0.0));
	temp.distLimit.push_back(25.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[7] : cheekRaiserR
	// ������ ��
	temp.auNum = 7;
	temp.actionPoint.push_back(1148);
	temp.moveVector.push_back(glm::vec3(2.0,6.0,3.0));
	temp.distLimit.push_back(600.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[8] : cheekRaiserL
	// ���� ��
	temp.auNum = 8;
	temp.actionPoint.push_back(287);
	temp.moveVector.push_back(glm::vec3(-2.0,6.0,3.0));
	temp.distLimit.push_back(600.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[9] : noseWrinkler
	// �ຼ�� ���� ����
	temp.auNum = 9;

	temp.actionPoint.push_back(863); // ������ �ຼ
	temp.moveVector.push_back(glm::vec3(2.0, 7.0, 0.0));
	temp.distLimit.push_back(750.0);

	temp.actionPoint.push_back(53); // ���� �ຼ
	temp.moveVector.push_back(glm::vec3(-2.0, 7.0, 0.0));
	temp.distLimit.push_back(750.0);

	temp.actionPoint.push_back(1346); // ������ ���� ����
	temp.moveVector.push_back(glm::vec3(0.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(442); // ���� ���� ����
	temp.moveVector.push_back(glm::vec3(0.0, -6.0, 3.0));
	temp.distLimit.push_back(900.0);

	temp.actionPoint.push_back(1347); // �̰�
	temp.moveVector.push_back(glm::vec3(0.0, 0.0, 0.0));
	temp.distLimit.push_back(0.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[10] : lipCornerPullerR
	// ������ �Բ���
	temp.auNum = 10;
	temp.actionPoint.push_back(877);
	temp.moveVector.push_back(glm::vec3(-6.0,4.0,0.0));
	temp.distLimit.push_back(300.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[11] : lipCornerPullerL
	// ���� �Բ���
	temp.auNum = 11;
	temp.actionPoint.push_back(69);
	temp.moveVector.push_back(glm::vec3(6.0,4.0,0.0));
	temp.distLimit.push_back(300.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[12] : chin raiser
	// ��
	temp.auNum = 12;
	temp.actionPoint.push_back(1598);
	temp.moveVector.push_back(glm::vec3(0.0,5.0,0.0));
	temp.distLimit.push_back(1400.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[13] : lip puckerer
	// ��
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

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[14] : lipsPart
	// ��
	temp.auNum = 14;

	// ������ �Բ���
	temp.actionPoint.push_back(877);
	temp.moveVector.push_back(glm::vec3(0.0,10.0,5.0));
	temp.distLimit.push_back(600.0);

	// ���� �Բ���
	temp.actionPoint.push_back(69);
	temp.moveVector.push_back(glm::vec3(0.0,10.0,5.0));
	temp.distLimit.push_back(600.0);
		
	temp.actionPoint.push_back(1203);
	temp.moveVector.push_back(glm::vec3(0.0,-20.0,-5.0));
	temp.distLimit.push_back(4900.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	// units[15] : stickOutLowerLip
	// ���?
	temp.auNum = 15;
	temp.actionPoint.push_back(1289);
	temp.moveVector.push_back(glm::vec3(0.0,8.0,10.0));
	temp.distLimit.push_back(800.0);

	units.push_back(temp);

	// �ʱ�ȭ
	temp.actionPoint.clear();
	temp.distLimit.clear();
	temp.moveVector.clear();

	//// units[16] : 
	//// ���?
	//temp.auNum = ;
	//temp.actionPoint.push_back();
	//temp.moveVector.push_back(glm::vec3());
	//temp.distLimit.push_back();

	//units.push_back(temp);

	//// �ʱ�ȭ
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

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CMerryDoc serialization

void CMerryDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CMerryDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CMerryDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CMerryDoc ����

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


// CMerryDoc ���


//void CMerryDoc::makeDirTable(vector <glm::vec3> position){
//
//	//CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
//	//CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
//
//	// table ����
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
//	// ������� ���������� table�� ���� ä��� ����
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
//						// �� ���͸� ����
//						float vResult = getInnerProduct(units[i].moveVector[p], units[j].moveVector[q]);
//
//						// �� ������ ���� ��
//						float vLength = getLength(units[i].moveVector[p]) * getLength(units[j].moveVector[q]);
//
//						// �� ������ ���̰��� cosine��
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
