#pragma once


class KeyStrokeCombo
{
	const char keystroke1;
	const char keystroke2;
	const char keystroke3;

public:
	KeyStrokeCombo(const char key1, const char key2 = NULL, const char key3 = NULL);
	bool isKeyComboPressed();
		
};