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

	// ���� ��ȯ ���� ����
	this_condition_end = false;

	//------------------------------------------------

	// ���� ǥ�� ����

	//���� �ٹ�
	float tWeight0[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	Expression tTemp0("0", tWeight0);
	pronounciations.push_back(tTemp0);

	// �� �߰� ( ���� �ٹ� )
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
	// �Է��� ������ �ý��� ���� �ε��� ������ ��ȯ

	for(int k=0;k<sentence.size();k++){

		transSentence[k] = matchPronounciationIdx(sentence[k]);
	}

	//// 'hello', 'merry'�� ���� e�� ������ ���ڻ��̿� ������ ���� ����
	//for(int k=0;k<sentence.size()-3;k++){// ������ ���ڰ� 2�� ������ �� ���� ����
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

	// 'is'���� s�� 1�� ����
	for(int k=1;k<sentence.size();k++){

		if(sentence[k-1] == 'i' && sentence[k] == 's' ){
					
			transSentence[k] = 1;
		}
	}


	//������ ���ڿ� 'e'������ �����̹Ƿ� ���� -> the�� ���⿡ �ɸ���!
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

	//���忡�� ù ����(��������)�� ������ �������� 0���� ����
	for(int k=0;k<sentence.size()-1;k++){

		if(this_condition_end == false && transSentence[k] == 1)
			transSentence[k] = 0;
		else
			this_condition_end = true;	
	}

	//'my'�� ���� ���� y�� ������ �� 1�� ����
	for(int k=1;k<sentence.size();k++){
	
		if(sentence[k-1] == 'm' && sentence[k] == 'y'){
			transSentence[k] = 1;
		}
	}
			
	//'merry'�� m�� 0�� ����
	for(int k=0;k<sentence.size()-1;k++){
						
		if(sentence[k] == 'm' && sentence[k+1] == 'e'){
			transSentence[k] = 0;
		}
	}

	////ǥ�� �±���'(', ')'�� ǥ�� ������ ����
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

	// ���� ���� Ư�� ���ĺ��� idx ������ ��ȯ

	int index = 1;

	if(emotionTagFlag == false){
		switch(letter){

		case '0': // �Դٹ�
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
			// �������� ���� ����, ����(����), ��ħǥ ��
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
	// �ִϸ��̼� ��� �ð��� input���� �޾Ƽ� ����, ����, ������ � ���ڸ� ���ϴ����� ����Ͽ� ��ȯ�ϴ� �Լ�
	
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	ControllerView* controller = (ControllerView*)pFrame->m_wndSplitter.GetPane(0,1);

	const int introTime = introBlockNum * speed;
	int currBlockNum = diff/speed;

	if(diff <= ( sentence.size() + (introBlockNum*2) ) * speed ){   
	
		if(/*(int)diff < introTime*/currBlockNum<introBlockNum){

			// �� ó�� ���� block��
			preIdx = matchPronounciationIdx('0');
			currIdx = matchPronounciationIdx('0');

		}else if(/*(int)diff >= introTime && (int)diff <= introTime + speed*/currBlockNum>=introBlockNum && currBlockNum< introBlockNum+1){

			// �� ù����
			preIdx = matchPronounciationIdx('0');
			currIdx = transSentence[0];
	
		}else if(/* (int)diff >= ((sentence.size() + introBlockNum) * speed)
			&& ( (int)diff < ((sentence.size() + introBlockNum + 1) * speed) )*/
			currBlockNum >= introBlockNum + sentence.size() && currBlockNum<introBlockNum + sentence.size()+1){

			// �� ������ ���� ���� block

			preIdx = transSentence[diff/speed - introBlockNum - 1 ];	
			currIdx= matchPronounciationIdx('0');

		}else if( /*(int)diff >= ((sentence.size() + introBlockNum + 1) * speed)*/currBlockNum >= introBlockNum + sentence.size()+1 ){

			// �� ������ ���� block��
			preIdx = matchPronounciationIdx('0');
			currIdx = matchPronounciationIdx('0');	
			
		}else{

			// ���� �� ��� ����
				
			preIdx = transSentence[diff/speed - introBlockNum - 1 ];	
			currIdx = transSentence[diff/speed - introBlockNum ];	

		}	

	}else{

		//animation end ���� 
		pView->animationFlag = false;
		pView->firstDrawFlag = true;
		pView->getStartTime = true;

		pView->speaking.transSentence.clear();
		pView->speaking.sentence.clear();

		// �ִϸ��̼� ���� �� ���� ǥ������ ���ư�			
		controller->expressionList.SetCurSel(controller->selectedEmotionIdx-1);		

	}	

}

void Speaking::setWeightAtTime(DWORD diff)
{

	if(diff%(int)speed <= speed/2.0){ // �� block�� ���� ����

		preWeight = 1.0 - abs( (float)(diff%(int)speed) + speed/2.0) / speed;
		currWeight =1.0 - abs( (float)(diff%(int)speed) - speed/2.0 ) / speed;

	}else{ // ������ ����

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

	// idx�� ������ ���� �� ��� ���� �� ǥ�� �±׿� ���� ���� ǥ�� ���̴�.
	// �׷��Ƿ� emotion module���� ǥ���� ������ spk ǥ������ ��ȯ�Ѵ�.

	if(preIdx<0)	preExp = pView->emotion.emotions[abs(preIdx)];
	else	preExp = pronounciations[preIdx];

	if(currIdx<0)	currExp = pView->emotion.emotions[abs(currIdx)];
	else	currExp = pronounciations[currIdx];
	
	for(int i=0;i<pDoc->units.size();i++){ // � ������ ���ϴ� ǥ���� �����. ���� ���� ���� ���� ����.

		nowLook.weight[i] = preExp.weight[i] * preWeight + currExp.weight[i] * currWeight;

	}
	
}