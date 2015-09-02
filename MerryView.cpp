
// MerryView.cpp : CMerryView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Merry.h"
#endif

#include "resource.h"
#include "MerryDoc.h"
#include "MerryView.h"
#include "MainFrm.h"
#include "ControllerView.h"
#include "Blending.h"

#include <gl/glew.h>
#include <gl/wglew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <math.h>

#include <iostream>

#include <SOIL.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMerryView

IMPLEMENT_DYNCREATE(CMerryView, CView)

BEGIN_MESSAGE_MAP(CMerryView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMerryView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CMerryView 생성/소멸

CMerryView::CMerryView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	//카메라 ------------------------------
	pos[0]=30.0f;		//카메라위치
	pos[1]=120.0f;
	pos[2]=300.0f;
	lookAt[0]=30.0f;		//바라보는방향
	lookAt[1]=80.0f;
	lookAt[2]=-80.0f;
	up[0]=0.0f;		//수직벡터
	up[1]=1.0f;
	up[2]=0.0f;

	//빛 -------------------------------
	lightPosition[0] = 30.0f;
	lightPosition[1] = 70.0f;
	lightPosition[2] = 1000.0f;
	lightPosition[3] = 1.0f;

	lightAmbient[0]= 0.8f;
	lightAmbient[1]= 0.8f;
	lightAmbient[2]= 0.8f;
	lightAmbient[3]= 1.0f;

	lightDiffuse[0]= 0.3f;
	lightDiffuse[1]= 0.3f;
	lightDiffuse[2]= 0.3f;
	lightDiffuse[3]= 1.0f;

	lightSpecular[0]= 0.3f;
	lightSpecular[1]= 0.3f;
	lightSpecular[2]= 0.3f;
	lightSpecular[3]= 1.0f;

	lightShineness=1.0f;

	// 애니메이션 --------------------------------

	animationFlag = false;
	getStartTime = true;
	firstDrawFlag = true;

	// 기타 -------------------------------------
	M_PI=3.141592;
	
	lButton = false;
	rButton = false;
	mButton = false;

}

CMerryView::~CMerryView()
{
}

BOOL CMerryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);
	
	return CView::PreCreateWindow(cs);
}

// CMerryView 그리기

void CMerryView::OnDraw(CDC* /*pDC*/)
{
	CMerryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->m_wndSplitter.SetActivePane(0, 1);
	ControllerView* controller = (ControllerView*)pFrame->GetActiveView();

	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glm::mat4 cam = glm::lookAt(glm::vec3(pos[0],pos[1],pos[2]),glm::vec3(lookAt[0],lookAt[1],lookAt[2]),glm::vec3(up[0],up[1],up[2]));
	glUniformMatrix4fv( glGetUniformLocation(pro, "cam"), 1, GL_FALSE, &cam[0][0]);	//행렬값 전달하기 ( 변수의위치, count, transpose, *value)

	glUniform4fv( glGetUniformLocation(pro, "lightPosition"), 1, lightPosition);
	glUniform4fv( glGetUniformLocation(pro, "lightAmbient"), 1, lightAmbient);
	glUniform4fv( glGetUniformLocation(pro, "lightDiffuse"), 1, lightDiffuse);
	glUniform4fv( glGetUniformLocation(pro, "lightSpecular"), 1, lightSpecular);
	glUniform1f( glGetUniformLocation(pro, "lightShineness"),lightShineness);
	
	glEnable(GL_DEPTH_TEST); 

	for(int i=0;i<box.size();i++){

		if(i <= 27){
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(glGetUniformLocation(pro, "tex"), 0);
		}else if(i == 28){
			glActiveTexture(GL_TEXTURE1);
			glUniform1i(glGetUniformLocation(pro, "tex"), 1);
		}else if(i == 29){
			glActiveTexture(GL_TEXTURE2);
			glUniform1i(glGetUniformLocation(pro, "tex"), 2);
		}else if(i == 30){
			glActiveTexture(GL_TEXTURE3);
			glUniform1i(glGetUniformLocation(pro, "tex"), 3);
		}else if(i == 31){
			glActiveTexture(GL_TEXTURE4);
			glUniform1i(glGetUniformLocation(pro, "tex"), 4);
		}  

		
		glBindVertexArray(box[i].VAO);
		glBindBuffer(GL_ARRAY_BUFFER, box[i].VBO[0]);	
		
		glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		glUniformMatrix4fv( glGetUniformLocation(pro, "Model"), 1, GL_FALSE, &Model[0][0]);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*box[i].currentPos.size() + sizeof(glm::vec3)*box[i].m_Normals.size() + sizeof(glm::vec2)*box[i].texCoord.size() , NULL , GL_STATIC_DRAW);	
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3)*box[i].currentPos.size() , box[i].currentPos.data());   
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*box[i].currentPos.size(), sizeof(glm::vec3)*box[i].m_Normals.size() , box[i].m_Normals.data());
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*box[i].currentPos.size() + sizeof(glm::vec3)*box[i].m_Normals.size(), sizeof(glm::vec2)*box[i].texCoord.size() , box[i].texCoord.data());

		GLuint index = glGetAttribLocation(pro, "vp");
		GLuint vNormal = glGetAttribLocation( pro, "vNormal" );
		GLuint texAttrib = glGetAttribLocation(pro, "texCoord");

		glEnableVertexAttribArray(index);
		glEnableVertexAttribArray(vNormal);
		glEnableVertexAttribArray(texAttrib);

		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);		
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(glm::vec3)*box[i].currentPos.size()));
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(glm::vec3)*box[i].currentPos.size()+sizeof(glm::vec3)*box[i].m_Normals.size()));//추가
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, box[i].VBO[1]);			
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(GLuint)*box[i].face.size() , box[i].face.data(), GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, box[i].face.size(), GL_UNSIGNED_INT, 0);	//( mode, count , index의 type, offset)
		
	}

	if ( FALSE == ::SwapBuffers( m_pDC->GetSafeHdc() ))
	{
		return;
	}

	if(animationFlag){ // animation codes

		if(getStartTime == true){

			// 애니메이션 시작 시각 기록
			startTime = GetTickCount();
			getStartTime = false;

			speaking.transSentenceToIdx();
		}

		nowTime = GetTickCount();
		diff = nowTime - startTime;

		speaking.setCharAtTime(diff); // 기본 표정 + 문장 표정 하려면 여기서 현재 idx값을 가져와야 하네! 이 값을 emotion system으로 보내주어야 한다.
		speaking.setWeightAtTime(diff);
		speaking.calCurrLook();

		blending.setPronounciation();
		blending.setEmotion();		
		blending.blendingFunction(diff);

	}

	if(firstDrawFlag || animationFlag){

		if(firstDrawFlag){

			firstDrawFlag = false;

			blending.finalExpression = emotion.emotions[controller->selectedEmotionIdx];
		}

		controller->innerBrowRaiserR.SetPos(blending.finalExpression.weight[0]);
		controller->innerBrowRaiserL.SetPos(blending.finalExpression.weight[1]);
		controller->outerBrowRaiserR.SetPos(blending.finalExpression.weight[2]);
		controller->outerBrowRaiserL.SetPos(blending.finalExpression.weight[3]);
		controller->browLowerer.SetPos(blending.finalExpression.weight[4]);
		controller->eyeCloseR.SetPos(blending.finalExpression.weight[5]);
		controller->eyeCloseL.SetPos(blending.finalExpression.weight[6]);
		controller->cheekRaiserR.SetPos(blending.finalExpression.weight[7]);
		controller->cheekRaiserL.SetPos(blending.finalExpression.weight[8]);
		controller->noseWrinkler.SetPos(blending.finalExpression.weight[9]);
		controller->lipCornerPullerR.SetPos(blending.finalExpression.weight[10]);
		controller->lipCornerPullerL.SetPos(blending.finalExpression.weight[11]);
		controller->chinRaiser.SetPos(blending.finalExpression.weight[12]);
		controller->lipPuckerer.SetPos(blending.finalExpression.weight[13]);
		controller->lipsPart.SetPos(blending.finalExpression.weight[14]);
		controller->stickOutLowerLip.SetPos(blending.finalExpression.weight[15]);

		relocate(blending.finalExpression);
	}
}




BOOL CMerryView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}
void CMerryView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}
void CMerryView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}



// CMerryView 진단

#ifdef _DEBUG
void CMerryView::AssertValid() const
{
	CView::AssertValid();
}

void CMerryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMerryDoc* CMerryView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMerryDoc)));
	return (CMerryDoc*)m_pDocument;
}
#endif //_DEBUG


// CMerryView 메시지 처리기

void CMerryView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pDC = new CClientDC(this);

	//Creating a window
	if(makecontext()==false){
		return;
	}
	if(initglew()==false){
		return;
	}
	if(newopengl()==false){
		return;
	}
	if(setopengl()==false){
		return;
	}

	//프로그램을 하나 만들어서 그 ID를 return함
	pro=glCreateProgram();	

	GLuint myShader1 = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* myshadersource1 = ReadFromFile("vshader.glsl");
	glShaderSource(myShader1, 1, &myshadersource1, NULL); //shader를 LOAD하기
	glCompileShader(myShader1); //shader를 compile하기

	GLsizei logSize = 0;
	GLchar  log[1024];

	GLint compileStatus = 0;
	glGetShaderiv(myShader1, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		glGetShaderInfoLog(myShader1, 1024, &logSize, log);
	}
	GLuint myShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* myshadersource2 = ReadFromFile("fshader.glsl");
	glShaderSource(myShader2, 1, &myshadersource2, NULL);	
	glCompileShader(myShader2);	

	glGetShaderiv(myShader2, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		glGetShaderInfoLog(myShader2, 1024, &logSize, log);
	}

	//shader를 program에 연결하기
	glAttachShader(pro, myShader1); //compile된 shader를 프로그램에 연결함
	glAttachShader(pro, myShader2); 
	glLinkProgram(pro);				//shader가 연결된 프로그램을 실행준비함
	glUseProgram(pro);				//프로그램을 실행하기


	/////////////////////////////////////////////////////////////////////
	ReadfromObj();	//obj파일 읽어들이기
	/////////////////////////////////////////////////////////////////////
	
	/* Texture loading */

	glGenTextures(5, textures);

	int width, height;
	unsigned char* image;
	
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	image = SOIL_load_image("obj/teeth_color.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glGenerateMipmap(GL_TEXTURE_2D);
	
	//세부 설정 부분
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	image = SOIL_load_image("obj/lEye_color.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glGenerateMipmap(GL_TEXTURE_2D);
	
	//세부 설정 부분
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	image = SOIL_load_image("obj/rEye_color.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glGenerateMipmap(GL_TEXTURE_2D);
	
	//세부 설정 부분
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE3);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	image = SOIL_load_image("obj/gum_color.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glGenerateMipmap(GL_TEXTURE_2D);
	
	//세부 설정 부분
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE4);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	image = SOIL_load_image("obj/skin_color7.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	
	//세부 설정 부분
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	///////////////////////////////////////////////////////////////////////////////


	for(int i=0;i<box.size();i++){	

		if(i <= 27){
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(glGetUniformLocation(pro, "tex"), 0);
		}else if(i == 28){
			glActiveTexture(GL_TEXTURE1);
			glUniform1i(glGetUniformLocation(pro, "tex"), 1);
		}else if(i == 29){
			glActiveTexture(GL_TEXTURE2);
			glUniform1i(glGetUniformLocation(pro, "tex"), 2);
		}else if(i == 30){
			glActiveTexture(GL_TEXTURE3);
			glUniform1i(glGetUniformLocation(pro, "tex"), 3);
		}else if(i == 31){
			glActiveTexture(GL_TEXTURE4);
			glUniform1i(glGetUniformLocation(pro, "tex"), 4);
		}    


		glGenVertexArrays(1,&(box[i].VAO));	
		glBindVertexArray(box[i].VAO);		

		glGenBuffers(1,&(box[i].VBO[0]));	
		glBindBuffer(GL_ARRAY_BUFFER, box[i].VBO[0]);	
	
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*box[i].currentPos.size() + sizeof(glm::vec3)*box[i].m_Normals.size() + sizeof(glm::vec2)*box[i].texCoord.size(), NULL , GL_STATIC_DRAW);	
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3)*box[i].currentPos.size() , box[i].currentPos.data());   
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*box[i].currentPos.size(), sizeof(glm::vec3)*box[i].m_Normals.size() , box[i].m_Normals.data());
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*box[i].currentPos.size()+sizeof(glm::vec3)*box[i].m_Normals.size(), sizeof(glm::vec2)*box[i].texCoord.size(), box[i].texCoord.data());//추가

		GLuint index = glGetAttribLocation(pro, "vp");
		GLuint vNormal = glGetAttribLocation( pro, "vNormal" );
		GLuint texAttrib = glGetAttribLocation(pro, "texCoord");

		glEnableVertexAttribArray(index);
		glEnableVertexAttribArray(vNormal);
		glEnableVertexAttribArray(texAttrib);

		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);		
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(glm::vec3)*box[i].currentPos.size()));
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(glm::vec3)*box[i].currentPos.size()+sizeof(glm::vec3)*box[i].m_Normals.size()));//추가

		glGenBuffers(1,&(box[i].VBO[1]));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, box[i].VBO[1]);	
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(GLuint)*box[i].face.size() , box[i].face.data(), GL_STATIC_DRAW);

	}

	////////////////////////////////////////////////////////////////////////////////////
	
	//Action Unit의 정보 읽어오기
	putAUInfo();	

	// 방향에 따른 가중치값 변경 table 생성
	setDirTable();

	// 입으로부터 각 AU의 거리
	setDistFromMouth();

}

bool CMerryView::makecontext(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,               // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		32,                             // 32-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		24,							  // 24-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	}; 

	// Get the id number for the best match supported by the hardware device context
	// to what is described in pfd
	int pixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);  

	//If there's no match, report an error
	if ( 0 == pixelFormat )
	{      
		return false;
	}  

	//If there is an acceptable match, set it as the current 
	if ( FALSE == SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd) )
	{      
		return false;
	}  

	//Create a context with this pixel format
	if ( 0 == (m_hRC = wglCreateContext( m_pDC->GetSafeHdc() ) ) )
	{      
		return false;
	} 

	//Make it current. Now we're ready to get extended features.
	if ( FALSE == wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
	{      
		return false;
	}

	return true;
}

bool CMerryView::initglew(void){

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		AfxMessageBox(_T("GLEW could not be initialized!"));
		return false;
	}
	else{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hRC);	
	}

	return true;
}

bool CMerryView::newopengl(void){

	const int attribList[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
		WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
		WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,     32,
		WGL_DEPTH_BITS_ARB,     24,
		//WGL_STENCIL_BITS_ARB,   8,
		0, 0  //End
	};

	unsigned int numFormats;
	int pixelFormat;
	PIXELFORMATDESCRIPTOR pfd; 

	//Select a pixel format number
	wglChoosePixelFormatARB(m_pDC->GetSafeHdc(), attribList, NULL, 1, &pixelFormat, &numFormats); 


	//Optional: Get the pixel format's description. We must provide a 
	//description to SetPixelFormat(), but its contents mean little.
	//According to MSDN: 
	//  The system's metafile component uses this structure to record the logical
	//  pixel format specification. The structure has no other effect upon the
	//  behavior of the SetPixelFormat function.


	DescribePixelFormat(m_pDC->GetSafeHdc(), pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd); 

	//Set it as the current 
	if ( FALSE == SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd) )
	{
		DWORD err = GetLastError();
		return false;
	}   

	//Create a context with this pixel format
	if ( 0 == (m_hRC = wglCreateContext( m_pDC->GetSafeHdc() ) ) )
	{      
		return false;
	}  

	//Make it current. Now we're ready to get extended features.
	if ( FALSE == wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
	{      
		return false;
	}

	return true;

}

bool CMerryView::setopengl(void){

	//Setup request for OpenGL 4.4 Core Profile
	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB,   3,
		WGL_CONTEXT_MINOR_VERSION_ARB,   2,
		WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 
		//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		0, 0  //End
	};  

	if(wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		//If this driver supports new style rendering contexts, create one
		HGLRC oldContext = m_hRC;
		if ( 0 == (m_hRC = m_hRC = wglCreateContextAttribsARB(m_pDC->GetSafeHdc(),0, attribs) ) )
		{         
			return false;
		}    
		if(!wglMakeCurrent(NULL,NULL) )
			wglDeleteContext(oldContext);
		if ( FALSE == wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
		{         
			return false;
		}     

	}else{  

		//Otherwise use the old style rendering context we created earlier.
		AfxMessageBox(_T("GL 3.2 Context not possible. Using old style context. (GL 2.1 and before)"));
	}
	return true;
}

void CMerryView::Perspective(const GLfloat fovy, const GLfloat aspect,  const GLfloat zNear, const GLfloat zFar, GLfloat* mat){

	GLfloat top   = tan(fovy/2.0*M_PI/180.0) * zNear;
	GLfloat right = top * aspect;

	for (int idx = 0; idx < 16; idx++) mat[idx] = 0.0;

	mat[0] = zNear/right;
	mat[5] = zNear/top;
	mat[10] = -(zFar + zNear)/(zFar - zNear);
	mat[14] = -2.0*zFar*zNear/(zFar - zNear);
	mat[11] = -1.0;
}

void CMerryView::OnSize(UINT nType, int cx, int cy)
{

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CWnd::OnSize(nType, cx, cy);
	
	glViewport(0,0,cx,cy);

	GLfloat projection[16];

	Perspective(60, (float)(cx)/(float)(cy), 0.1, 1500, projection);

	glUniformMatrix4fv( glGetUniformLocation(pro, "proj"), 1, GL_FALSE,  projection);
	
}

char* CMerryView::ReadFromFile(char* filename){

	FILE* fp; //파일포인터 타입 : 파일을 가리키는 포인터
	errno_t err = fopen_s(&fp, filename, "r+b"); //파일 열기

	if ( err != 0 ) { return NULL; }

	fseek(fp, 0L, SEEK_END);	//Jump to the end of file

	long size = ftell(fp);  //ftell : 파일의 시작부터 현재 파일의 위치까지를 바이트단위로 나타내는 long형값을 리턴

	fseek(fp, 0L, SEEK_SET); // 파일포인터를 처음부터 0L후에 위치시킴

	char* buf = new char[size+1];	
	size = fread(buf, 1, size, fp);
	/*  
	buf : 파일에서 읽은 데이터를 저장할 메모리
	1 : 읽을 단위(char형 읽을 거니깐, 1)
	size : 두번째 인자로 넘긴 크기를 몇번이나 읽을 것인가
	fp : 어디서 읽을 것인가

	읽어들인 원소의 개수가 return된다.
	*/

	buf[size] = '\0';
	//모든 내용이 buf에 들어감
	fclose(fp);

	return buf;
}

void CMerryView::ReadfromObj(void){

	string inLineBuf;	//한 줄
	string String;
	string header;	
		
	GLfloat x=0,y=0,z=0;
	char ex='s';//이전 줄의 첫 문자
	int vCount = 0;
	int nCount = 0;
	int tCount = 0;
	int k=0;//box 객체의 수?
	Box onebox;

	vector <glm::vec2> tempTex;//추가
	vector <glm::vec3> tempNormal;//추가

	GLfloat temp[6]={0,0,0,0,0,0};
	int temp_index=0;

	ifstream objFile("obj/head_uv2.obj");//head_uv2.obj
	if (objFile.fail())	return;

	while(!objFile.eof()){

		getline(objFile,inLineBuf);		//한 줄씩 읽어들이기
		istringstream inLine(inLineBuf);

		if(inLineBuf.length()>0){

			inLine >> header;

			if(header == "#"){}	//obj file에서 #은 주석 영역
			else if (header == "v"){//vertex				

				if(ex=='f'){//v -> f 이면 새로운 box일 때 이므로 box의 내용을 지우고 새롭게 추가한다.										

					box.push_back(onebox);
					k++;
					onebox.originalPos.erase(onebox.originalPos.begin(), onebox.originalPos.end());
					onebox.currentPos.erase(onebox.currentPos.begin(), onebox.currentPos.end());
					onebox.face.erase(onebox.face.begin(), onebox.face.end());
					onebox.texCoord.erase(onebox.texCoord.begin(), onebox.texCoord.end());
					onebox.m_Normals.erase(onebox.m_Normals.begin(), onebox.m_Normals.end());					
				}					

				ex='v';
				inLine >> x >> y >> z;				
				onebox.originalPos.push_back(glm::vec3(x, y, z));
				onebox.currentPos.push_back(glm::vec3(x, y, z));
				onebox.texCoord.push_back(glm::vec2(0,0));
				onebox.m_Normals.push_back(glm::vec3(0,0,0));

			}else if(header == "vt"){

				if(ex=='v'&& k!=0){// v -> t 인 경우. vertex 입력이 끝났으니까 size 계산을 한다.
					vCount += box[k-1].originalPos.size();					
				}

				ex = 't';
				inLine >> x >> y;
				tempTex.push_back(glm::vec2(x, y));

			}else if(header == "vn"){

				if(ex=='vt'&& k!=0){// vt -> vn 인 경우. texture 입력이 끝났으니까 size 계산을 한다.
					tCount += box[k-1].texCoord.size();				
				}

				ex = 'n';
				inLine >> x >> y >> z;
				tempNormal.push_back(glm::vec3(x, y, z));

			}else if (header == "f"){//face

				if(ex=='vn'&& k!=0){// vn -> f 인 경우. normal 입력이 끝났으니까 size 계산을 한다.
					nCount += box[k-1].m_Normals.size();		
				}

				ex='f';
				int nface = count(inLineBuf.begin(), inLineBuf.end(), '/')/2;// f 뒤에 숫자 몇 개나 있는지

				for(int idx2=0;idx2 < nface; idx2++){

					int fVertex, fTexture, fNormal;
					char c,e;//버려야 할 '//'들

					inLine >> fVertex >> c >> fTexture >> e >> fNormal;
					temp[temp_index++] = fVertex-vCount-1;

					onebox.texCoord[fVertex-vCount-1] = tempTex[fTexture-tCount-1];
					onebox.m_Normals[fVertex-vCount-1] = tempNormal[fNormal-nCount-1]; 
				}	
								
				int second=1;
				int third=2;

				for(int i=0;i<3*(nface-2);i++){//face를 이루는 vertex값들 넣기.					
			
					if(i%3==0)	onebox.face.push_back((int)temp[0]);
					if(i%3==1)	onebox.face.push_back((int)temp[second++]);
					if(i%3==2)	onebox.face.push_back((int)temp[third++]);

				}
				temp_index=0;
			}
		}	
	}

	box.push_back(onebox);	//마지막물체
}

void CMerryView::relocate(Expression totalExpression){

	for(int i=0;i<box[31].currentPos.size();i++){

		glm::vec3 finalVector = glm::vec3(0.0,0.0,0.0);						
		
		for(int j=0;j<box[31].pointInfo[i].size();j++){

			finalVector += (
				
				box[31].pointInfo[i][j].moveVector //ex) (6,4,0)
				* box[31].pointInfo[i][j].weight //ex) (0.5)
				* (totalExpression.weight[box[31].pointInfo[i][j].auNum]) * (float)(1.0/100.0) //ex) (30 * 1.0/100.0)
			
				);

			if(j+1 == box[31].pointInfo[i].size()){
				box[31].currentPos[i] = box[31].originalPos[i] + finalVector;	
				
			}
		}

	}

	Invalidate(FALSE);
}

void CMerryView::putAUInfo(void)
{
	// object의 vertex를 기준으로, 해당 vertex에 연관된 action unit의 목록을 등록한다.

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	for(int i=0;i<box[31].currentPos.size();i++){
		vector<EffectedAU> temp;
		box[31].pointInfo.push_back(temp);
	}
	
	//각 점마다 영향미치는 au정보와 weight값저장
	float dist[7];
	for(int i=0; i<sizeof(dist)/sizeof(dist[0]); i++){
		dist[i] = 0.0f;
	}
	EffectedAU temp;
	glm::vec3 vector;
	float limit;

	int upperLip[31] = {68, 69, 74, 75, 76, 77, 82, 87, 88, 89, 92, 460, 756, 877, 882, 883, 884, 885, 888, 893, 894, 895, 896, 897, 898, 901, 987, 1173, 1174, 1255, 1352};
	int lowerLip[24] = {70, 73, 80, 354, 355, 356, 358, 359, 361, 362, 363, 780, 781, 878, 881, 886, 1274 ,1273 , 1275, 1277, 1278, 1282, 1283, 1284};	
	//int lEye_lowerLine[8] = {1086, 1087, 1091, 1092, 1094, 1095, 1100, 1206};
	//int lEye_upperLine[8] = {1099, 1102, 1103, 1104, 1106, 1108, 1233, 1246};


	//얼굴의 각 점을 순서대로 검사
	for(int i=0;i<box[31].currentPos.size();i++){

		//innerBrowRaiserR///////////////////////////////

		for(int j=0;j<pDoc->units[0].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[0].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[0].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[0].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}

		temp.auNum = 0;
		limit = pDoc->units[0].distLimit[0];

		if(dist[0] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[0].actionPoint[1]].x - 10){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[0].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}	

		/////////////////////////////////////////////////

		//innerBrowRaiserL///////////////////////////////

		for(int j=0;j<pDoc->units[1].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[1].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[1].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[1].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 1;
		limit = pDoc->units[1].distLimit[0];

		if(dist[0] <= limit && box[31].currentPos[i].x > box[31].currentPos[pDoc->units[1].actionPoint[1]].x + 10){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[1].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//outerBrowRaiserR///////////////////////////////

		for(int j=0;j<pDoc->units[2].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[2].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[2].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[2].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 2;
		limit = pDoc->units[2].distLimit[0];

		if(dist[0] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[2].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//outerBrowRaiserL///////////////////////////////

		for(int j=0;j<pDoc->units[3].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[3].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[3].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[3].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 3;
		limit = pDoc->units[3].distLimit[0];

		if(dist[0] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[3].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//browLowerer////////////////////////////////////

		for(int j=0;j<pDoc->units[4].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[4].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[4].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[4].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 4;
		limit = pDoc->units[4].distLimit[0];

		// 안쪽 눈썹 오른쪽
		if(dist[0] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[4].actionPoint[4]].x - 10){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[4].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		// 안쪽 눈썹 왼쪽
		if(dist[1] <= limit && box[31].currentPos[i].x > box[31].currentPos[pDoc->units[4].actionPoint[4]].x + 10){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[4].moveVector[1];
			temp.weight = ((limit - dist[1]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		// 바깥쪽 눈썹 오른쪽
		if(dist[2] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[4].moveVector[2];
			temp.weight = ((limit - dist[2]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		// 바깥쪽 눈썹 왼쪽
		if(dist[3] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[4].moveVector[3];
			temp.weight = ((limit - dist[3]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//eyeCloseR//////////////////////////////////////

		for(int j=0;j<pDoc->units[5].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[5].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[5].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[5].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 5;
		limit = pDoc->units[5].distLimit[0];

		// 오른쪽 눈 바깥쪽
		if(dist[0] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[5].actionPoint[0]].x + 1
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[5].actionPoint[0]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[5].actionPoint[0]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[5].actionPoint[0]].y - 0.1){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[5].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[5].distLimit[1];

		if(dist[1] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[5].actionPoint[1]].x + 1
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[5].actionPoint[1]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[5].actionPoint[1]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[5].actionPoint[1]].y - 3){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[5].moveVector[1];
			temp.weight = ((limit - dist[1]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[5].distLimit[2];

		if(dist[2] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[5].actionPoint[2]].x + 1
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[5].actionPoint[2]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[5].actionPoint[2]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[5].actionPoint[2]].y - 3){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[5].moveVector[2];
			temp.weight = ((limit - dist[2]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[5].distLimit[3];

		if(dist[3] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[5].actionPoint[3]].x + 4
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[5].actionPoint[3]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[5].actionPoint[3]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[5].actionPoint[3]].y - 3){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[5].moveVector[3];
			temp.weight = ((limit - dist[3]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[5].distLimit[4];

		if(dist[4] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[5].actionPoint[4]].x + 1
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[5].actionPoint[4]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[5].actionPoint[4]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[5].actionPoint[4]].y - 0.1){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[5].moveVector[4];
			temp.weight = ((limit - dist[4]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[5].distLimit[5];

		// 오른쪽 눈 안쪽
		if(dist[5] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[5].actionPoint[5]].x + 1
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[5].actionPoint[5]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[5].actionPoint[5]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[5].actionPoint[5]].y - 0.1){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[5].moveVector[5];
			temp.weight = ((limit - dist[5]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//eyeCloseL//////////////////////////////////////

		for(int j=0;j<pDoc->units[6].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[6].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[6].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[6].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 6;
		limit = pDoc->units[6].distLimit[0];

		// 왼쪽 눈 바깥쪽
		if(dist[0] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[6].actionPoint[0]].x + 1
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[6].actionPoint[0]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[6].actionPoint[0]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[6].actionPoint[0]].y - 0.1){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[6].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[6].distLimit[1];

		if(dist[1] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[6].actionPoint[1]].x + 1
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[6].actionPoint[1]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[6].actionPoint[1]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[6].actionPoint[1]].y - 3){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[6].moveVector[1];
			temp.weight = ((limit - dist[1]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[6].distLimit[2];

		if(dist[2] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[6].actionPoint[2]].x + 1
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[6].actionPoint[2]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[6].actionPoint[2]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[6].actionPoint[2]].y - 3){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[6].moveVector[2];
			temp.weight = ((limit - dist[2]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[6].distLimit[3];

		if(dist[3] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[6].actionPoint[3]].x + 4
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[6].actionPoint[3]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[6].actionPoint[3]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[6].actionPoint[3]].y - 3){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[6].moveVector[3];
			temp.weight = ((limit - dist[3]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[6].distLimit[4];

		if(dist[4] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[6].actionPoint[4]].x + 1
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[6].actionPoint[4]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[6].actionPoint[4]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[6].actionPoint[4]].y - 0.1){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[6].moveVector[4];
			temp.weight = ((limit - dist[4]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[6].distLimit[5];

		// 왼쪽 눈 안쪽
		if(dist[5] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[6].actionPoint[5]].x + 1
			&& box[31].currentPos[i].x > box[31].currentPos[pDoc->units[6].actionPoint[5]].x - 1
			&& box[31].currentPos[i].y < box[31].currentPos[pDoc->units[6].actionPoint[5]].y + 3
			&& box[31].currentPos[i].y > box[31].currentPos[pDoc->units[6].actionPoint[5]].y - 0.1){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[6].moveVector[5];
			temp.weight = ((limit - dist[5]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		//////////////////////////////////////////////

		//cheekRaiserR///////////////////////////////////

		for(int j=0;j<pDoc->units[7].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[7].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[7].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[7].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 7;
		limit = pDoc->units[7].distLimit[0];

		if(dist[0] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[7].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//cheekRaiserL///////////////////////////////////

		for(int j=0;j<pDoc->units[8].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[8].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[8].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[8].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 8;
		limit = pDoc->units[8].distLimit[0];

		if(dist[0] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[8].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//noseWrinkler///////////////////////////////////

		for(int j=0;j<pDoc->units[9].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[9].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[9].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[9].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 9;
		limit = pDoc->units[9].distLimit[0];

		if(dist[0] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[9].actionPoint[4]].x  - 3){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[9].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[9].distLimit[1];

		if(dist[1] <= limit && box[31].currentPos[i].x > box[31].currentPos[pDoc->units[9].actionPoint[4]].x  + 3){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[9].moveVector[1];
			temp.weight = ((limit - dist[1]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[9].distLimit[2];

		if(dist[2] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[9].moveVector[2];
			temp.weight = ((limit - dist[2]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[9].distLimit[3];

		if(dist[3] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[9].moveVector[3];
			temp.weight = ((limit - dist[3]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//lipCornerPullerR///////////////////////////////

		for(int j=0;j<pDoc->units[10].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[10].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[10].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[10].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 10;
		limit = pDoc->units[10].distLimit[0];

		if(dist[0] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[10].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//lipCornerPullerL///////////////////////////////

		for(int j=0;j<pDoc->units[11].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[11].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[11].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[11].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 11;
		limit = pDoc->units[11].distLimit[0];

		if(dist[0] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[11].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//chinRaiser/////////////////////////////////////

		for(int j=0;j<pDoc->units[12].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[12].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[12].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[12].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 12;
		limit = pDoc->units[12].distLimit[0];

		if(dist[0] <= limit){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[12].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//lipPuckerer////////////////////////////////////

		for(int j=0;j<pDoc->units[13].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[13].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[13].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[13].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 13;
		limit = pDoc->units[13].distLimit[0];

		if(dist[0] <= limit && box[31].currentPos[i].x < box[31].currentPos[pDoc->units[13].actionPoint[0]].x){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[13].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[13].distLimit[1];

		if(dist[1] <= limit && box[31].currentPos[i].x >= box[31].currentPos[pDoc->units[13].actionPoint[1]].x){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[13].moveVector[1];
			temp.weight = ((limit - dist[1]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[13].distLimit[2];

		if(dist[2] <= limit && box[31].currentPos[i].x <= box[31].currentPos[pDoc->units[13].actionPoint[2]].x){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[13].moveVector[2];
			temp.weight = ((limit - dist[2]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[13].distLimit[3];

		if(dist[3] <= limit && box[31].currentPos[i].x > box[31].currentPos[pDoc->units[13].actionPoint[3]].x){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[13].moveVector[3];
			temp.weight = ((limit - dist[3]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[13].distLimit[4];

		if(dist[4] <= limit && box[31].currentPos[i].y > box[31].currentPos[pDoc->units[13].actionPoint[4]].y
			&& box[31].currentPos[i].y <= 52.5){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[13].moveVector[4];
			temp.weight = ((limit - dist[4]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[13].distLimit[5];

		if(dist[5] <= limit && box[31].currentPos[i].y < box[31].currentPos[pDoc->units[13].actionPoint[5]].y + 5
			&& box[31].currentPos[i].y > box[31].currentPos[i].y + 1){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[13].moveVector[5];
			temp.weight = ((limit - dist[5]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		limit = pDoc->units[13].distLimit[6];

		if(dist[6] <= limit && box[31].currentPos[i].y < box[31].currentPos[i].y + 0.00001
			&& box[31].currentPos[i].y > 52.5){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[13].moveVector[6];
			temp.weight = ((limit - dist[6]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

		//lipsPart///////////////////////////////////////

		for(int j=0;j<pDoc->units[14].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[14].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[14].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[14].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 14;
		

		bool upperLipFlag = false;

		for(int j=0;j<sizeof(upperLip)/sizeof(int);j++){
				if(i == upperLip[j]){
					upperLipFlag = true;
				}
		}

		for(int j=0;j<3;j++){

			limit = pDoc->units[14].distLimit[j];

			if(dist[j] <= limit && box[31].currentPos[i].y  <= 52.0 && upperLipFlag == false){

				//weight값 계산_(AP와의 거리비율)
						
				temp.moveVector = pDoc->units[14].moveVector[j];
				temp.weight = ((limit - dist[j]) * 1.0/limit);

				box[31].pointInfo[i].push_back(temp);
			}

		}

		// 입 안쪽 벌리기
		for(int j=0;j<sizeof(lowerLip)/sizeof(int);j++){
			if(i == lowerLip[j]){
				moveLips(i, temp.auNum, pDoc->units[14].moveVector[2]);
			}
		}

		/////////////////////////////////////////////////

		//stickOutLowerLip///////////////////////////////

		for(int j=0;j<pDoc->units[15].actionPoint.size();j++){
			float distance = pow(double(box[31].currentPos[i].x - box[31].currentPos[pDoc->units[15].actionPoint[j]].x),2) +
				pow(double(box[31].currentPos[i].y - box[31].currentPos[pDoc->units[15].actionPoint[j]].y), 2) +
				pow(double(box[31].currentPos[i].z - box[31].currentPos[pDoc->units[15].actionPoint[j]].z), 2);			

			dist[j] = distance;
		}
		
		temp.auNum = 15;
		limit = pDoc->units[15].distLimit[0];

		if(dist[0] <= limit  && box[31].currentPos[i].y >= 35  && box[31].currentPos[i].y <= 52.5
			&& box[31].currentPos[i].x <= 59  && box[31].currentPos[i].x >= 15){

			//weight값 계산_(AP와의 거리비율)
						
			temp.moveVector = pDoc->units[15].moveVector[0];
			temp.weight = ((limit - dist[0]) * 1.0/limit);

			box[31].pointInfo[i].push_back(temp);
		}

		/////////////////////////////////////////////////

	}
	
}

void CMerryView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	rButton = true;
	mouse_point = point;

	CView::OnRButtonDown(nFlags, point);
}

void CMerryView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	rButton = false;

	CView::OnRButtonUp(nFlags, point);
}

void CMerryView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lButton = true;
	mouse_point = point;

	CView::OnLButtonDown(nFlags, point);
}

void CMerryView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lButton = false;

	CView::OnLButtonUp(nFlags, point);
}

void CMerryView::OnMouseMove(UINT nFlags, CPoint point)
{

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(lButton == true || mButton == true || rButton == true){

		int dx = point.x - mouse_point.x;
		int dy = point.y - mouse_point.y;

		if(lButton == true){//mouse 왼쪽 버튼 눌렸을 때

			//lookAt의 위치를 원점으로 하는 가상의 구 위로 카메라를 이동한다.

			GLfloat sphere[3];
			int temp = 0;

			sphere[0] = pos[0] - lookAt[0];
			sphere[1] = pos[1] - lookAt[1];
			sphere[2] = pos[2] - lookAt[2];

			int r = sphere[0]*sphere[0] + sphere[1]*sphere[1] + sphere[2]*sphere[2];

			if(pos[2] >= 0){	
				pos[0] -= dx;
				pos[1] += dy;

				sphere[0] -= dx;
				sphere[1] += dy;

				temp = int(sqrt(abs(r - int(sphere[0]*sphere[0] + sphere[1]*sphere[1]))));
				temp = abs(int(sphere[2]) - temp);
			}else{
				pos[0] += dx;
				pos[1] += dy;

				sphere[0] += dx;
				sphere[1] += dy;

				temp = int(sqrt(abs(r - int(sphere[0]*sphere[0] + sphere[1]*sphere[1]))));
				temp = abs(int(sphere[2]) + temp);
			}	

			if(dy == 0){
				if(sphere[2] > 0){
					if(dx > 0){
						if(sphere[0] > 0) pos[2] -= temp; else pos[2] += temp;
					}else{
						if(sphere[0] > 0) pos[2] += temp; else pos[2] -= temp;
					}
				}else{
					if(dx > 0){
						if(sphere[0] > 0) pos[2] += temp; else pos[2] -= temp;
					}else{
						if(sphere[0] > 0) pos[2] -= temp; else pos[2] += temp;
					}
				}
			}else{
				if(sphere[2] > 0){
					if(dy > 0){
						if(sphere[1] > 0) pos[2] -= temp; else pos[2] += temp;
					}else{
						if(sphere[1] > 0) pos[2] += temp; else pos[2] -= temp;
					}
				}else{
					if(dy > 0){
						if(sphere[1] > 0) pos[2] += temp; else pos[2] -= temp;
					}else{
						if(sphere[1] > 0) pos[2] -= temp; else pos[2] += temp;
					}
				}
			}

		}

		if(mButton == true){//mouse 휠 눌렸을 때		

			//물체를 바라보는 방향은 일정한데 xy평면으로만 카메라를 움직이게 한다.

			if(pos[2] > 0){
				pos[0] -= dx;		pos[1] += dy;
				lookAt[0] -= dx;	lookAt[1] += dy;
			}else{
				pos[0] += dx;		pos[1] += dy;
				lookAt[0] += dx;	lookAt[1] += dy;
			}

		}

		if(rButton == true){//mouse 오른쪽 버튼 눌렸을 때

			//카메라를 앞, 뒤로 이동해 물체를 확대, 축소시킨다.

			bool enlargement;

			if(dx == 0){
				if(dy > 0) enlargement = true;
				else enlargement = false;
			}else if(dx > 0){
				if(dy/dx>1)	enlargement = false;
				else enlargement = true;
			}else{
				if(dy/dx>1)	enlargement = true;
				else enlargement = false;
			}

			glm::vec3 angle = glm::vec3(pos[0]-lookAt[0], pos[1]-lookAt[1], pos[2]-lookAt[2]);

			if(enlargement == true){
				pos[0] += 0.02*angle[0];
				pos[1] += 0.02*angle[1];
				pos[2] += 0.02*angle[2];
			}else{
				pos[0] -= 0.02*angle[0];
				pos[1] -= 0.02*angle[1];
				pos[2] -= 0.02*angle[2];
			}
			
		}

		//카메라 위치의 뒤로 조명을 이동한다.
		glm::vec3 angle = glm::vec3(pos[0]-lookAt[0], pos[1]-lookAt[1], pos[2]-lookAt[2]);

		lightPosition[0] = 50*angle[0];
		lightPosition[1] = 50*angle[1];
		lightPosition[2] = 50*angle[2];

		mouse_point = point;	
		Invalidate(false);

	}

	CView::OnMouseMove(nFlags, point);
}

void CMerryView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mButton = false;
	mouse_point = point;

	CView::OnMButtonUp(nFlags, point);
}

void CMerryView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mButton = true;
	mouse_point = point;

	CView::OnMButtonDown(nFlags, point);
}

BOOL CMerryView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)

{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//마우스 휠을 움직이면 카메라를 앞, 뒤로 이동해 물체를 확대, 축소시킨다.
	bool enlargement;

	if(zDelta > 0) enlargement = false;
	else enlargement = true;

	glm::vec3 angle = glm::vec3(pos[0]-lookAt[0], pos[1]-lookAt[1], pos[2]-lookAt[2]);

	if(enlargement == true){
		pos[0] += 0.04*angle[0];
		pos[1] += 0.04*angle[1];
		pos[2] += 0.04*angle[2];
	}else{
		pos[0] -= 0.04*angle[0];
		pos[1] -= 0.04*angle[1];
		pos[2] -= 0.04*angle[2];
	}

	Invalidate(false);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMerryView::moveLips(int point, int au, glm::vec3 vector)
{
	// point index, move vector

	EffectedAU temp;

	temp.moveVector = vector;
	temp.weight = 1.0;
	temp.auNum = au;

	box[31].pointInfo[point].push_back(temp);

}

void CMerryView::setDirTable(){

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	// table 생성 & 초기화
	int auSize = pDoc->units.size();

	for(int i=0; i<auSize; i++){
		vector<float> row;
		for(int j=0; j<auSize; j++){
			row.push_back(1.0f);
		}
		pDoc->directionTable.push_back(row);
	}

	// table에 값을 채우는 내용

	for(int i=0; i<box[31].pointInfo.size(); i++){
		for(int p=0; p<box[31].pointInfo[i].size(); p++){
			for(int q=p+1; q<box[31].pointInfo[i].size(); q++){

				EffectedAU au1 = box[31].pointInfo[i][p];
				EffectedAU au2 = box[31].pointInfo[i][q];

				// 두 벡터를 내적
				float vResult = getInnerProduct(au1.moveVector,au2.moveVector);

				// 두 벡터의 길이 곱
				float vLength = getLength(au1.moveVector) * getLength(au2.moveVector);

				// 두 벡터의 사이각의 cosine값
				double cosine = vResult / vLength;
				float radian = acos(cosine);
				float result = cos(radian/2);

				// 결과값이 가장 낮은 것을 선택
				if(pDoc->directionTable[au1.auNum][au2.auNum] > result){
						pDoc->directionTable[au1.auNum][au2.auNum] = result;
						pDoc->directionTable[au2.auNum][au1.auNum] = result;
				}

			}

		}
	}
}

float CMerryView::getLength(glm::vec3 vector){

	float value = vector.x * vector.x;
	value += vector.y * vector.y;
	value += vector.z * vector.z;

	value = sqrt(value);

	return value;

}

float CMerryView::getInnerProduct(glm::vec3 vec1, glm::vec3 vec2){

	float value = vec1.x * vec2.x;
	value += vec1.y * vec2.y;
	value += vec1.z * vec2.z;

	return value;
}

void CMerryView::setDistFromMouth(void){
	// 입으로부터 각 AU의 거리

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	vector<int> mouth;
	mouth.push_back(877);
	mouth.push_back(69);

	glm::vec3 midPoint_mouth = getMidPoint(mouth);

	float limit = getDistance(midPoint_mouth, box[31].originalPos[1347]);

	for(int i=0; i<pDoc->units.size(); i++){

		glm::vec3 midPoint = getMidPoint(pDoc->units[i].actionPoint);

		float distance = getDistance(midPoint_mouth, midPoint);

		float value = distance / limit;

		if(value > 1.0)	value = 1.0;

		pDoc->units[i].distFromMouth  = value;

	}

}

glm::vec3 CMerryView::getMidPoint(vector<int> points){
	// 얼굴의 여러 점 사이의 중점

	glm::vec3 result;

	for(int i=0;i<points.size();i++){
		result.x += box[31].originalPos[points[i]].x;
		result.y += box[31].originalPos[points[i]].y;
		result.z += box[31].originalPos[points[i]].z;
	}

	result /= points.size();

	return result;
}

float CMerryView::getDistance(glm::vec3 p1, glm::vec3 p2){
	// 두 점 사이의 거리

	float result = pow((double)(p1.x - p2.x), 2);
	result += pow((double)(p1.y - p2.y), 2);
	result += pow((double)(p1.z - p2.z), 2);

	result = sqrt(result);

	return result;

}