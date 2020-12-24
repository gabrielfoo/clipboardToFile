#include "stdafx.h"
#include "ClipboardToTextmain.h"
#include "KeyStrokeCombo.h"
#include "ClipboardAPIHandler.h"


std::atomic<bool> atomicboolKeepThreadAlive = true;

void sendKeyWithSendInput(const WORD key, const bool iskeystrokeUp);
void CtrlVtoActiveWindow();


int real_main() {

	//SetConsoleOutputCP(CP_UTF8);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);
	KeyStrokeCombo CTRLSHIFTVCombo(VK_CONTROL, VK_SHIFT, 'V');
	//AllocConsole();
	ClipboardAPIHandler clip;
	
	while (atomicboolKeepThreadAlive) {

		if (CTRLSHIFTVCombo.isKeyComboPressed())
		{
			clip.RetrieveClipboardData();
			Sleep(500);
			CtrlVtoActiveWindow();
			Sleep(1000);
		}
		Sleep(4);
	}
	return 0;
}


void CtrlVtoActiveWindow()
{
	sendKeyWithSendInput(VK_CONTROL, false);
	sendKeyWithSendInput('V', false);
	sendKeyWithSendInput(VK_CONTROL, true);
	sendKeyWithSendInput('V', true);
}


void sendKeyWithSendInput(const WORD key, const bool iskeystrokeUp)
{
	INPUT input = { 0 };
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;

	iskeystrokeUp? input.ki.dwFlags |= KEYEVENTF_KEYUP : input.ki.dwFlags = 0;

	SendInput(1, &input, sizeof(input));
}


