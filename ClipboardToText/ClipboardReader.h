#pragma once
#include "stdafx.h"

class ClipboardMan {
public:
	void RetrieveClipboardText();
	
private:
	void TurnClipboardTextToFile(const std::string& text);
	std::string sSaveFileToTempFolder(const std::string& text);
	std::string sGenerateFileNameBasedOnTime();
};