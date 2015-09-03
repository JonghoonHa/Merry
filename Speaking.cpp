#include "stdafx.h"
#include "Speaking.h"
#include "MerryView.h"
#include "ControllerView.h"

Speaking::Speaking(void){
}
Speaking::Speaking(float _speed, int _introBlockNum)
{
	speed = _speed;
	introBlockNum = _introBlockNum;

	preIdx = 0; currIdx = 0; nextIdx = 0;
	preWeight = 0.0; currWeight = 0.0; nextWeight = 0.0;

	emotionTagFlag = false;

	//-----------------------------------------------

	// 발음 변환 제어 조건
	this_condition_end = false;

	//------------------------------------------------

	// 발음 표정 생성

	//완전 다뭄
	float tWeight0[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	Expression tTemp0("0", tWeight0);
	pronounciations.push_back(tTemp0);

	// 말 중간 ( 조금 다뭄 )
	float tWeight1[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0, 0.0};
	Expression tTemp1("01", tWeight1);
	pronounciations.push_back(tTemp1);

	float tWeight2[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 0.0};
	Expression tTemp2("a", tWeight2);
	pronounciations.push_back(tTemp2);

	float tWeight3[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 50.0, 50.0, 0.0, 0.0, 40.0, 0.0};
	Expression tTemp3("e", tWeight3);
	pronounciations.push_back(tTemp3);

	float tWeight4[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 80.0, 80.0, 0.0, 0.0, 20.0, 0.0};
	Expression tTemp4("i", tWeight4);
	pronounciations.push_back(tTemp4);

	float tWeight5[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 60.0, 0.0};
	Expression tTemp5("o", tWeight5);
	pronounciations.push_back(tTemp5);

	float tWeight6[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 80.0, 100.0, 60.0, 0.0};
	Expression tTemp6("u", tWeight6);
	pronounciations.push_back(tTemp6);

	float tWeight7[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 50.0, 50.0, 0.0, 0.0, 10.0, 0.0};
	Expression tTemp7("y", tWeight7);
	pronounciations.push_back(tTemp7);

	float tWeight8[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 0.0};
	Expression tTemp8("m", tWeight8);
	pronounciations.push_back(tTemp8);

}

Speaking::~Speaking(void)
{
}

Expression Speaking::getPronounciation(void)
{
	return nowLook;
}

void Speaking::transSentenceToIdx(void)
{
	// 입력한 문장을 시스템 내부 인덱스 값으로 변환

	for(int k=0;k<sentence.size();k++){

		transSentence[k] = matchPronounciationIdx(sentence[k]);
	}

	//// 'hello', 'merry'와 같이 e와 마지막 글자사이에 나오는 자음 제어
	//for(int k=0;k<sentence.size()-3;k++){// 문장의 글자가 2개 이하일 때 오류 유발
	//	 
	//	if(sentence[k] == 'e' && 
	//		(sentence[k+1] != ' ' && sentence[k+1] != '.' ) &&
	//		(sentence[k+2] != ' ' && sentence[k+2] != '.' ) &&
	//		(transSentence[k+3] != 1 && transSentence[k+3] != 0)){
	//					
	//			transSentence[k+1] = transSentence[k];
	//			transSentence[k+2] = transSentence[k+3];

	//	}
	//}

	// 'is'에서 s을 1로 제어
	for(int k=1;k<sentence.size();k++){

		if(sentence[k-1] == 'i' && sentence[k] == 's' ){
					
			transSentence[k] = 1;
		}
	}


	//마지막 글자에 'e'나오면 묵음이므로 제어 -> the도 여기에 걸린다!
	for(int k=1;k<sentence.size();k++){			
				
		if(sentence[k-1] == 'e' && sentence[k] == ' '){
			transSentence[k-1] = 0;

			if(k+1 != sentence.size()){
				transSentence[k] = 0;
			}
		}

		if(sentence[k] == 'e' && k+1 == sentence.size()){
			transSentence[k] = 0;
		}
	}

	//문장에서 첫 모음(지정글자)이 나오기 전까지는 0으로 제어
	for(int k=0;k<sentence.size()-1;k++){

		if(this_condition_end == false && transSentence[k] == 1)
			transSentence[k] = 0;
		else
			this_condition_end = true;	
	}

	//'my'와 같이 끝이 y로 끝나는 것 1로 제어
	for(int k=1;k<sentence.size();k++){
	
		if(sentence[k-1] == 'm' && sentence[k] == 'y'){
			transSentence[k] = 1;
		}
	}
			
	//'merry'의 m을 0로 제어
	for(int k=0;k<sentence.size()-1;k++){
						
		if(sentence[k] == 'm' && sentence[k+1] == 'e'){
			transSentence[k] = 0;
		}
	}

	////표정 태그인'(', ')'를 표정 값으로 제어
	//for(int k=0;k<sentence.size()-1;k++){
	//					
	//	if(sentence[k] == '('){
	//		transSentence[k] = transSentence[k+1];
	//	}
	//	if(sentence[k] == ')'){
	//		transSentence[k] = transSentence[k-1];
	//	}
	//}

}

int Speaking::matchPronounciationIdx(char letter){

	// 문장 속의 특정 알파벳을 idx 값으로 변환

	int index = 1;

	if(emotionTagFlag == false){
		switch(letter){

		case '0': // 입다뭄
			index = 0;	break;
		case 'a':
			index = 2;	break;
		case 'e':
			index = 3;	break;
		case 'i':
			index = 4;	break;
		case 'o':
			index= 5;	break;
		case 'u':
			index = 6;	break;
		case 'y':
			index = 7;	break;
		case 'm':
			index = 0;	break;
		case 'b' :
			index = 0;	break;
		case 'p' :
			index = 0;	break;
		case '(' :
			index = 0;
			emotionTagFlag = true;
			break;
		default :
			// 지정되지 않은 자음, 띄어쓰기(공백), 마침표 등
			index = 1;
			break;
		}
	}else{ // emotionTagFlag == true

		if(letter == ')'){
			index = 0;
			emotionTagFlag = false;
		}
		else{
			index = int(letter - '0') * (-1);
		}
	}

	return index;
}


void Speaking::setCharAtTime(DWORD diff)
{
	// 애니메이션 경과 시간을 input으로 받아서 이전, 현재, 다음에 어떤 글자를 말하는지를 계산하여 반환하는 함수
	
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	ControllerView* controller = (ControllerView*)pFrame->m_wndSplitter.GetPane(0,1);

	const int introTime = introBlockNum * speed;
	int currBlockNum = diff/speed;

	if(diff <= ( sentence.size() + (introBlockNum*2) ) * speed ){   
	
		if(/*(int)diff < introTime*/currBlockNum<introBlockNum){

			// 맨 처음 공백 block들
			preIdx = matchPronounciationIdx('0');
			currIdx = matchPronounciationIdx('0');

		}else if(/*(int)diff >= introTime && (int)diff <= introTime + speed*/currBlockNum>=introBlockNum && currBlockNum< introBlockNum+1){

			// 맨 첫글자
			preIdx = matchPronounciationIdx('0');
			currIdx = transSentence[0];
	
		}else if(/* (int)diff >= ((sentence.size() + introBlockNum) * speed)
			&& ( (int)diff < ((sentence.size() + introBlockNum + 1) * speed) )*/
			currBlockNum >= introBlockNum + sentence.size() && currBlockNum<introBlockNum + sentence.size()+1){

			// 맨 마지막 글자 다음 block

			preIdx = transSentence[diff/speed - introBlockNum - 1 ];	
			currIdx= matchPronounciationIdx('0');

		}else if( /*(int)diff >= ((sentence.size() + introBlockNum + 1) * speed)*/currBlockNum >= introBlockNum + sentence.size()+1 ){

			// 맨 마지막 공백 block들
			preIdx = matchPronounciationIdx('0');
			currIdx = matchPronounciationIdx('0');	
			
		}else{

			// 문장 속 어느 글자
				
			preIdx = transSentence[diff/speed - introBlockNum - 1 ];	
			currIdx = transSentence[diff/speed - introBlockNum ];	

		}	

	}else{

		//animation end 조건 
		pView->animationFlag = false;
		pView->firstDrawFlag = true;
		pView->getStartTime = true;

		pView->speaking.transSentence.clear();
		pView->speaking.sentence.clear();

		// 애니메이션 끝난 후 이전 표정으로 돌아감			
		controller->expressionList.SetCurSel(controller->selectedEmotionIdx-1);		

	}	

}

void Speaking::setWeightAtTime(DWORD diff)
{

	if(diff%(int)speed <= speed/2.0){ // 한 block의 앞쪽 절반

		preWeight = 1.0 - abs( (float)(diff%(int)speed) + speed/2.0) / speed;
		currWeight =1.0 - abs( (float)(diff%(int)speed) - speed/2.0 ) / speed;

	}else{ // 나머지 절반

		preWeight = 0.0;
		currWeight = 1.0;

	}

}


void Speaking::calCurrLook(void){

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	ControllerView* controller = (ControllerView*)pFrame->GetActiveView();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	CMerryDoc* pDoc = (CMerryDoc *)pFrame->GetActiveDocument();

	Expression preExp;
	Expression currExp;

	// idx가 음수인 경우는 말 대신 문장 내 표정 태그에 의해 들어온 표정 값이다.
	// 그러므로 emotion module에서 표정을 가져와 spk 표정으로 반환한다.

	if(preIdx<0)	preExp = pView->emotion.emotions[abs(preIdx)];
	else	preExp = pronounciations[preIdx];

	if(currIdx<0)	currExp = pView->emotion.emotions[abs(currIdx)];
	else	currExp = pronounciations[currIdx];
	
	for(int i=0;i<pDoc->units.size();i++){ // 어떤 순간의 말하는 표정의 결과물. 이전 값과 현재 값의 조합.

		nowLook.weight[i] = preExp.weight[i] * preWeight + currExp.weight[i] * currWeight;

	}
	
}