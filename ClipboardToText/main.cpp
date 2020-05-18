#include "stdafx.h"

#include "KeyStrokeCombo.h"
#include "ClipboardReader.h"



void sendKeyWithSendInput(const WORD key, const bool iskeystrokeUp);
void CtrlVtoActiveWindow();




int main() {


	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);
	std::cout << "ClipboardToText start" << std::endl;
	//FreeConsole();
	KeyStrokeCombo ActivationKeyCombo(VK_CONTROL, VK_SHIFT, 'V');

	ClipboardMan clip;
	
	
	while (true) {

		if (ActivationKeyCombo.isKeyComboPressed())
		{
			clip.RetrieveClipboardText();
			Sleep(500);
			CtrlVtoActiveWindow();
			Sleep(1000);

		}

	}

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


