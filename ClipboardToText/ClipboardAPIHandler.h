#pragma once
#ifndef CLIPBOARD_READER_H 
#define	CLIPBOARD_READER_H 

#include "stdafx.h"
#include "ClipboardReaderFactory.h"
#include "DataToFile.h"

class ClipboardAPIHandler {
public:
	void RetrieveClipboardData();
	
private:
	void ClipboardAPIHandler::PutFileLocationIntoClipboard(const std::string& sFilePath);
	void ClipboardToFileToClipboardOperation(const void* clipboardData, const std::unique_ptr <DataToFileFactory>& SaveDataStrategy);
	const void* AcquireClipboardData(const unsigned int& PredefinedClipboardFormat);
	//std::string sSaveFileToTempFolder(const std::wstring& text);
	//std::string sGenerateFileNameBasedOnTime();
};

#endif