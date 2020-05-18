#include "stdafx.h"
#include "KeyStrokeCombo.h"

//TODO: must do checks for NULL
KeyStrokeCombo::KeyStrokeCombo(char key1, char key2 /*= NULL*/ , char key3 /*= NULL*/):
	keystroke1(key1),keystroke2(key2),keystroke3(key3)
{}

bool KeyStrokeCombo::isKeyComboPressed()
{
	if (GetAsyncKeyState(keystroke1) & 0x8000)
	{
		if (GetAsyncKeyState(keystroke2) & 0x8000)
		{
			if (GetAsyncKeyState(keystroke3) & 0x8000)
			{
				return true;
			}
				
		}
	}
	
	return false;
}