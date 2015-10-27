#pragma once
#include <sapi.h>
#include <vector>

class SAPI {
	int Volume;
	int Rate;
	ISpVoice *pVoice;

public:
	SAPI() {
		pVoice = NULL;
		Volume = 100;
		Rate = 0;
	}

	BOOL Initialize() {

		if (FAILED(::CoInitialize(NULL)))
			return FALSE;

		HRESULT hr = CoCreateInstance(
			CLSID_SpVoice,
			NULL,
			CLSCTX_ALL,
			IID_ISpVoice,
			(void **)&pVoice);

		if (FAILED(hr))	return FALSE;

		pVoice->SetVolume(Volume);
		pVoice->SetRate(Rate);

		return TRUE;
	}

	VOID SetVolume(int vol) {

		if (vol <= 0) {
			vol = 0;
		}
		else if (vol >= 100) {
			vol = 100;
		}
		Volume = vol;
		pVoice->SetVolume(Volume);
	}

	VOID SetSpeed(int rate) {
		if (rate <= -10) {
			rate = -10;	
		}
		else if (rate >= 10) {
			rate = 10;
		}
		Rate = rate;
		pVoice->SetRate(Rate);
	}

	int GetVolume() { return Volume; }
	int GetSpeed() { return Rate; }

	BOOL Speaking(const wchar_t *str) {
		if (!pVoice)
			return FALSE;

		HRESULT hr = pVoice->Speak(str, 0, NULL);
		if (FAILED(hr))
			return FALSE;

		return TRUE;
	}
	
	virtual ~SAPI() {
		if (pVoice) {
			pVoice->Release();
			pVoice = NULL;
		}

		::CoUninitialize();
			
	}




};