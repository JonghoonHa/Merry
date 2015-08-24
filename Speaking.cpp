#include "stdafx.h"
#include "Speaking.h"
#include "MerryView.h"
#include "ControllerView.h"

Speaking::Speaking(void)
{
	speed = 200.0;
	
	introBlockNum = 10;
	introTime = introBlockNum * speed;

	preIdx = 0; currIdx = 0; nextIdx = 0;
	preWeight = 0.0; currWeight = 0.0; nextWeight = 0.0;


	Expression temp;
	for(int i=0;i<9;i++){
		pronounciations.push_back(temp);
	}

	emotionTagFlag = false;

	//-----------------------------------------------

	// ���� ��ȯ ���� ����
	this_condition_end = false;

	//------------------------------------------------

	//���� �ٹ�
	pronounciations[0].name = "0";

	pronounciations[0].weight[0] = 0.0;
	pronounciations[0].weight[1] = 0.0;
	pronounciations[0].weight[2] = 0.0;
	pronounciations[0].weight[3] = 0.0;
	pronounciations[0].weight[4] = 0.0;
	pronounciations[0].weight[5] = 0.0;
	pronounciations[0].weight[6] = 0.0;
	pronounciations[0].weight[7] = 0.0;
	pronounciations[0].weight[8] = 0.0;
	pronounciations[0].weight[9] = 0.0;
	pronounciations[0].weight[10] = 0.0;
	pronounciations[0].weight[11] = 0.0;
	pronounciations[0].weight[12] = 0.0;
	pronounciations[0].weight[13] = 0.0;
	pronounciations[0].weight[14] = 0.0;
	pronounciations[0].weight[15] = 0.0;

	// �� �߰� ( ���� �ٹ� )

	pronounciations[1].name = "01";

	pronounciations[1].weight[0] = 0.0;
	pronounciations[1].weight[1] = 0.0;
	pronounciations[1].weight[2] = 0.0;
	pronounciations[1].weight[3] = 0.0;
	pronounciations[1].weight[4] = 0.0;
	pronounciations[1].weight[5] = 0.0;
	pronounciations[1].weight[6] = 0.0;
	pronounciations[1].weight[7] = 0.0;
	pronounciations[1].weight[8] = 0.0;
	pronounciations[1].weight[9] = 0.0;
	pronounciations[1].weight[10] = 0.0;
	pronounciations[1].weight[11] = 0.0;
	pronounciations[1].weight[12] = 0.0;
	pronounciations[1].weight[13] = 0.0;
	pronounciations[1].weight[14] = 20.0;
	pronounciations[1].weight[15] = 0.0;



	pronounciations[2].name = "a";

	pronounciations[2].weight[0] = 0.0;
	pronounciations[2].weight[1] = 0.0;
	pronounciations[2].weight[2] = 0.0;
	pronounciations[2].weight[3] = 0.0;
	pronounciations[2].weight[4] = 0.0;
	pronounciations[2].weight[5] = 0.0;
	pronounciations[2].weight[6] = 0.0;
	pronounciations[2].weight[7] = 0.0;
	pronounciations[2].weight[8] = 0.0;
	pronounciations[2].weight[9] = 0.0;
	pronounciations[2].weight[10] = 0.0;
	pronounciations[2].weight[11] = 0.0;
	pronounciations[2].weight[12] = 0.0;
	pronounciations[2].weight[13] = 0.0;
	pronounciations[2].weight[14] = 100.0;
	pronounciations[2].weight[15] = 0.0;


	pronounciations[3].name = "e";

	pronounciations[3].weight[0] = 0.0;
	pronounciations[3].weight[1] = 0.0;
	pronounciations[3].weight[2] = 0.0;
	pronounciations[3].weight[3] = 0.0;
	pronounciations[3].weight[4] = 0.0;
	pronounciations[3].weight[5] = 0.0;
	pronounciations[3].weight[6] = 0.0;
	pronounciations[3].weight[7] = 0.0;
	pronounciations[3].weight[8] = 0.0;
	pronounciations[3].weight[9] = 0.0;
	pronounciations[3].weight[10] = 50.0;
	pronounciations[3].weight[11] = 50.0;
	pronounciations[3].weight[12] = 0.0;
	pronounciations[3].weight[13] = 0.0;
	pronounciations[3].weight[14] = 40.0;
	pronounciations[3].weight[15] = 0.0;


	pronounciations[4].name = "i";

	pronounciations[4].weight[0] = 0.0;
	pronounciations[4].weight[1] = 0.0;
	pronounciations[4].weight[2] = 0.0;
	pronounciations[4].weight[3] = 0.0;
	pronounciations[4].weight[4] = 0.0;
	pronounciations[4].weight[5] = 0.0;
	pronounciations[4].weight[6] = 0.0;
	pronounciations[4].weight[7] = 0.0;
	pronounciations[4].weight[8] = 0.0;
	pronounciations[4].weight[9] = 0.0;
	pronounciations[4].weight[10] = 80.0;
	pronounciations[4].weight[11] = 80.0;
	pronounciations[4].weight[12] = 0.0;
	pronounciations[4].weight[13] = 0.0;
	pronounciations[4].weight[14] = 20.0;
	pronounciations[4].weight[15] = 0.0;


	pronounciations[5].name = "o";

	pronounciations[5].weight[0] = 0.0;
	pronounciations[5].weight[1] = 0.0;
	pronounciations[5].weight[2] = 0.0;
	pronounciations[5].weight[3] = 0.0;
	pronounciations[5].weight[4] = 0.0;
	pronounciations[5].weight[5] = 0.0;
	pronounciations[5].weight[6] = 0.0;
	pronounciations[5].weight[7] = 0.0;
	pronounciations[5].weight[8] = 0.0;
	pronounciations[5].weight[9] = 0.0;
	pronounciations[5].weight[10] = 0.0;
	pronounciations[5].weight[11] = 0.0;
	pronounciations[5].weight[12] = 0.0;
	pronounciations[5].weight[13] = 100.0;
	pronounciations[5].weight[14] = 60.0;
	pronounciations[5].weight[15] = 0.0;
		

	pronounciations[6].name = "u";

	pronounciations[6].weight[0] = 0.0;
	pronounciations[6].weight[1] = 0.0;
	pronounciations[6].weight[2] = 0.0;
	pronounciations[6].weight[3] = 0.0;
	pronounciations[6].weight[4] = 0.0;
	pronounciations[6].weight[5] = 0.0;
	pronounciations[6].weight[6] = 0.0;
	pronounciations[6].weight[7] = 0.0;
	pronounciations[6].weight[8] = 0.0;
	pronounciations[6].weight[9] = 0.0;
	pronounciations[6].weight[10] = 0.0;
	pronounciations[6].weight[11] = 0.0;
	pronounciations[6].weight[12] = 80.0;
	pronounciations[6].weight[13] = 100.0;
	pronounciations[6].weight[14] = 60.0;
	pronounciations[6].weight[15] = 0.0;
		

	pronounciations[7].name = "y";

	pronounciations[7].weight[0] = 0.0;
	pronounciations[7].weight[1] = 0.0;
	pronounciations[7].weight[2] = 0.0;
	pronounciations[7].weight[3] = 0.0;
	pronounciations[7].weight[4] = 0.0;
	pronounciations[7].weight[5] = 0.0;
	pronounciations[7].weight[6] = 0.0;
	pronounciations[7].weight[7] = 0.0;
	pronounciations[7].weight[8] = 0.0;
	pronounciations[7].weight[9] = 0.0;
	pronounciations[7].weight[10] = 50.0;
	pronounciations[7].weight[11] = 50.0;
	pronounciations[7].weight[12] = 0.0;
	pronounciations[7].weight[13] = 0.0;
	pronounciations[7].weight[14] = 10.0;
	pronounciations[7].weight[15] = 0.0;

	pronounciations[8].name = "m";

	pronounciations[8].weight[0] = 0.0;
	pronounciations[8].weight[1] = 0.0;
	pronounciations[8].weight[2] = 0.0;
	pronounciations[8].weight[3] = 0.0;
	pronounciations[8].weight[4] = 0.0;
	pronounciations[8].weight[5] = 0.0;
	pronounciations[8].weight[6] = 0.0;
	pronounciations[8].weight[7] = 0.0;
	pronounciations[8].weight[8] = 0.0;
	pronounciations[8].weight[9] = 0.0;
	pronounciations[8].weight[10] = 0.0;
	pronounciations[8].weight[11] = 0.0;
	pronounciations[8].weight[12] = 0.0;
	pronounciations[8].weight[13] = 0.0;
	pronounciations[8].weight[14] = 100.0;
	pronounciations[8].weight[15] = 0.0;


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

	// 'hello', 'merry'�� ���� e�� ������ ���ڻ��̿� ������ ���� ����
	for(int k=0;k<sentence.size()-3;k++){//?
		 
		if(sentence[k] == 'e' && 
			(sentence[k+1] != ' ' && sentence[k+1] != '.' ) &&
			(sentence[k+2] != ' ' && sentence[k+2] != '.' ) &&
			(transSentence[k+3] != 1 && transSentence[k+3] != 0)){
						
				transSentence[k+1] = transSentence[k];
				transSentence[k+2] = transSentence[k+3];

		}
	}

	//// 'name'���� m�� a�� ����
	//for(int k=1;k<sentence.size()-1;k++){

	//		
	//	if(sentence[k-1] == 'a' && sentence[k+1] == 'e' ){
	//				
	//		transSentence[k] = 2;

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

		if(this_condition_end == false && transSentence[k] == 1){
			transSentence[k] = 0;
		}else{
			this_condition_end = true;
		}
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

	// ǥ�� �±���'(', ')'�� ǥ�� ������ ����
	for(int k=0;k<sentence.size()-1;k++){
						
		if(sentence[k] == '('){
			transSentence[k] = transSentence[k+1];
		}
		if(sentence[k] == ')'){
			transSentence[k] = transSentence[k-1];
		}
	}

	for(int k=0;k<sentence.size();k++){

		FILE* fp = fopen("1111.txt","at+");
		fprintf(fp,"%d   \n", transSentence[k] );
		fclose(fp);

	}

}

int Speaking::matchPronounciationIdx(char letter){

	// ���� ���� Ư�� ���ĺ��� idx ������ ��ȯ

	int index = 1; // �⺻ ���� : �������� ���� ����, ����(����), ��ħǥ ��

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
			emotionTagFlag = true;
			break;
		//default :
		//	// �������� ���� ����, ����(����), ��ħǥ ��
		//	index = 1;
		//	break;
		}
	}else{ // emotionTagFlag == true

		if(letter == ')'){
			emotionTagFlag = false;
		}
		else{
			index = int(letter - '0') * (-1);
		}
	}

	return index;
}


int Speaking::setCharAtTime(DWORD diff)
{
	// �ִϸ��̼� ��� �ð��� input���� �޾Ƽ� ����, ����, ������ � ���ڸ� ���ϴ����� ����Ͽ� ��ȯ�ϴ� �Լ�
	
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);

	if(diff <= ( sentence.size() + (introBlockNum*2) ) * speed ){   
	
		if((int)diff < introTime){

			// �� ó�� ���� block��
			preIdx = matchPronounciationIdx('0');
			currIdx = matchPronounciationIdx('0');

		}else if((int)diff >= introTime && (int)diff <= introTime + speed){

			// �� ù����
			preIdx = matchPronounciationIdx('0');
			currIdx = transSentence[0];
	
		}else if( (int)diff >= ((sentence.size() + introBlockNum) * speed)
			&& ( (int)diff < ((sentence.size() + introBlockNum + 1) * speed) )){

			// �� ������ ���� ���� block

			preIdx = transSentence[diff/speed - (introBlockNum + 1) ];	
			currIdx= matchPronounciationIdx('0');

		}else if( (int)diff >= ((sentence.size() + introBlockNum + 1) * speed) ){

			// �� ������ ���� block��
			preIdx = matchPronounciationIdx('0');
			currIdx = matchPronounciationIdx('0');	
			
		}else{

			//------------------------------------------------------------------------------------ ������
				
			preIdx = transSentence[diff/speed - (introBlockNum + 1) ];	
			currIdx = transSentence[diff/speed - introBlockNum ];	
				

		}	

		if(currIdx<0){
			int a = 0;
			a +=1;
		}
		return currIdx;

	}else{

		//animation end ���� 
		pView->animationFlag = false;
		pView->getStartTime = true;

		pView->speaking.transSentence.clear();
		pView->speaking.sentence.clear();

		CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
		pFrame->m_wndSplitter.SetActivePane(0, 1);
		ControllerView* controller = (ControllerView*)pFrame->GetActiveView();

		// �ִϸ��̼� ���� �� default�� ����				
		controller->expressionList.SetCurSel(0);

		for(int i = 0; i < sizeof(controller->tempExpression.weight)/sizeof(float); i++){
		
			controller->tempExpression.weight[i] = pView->emotion.emotions[0].weight[i];
		
		}
		// �ִϸ��̼� ������ ���� ǥ������ ���ư��� ����� �����غ���.

	}	

	return 0;
}

void Speaking::setWeightAtTime(DWORD diff)
{

	if(diff%(int)speed <= speed/2.0){

		preWeight = - (abs( (float)(diff%(int)speed) + speed/2.0) * 1.0/speed) + 1.0;
		currWeight = - (abs( (float)(diff%(int)speed) - speed/2.0 ) * 1.0/speed) + 1.0;

	}else{

		preWeight = 0.0;
		currWeight = 1.0;

	}
			
	
}


void Speaking::calCurrLook(void){

	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	ControllerView* controller = (ControllerView*)pFrame->GetActiveView();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);

	Expression preExp;
	Expression currExp;

	// idx�� ������ ���� �� ��� ���� �� ǥ�� �±׿� ���� ���� ǥ�� ���̴�.
	// �׷��Ƿ� emotion module���� ǥ���� ������ spk ǥ������ ��ȯ�Ѵ�.

	if(preIdx<0)	preExp = pView->emotion.emotions[abs(preIdx)];
	else	preExp = pronounciations[preIdx];

	if(currIdx<0)	currExp = pView->emotion.emotions[abs(currIdx)];
	else	currExp = pronounciations[currIdx];
	
	for(int i=0;i<16;i++){ // � ������ ���ϴ� ǥ���� �����. ���� ���� ���� ���� ����.

		nowLook.weight[i] = preExp.weight[i] * preWeight + currExp.weight[i] * currWeight;

	}
	
}