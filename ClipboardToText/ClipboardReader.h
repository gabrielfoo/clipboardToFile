#pragma once
#ifndef CLIPBOARD_READER_H 
#define	CLIPBOARD_READER_H 

#include "stdafx.h"

class ClipboardMan {
public:
	void RetrieveClipboardData();
	
private:
	void TurnClipboardTextToFile(const std::wstring& text);
	std::string sSaveFileToTempFolder(const std::wstring& text);
	std::string sGenerateFileNameBasedOnTime();
};

#endif