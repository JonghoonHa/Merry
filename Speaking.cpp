#include "stdafx.h"
#include "Speaking.h"
#include "MerryView.h"
#include "ControllerView.h"
#include "SAPI.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

Speaking::Speaking(void){
}
Speaking::Speaking(float _speed, int _introBlockNum)
{
	speed = _speed;
	introBlockNum = _introBlockNum;

	preIdx = 0; currIdx = 0; nextIdx = 0;
	preWeight = 0.0; currWeight = 0.0; nextWeight = 0.0;

	//-----------------------------------------------

	// 발음 표정 생성

	//완전 다뭄
	float tWeight0[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	Expression tTemp0("0", tWeight0);
	pronounciations.push_back(tTemp0);

	// 말 중간 ( 조금 다뭄 )
	float tWeight1[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0, 0.0};
	Expression tTemp1("1", tWeight1);
	pronounciations.push_back(tTemp1);

	//æ[애]
	float tWeight2[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 40.0, 40.0, 0.0, 0.0, 30.0, 0.0 };
	Expression tTemp2("2", tWeight2);
	pronounciations.push_back(tTemp2);

	//p[ㅍ]
	float tWeight3[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	Expression tTemp3("3", tWeight3);
	pronounciations.push_back(tTemp3);

	//?[어]
	float tWeight4[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 60.0, 40.0, 0.0 };
	Expression tTemp4("4", tWeight4);
	pronounciations.push_back(tTemp4);

	//l[ㄹ]
	float tWeight5[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 15.0, 0.0 };
	Expression tTemp5("5", tWeight5);
	pronounciations.push_back(tTemp5);

	//b[ㅂ]
	float tWeight6[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 60.0, 30.0, 0.0 };
	Expression tTemp6("6", tWeight6);
	pronounciations.push_back(tTemp6);

	//n[ㄴ]
	float tWeight7[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 30.0, 20.0, 0.0 };
	Expression tTemp7("7", tWeight7);
	pronounciations.push_back(tTemp7);

	//m[ㅁ]
	float tWeight8[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0, 0.0 };
	Expression tTemp8("8", tWeight8);
	pronounciations.push_back(tTemp8);

	//a[아]
	float tWeight9[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 50.0, 0.0 };
	Expression tTemp9("9", tWeight9);
	pronounciations.push_back(tTemp9);

	//?[이]
	float tWeight10[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 10.0, 0.0, 0.0, 20.0, 0.0 };
	Expression tTemp10("10", tWeight10);
	pronounciations.push_back(tTemp10);

	//e[에]
	float tWeight11[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0, 20.0, 0.0, 0.0, 40.0, 0.0 };
	Expression tTemp11("11", tWeight11);
	pronounciations.push_back(tTemp11);

	//z[ㅈ]
	float tWeight12[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0, 0.0 };
	Expression tTemp12("12", tWeight12);
	pronounciations.push_back(tTemp12);

	//r[ㄹ]
	float tWeight13[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 70.0, 20.0, 0.0 };
	Expression tTemp13("13", tWeight13);
	pronounciations.push_back(tTemp13);

	//i[이]
	float tWeight14[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 50.0, 50.0, 0.0, 0.0, 20.0, 0.0 };
	Expression tTemp14("14", tWeight14);
	pronounciations.push_back(tTemp14);

	//s[ㅅ]
	float tWeight15[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 30.0, 0.0 };
	Expression tTemp15("15", tWeight15);
	pronounciations.push_back(tTemp15);

	//t[ㅌ]
	float tWeight16[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 80.0, 30.0, 0.0 };
	Expression tTemp16("16", tWeight16);
	pronounciations.push_back(tTemp16);

	//?;[어]
	float tWeight17[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 30.0, 0.0 };
	Expression tTemp17("17", tWeight17);
	pronounciations.push_back(tTemp17);

	//i:[이]
	float tWeight18[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 30.0, 30.0, 0.0, 0.0, 20.0, 0.0 };
	Expression tTemp18("18", tWeight18);
	pronounciations.push_back(tTemp18);

	//j[이]
	float tWeight19[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 50.0, 70.0, 20.0, 0.0 };
	Expression tTemp19("19", tWeight19);
	pronounciations.push_back(tTemp19);

	//w[우]
	float tWeight20[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 70.0, 20.0, 0.0 };
	Expression tTemp20("20", tWeight20);
	pronounciations.push_back(tTemp20);

	//h[ㅎ]
	float tWeight21[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 70.0, 70.0, 0.0, 0.0, 30.0, 0.0 };
	Expression tTemp21("21", tWeight21);
	pronounciations.push_back(tTemp21);

	//o?[오우]
	float tWeight22[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 50.0, 80.0, 30.0, 0.0 };
	Expression tTemp22("22", tWeight22);
	pronounciations.push_back(tTemp22);

	//?i[아이]
	float tWeight23[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 50.0, 0.0 };
	Expression tTemp23("23", tWeight23);
	pronounciations.push_back(tTemp23);

	//d[ㄷ]
	float tWeight24[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 0.0 };
	Expression tTemp24("24", tWeight24);
	pronounciations.push_back(tTemp24);

	//?[우]
	float tWeight25[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 15.0, 80.0, 20.0, 0.0 };
	Expression tTemp25("25", tWeight25);
	pronounciations.push_back(tTemp25);

	//k[ㅋ]
	float tWeight26[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 10.0, 0.0, 50.0, 50.0, 0.0 };
	Expression tTemp26("26", tWeight26);
	pronounciations.push_back(tTemp26);

	//?[어]
	float tWeight27[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 80.0, 30.0, 0.0 };
	Expression tTemp27("27", tWeight27);
	pronounciations.push_back(tTemp27);

	//v[ㅂ]
	float tWeight28[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 30.0, 30.0, 20.0, 0.0 };
	Expression tTemp28("28", tWeight28);
	pronounciations.push_back(tTemp28);

	//ð[ㄷ]
	float tWeight29[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 40.0, 0.0 };
	Expression tTemp29("29", tWeight29);
	pronounciations.push_back(tTemp29);

	//?[쉬]
	float tWeight30[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 80.0, 80.0, 10.0, 0.0 };
	Expression tTemp30("30", tWeight30);
	pronounciations.push_back(tTemp30);

	//g[ㄱ]
	float tWeight31[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 0.0 };
	Expression tTemp31("31", tWeight31);
	pronounciations.push_back(tTemp31);

	//3:[ㅓ]
	float tWeight32[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0, 30.0, 0.0 };
	Expression tTemp32("32", tWeight32);
	pronounciations.push_back(tTemp32);

	//a?[아우]
	float tWeight33[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 100.0, 10.0, 0.0 };
	Expression tTemp33("33", tWeight33);
	pronounciations.push_back(tTemp33);

	//f[ㅍ]
	float tWeight34[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 30.0, 70.0, 30.0, 0.0 };
	Expression tTemp34("34", tWeight34);
	pronounciations.push_back(tTemp34);

	//u:[우]
	float tWeight35[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 70.0, 10.0, 0.0 };
	Expression tTemp35("35", tWeight35);
	pronounciations.push_back(tTemp35);

	//?:[아]
	float tWeight36[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 50.0, 0.0 };
	Expression tTemp36("36", tWeight36);
	pronounciations.push_back(tTemp36);

	//[움]
	float tWeight37[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 30.0, 30.0, 0.0, 0.0 };
	Expression tTemp37("37", tWeight37);
	pronounciations.push_back(tTemp37);


	
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
	
	/*
	sentence를 구성하는 각 단어들마다 pronunciation_dic.txt에서 찾아서
	해당 단어의 번호와 매칭시켜줌	
	*/
	
	
	
	
	string index_bucket = matchPronounciationIdx(sentence);

	int pending = 0;
	int pending2 = 0;
	char pendingWord = NULL;

	ofstream out3;
	out3.open("t14.txt");
	out3 << index_bucket << endl;

	//발음기호단어의 사이즈만큼 trnasSentecnce에 push
	for (int i = 0;i < index_bucket.size();i++) {

		char one = index_bucket.at(i);
		
		if (one == ',') {
			pending = 1;
			continue;
		}
		else if (one == '-') {
			pending2 = 1;
			continue;
		}
		else {
			if (pending == 1) {
				pendingWord = one;
				pending = 0;
				continue;
			}
			else {
							
				if (pendingWord == NULL) {		

					if (pending2 == 1) {
						transSentence.push_back(-((int)one - '0'));
						pending2 = 0;
					}
					else {
						transSentence.push_back((int)one - '0');
					}
									
				}
				else {
					char two_word[2];
					two_word[0] = pendingWord;
					two_word[1] = one;

					string two_word_f;
					two_word_f += two_word[0];
					two_word_f += two_word[1];

					char* myBuffer = new char[2];
					std::strcpy(myBuffer, two_word_f.c_str());
										
					transSentence.push_back((atoi)(myBuffer)); //two_word라는 string형을 int로 변환하여 저장

					pendingWord = NULL;			
					pending = 0;
				}
				
			}
			
		}

	}

	for (int i = 0;i < transSentence.size();i++)
		out3 << transSentence[i] << endl;

}

std::string Speaking::matchPronounciationIdx(vector<char> word){

	string inLineBuf;	//한 줄
	string header;
	string x, y, z;
	string return_val;

	// 문장 속의 특정 알파벳을 idx 값으로 변환

	int token_num = 0;
	for (int i = 0;i < word.size();i++) {
		if (word[i] == ' ')	token_num++;
	}

	ofstream out3;
	out3.open("t15.txt");
	out3 << token_num << endl;


	std::string* word_formatString = new std::string[token_num + 1];

	int start = 0;
	for (int i = 0;i < word.size();i++) {

		if (word[i] != ' ')	word_formatString[start] += word[i];
		else
		{
			start++;
		}
	}
	//--------------------------------------------------------------------------------
	// ex, my name is merry 의 각 단어가 word_formatString[]에 각각 저장되어 있는 상태
	//--------------------------------------------------------------------------------



	ifstream DATAFile("pronunciationDic.txt");
	if (DATAFile.fail()) {
		return "fail";
	}
	
	
	for (int i = 0;i < token_num + 1;i++) {

		if (word_formatString[i].at(0) == '(') {

			return_val += "0";
			return_val += "-";
			return_val += word_formatString[i].at(1);
			return_val += "0";
			
			continue;

		}


		while (!DATAFile.eof()) {

			//out3 << return_val <<endl;

			getline(DATAFile, inLineBuf);		//한 줄씩 읽어들이기
			istringstream inLine(inLineBuf);

			if (inLineBuf.length() > 0) {

				inLine >> header;

				if (header == "#") {	//주석영역
				}
				else if (header == "*") {

					inLine >> x >> y >> z;

					if (x == word_formatString[i]) {

						return_val += z;
						DATAFile.seekg(SEEK_SET);
						
						break;
					}
				}
			}
		}
		


	}

	
	return return_val;
}


void Speaking::setCharAtTime(DWORD diff)
{
	// 애니메이션 경과 시간을 input으로 받아서 이전, 현재, 다음에 어떤 글자를 말하는지를 계산하여 반환하는 함수
	
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMerryView* pView  = (CMerryView *)pFrame->m_wndSplitterSub.GetPane(0, 0);
	ControllerView* controller = (ControllerView*)pFrame->m_wndSplitter.GetPane(0,1);

	const int introTime = introBlockNum * speed;
	int currBlockNum = diff/speed;

	if(diff <= ( transSentence.size() + (introBlockNum*2) ) * speed ){  
	
		if(currBlockNum<introBlockNum){

			// 맨 처음 공백 block들
			preIdx = 0;
			currIdx = 0;

		}else if(currBlockNum>=introBlockNum && currBlockNum< introBlockNum+1){

			// 맨 첫글자
			preIdx = 0;
			currIdx = transSentence[0];
	
		}else if(/* (int)diff >= ((sentence.size() + introBlockNum) * speed)
			&& ( (int)diff < ((sentence.size() + introBlockNum + 1) * speed) )*/
			currBlockNum >= introBlockNum + transSentence.size() && currBlockNum<introBlockNum + transSentence.size()+1){

			// 맨 마지막 글자 다음 block

			preIdx = transSentence[diff/speed - introBlockNum - 1 ];	
			currIdx = 0;

		}else if( /*(int)diff >= ((sentence.size() + introBlockNum + 1) * speed)*/currBlockNum >= introBlockNum + transSentence.size()+1 ){

			// 맨 마지막 공백 block들
			preIdx = 0;
			currIdx = 0;
			
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

	if(preIdx >= 0) preExp = pronounciations[preIdx];
	if(currIdx >= 0) currExp = pronounciations[currIdx];
	
	for(int i=0;i<pDoc->units.size();i++){ // 어떤 순간의 말하는 표정의 결과물. 이전 값과 현재 값의 조합.

		nowLook.weight[i] = preExp.weight[i] * preWeight + currExp.weight[i] * currWeight;

	}
	
}

UINT Speaking::voice(LPVOID IParam) {

	SAPI ap;
	if (ap.Initialize()) {

		ap.SetSpeed(-4);
		ap.SetVolume(100);
		
		char* buf = (char*)IParam;
		
		/*ofstream out;
		out.open("output1.txt");
				
		out << buf;
		out.close();*/
		
		//char* -> wchar_t*형 형변환
		wchar_t* wc;
		int strSize = MultiByteToWideChar(CP_ACP, 0, buf, -1, NULL, NULL);
		wc = new WCHAR[strSize];
		MultiByteToWideChar(CP_ACP, 0, buf, strlen(buf) + 1, wc, strSize);	//형변환

		Sleep(5000);		

		//ap.Speaking(wc);
		delete[] wc;
	}

	return 0;
	
}