#pragma once
#include "stdafx.h"

class ClipboardMan {
public:
	void RetrieveClipboardText();
	
private:
	void TurnClipboardTextToFile(const std::wstring& text);
	std::string sSaveFileToTempFolder(const std::wstring& text);
	std::string sGenerateFileNameBasedOnTime();
};