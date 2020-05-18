#include "stdafx.h"
#include "ClipboardReader.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <ShlObj_core.h>


void ClipboardMan::RetrieveClipboardText()
{
	HGLOBAL cbuf;
	const char *ptr;
	std::string sClipboardText;

	if (IsClipboardFormatAvailable(CF_TEXT)) {
		if (OpenClipboard(NULL))
		{
			cbuf = GetClipboardData(CF_TEXT);

			ptr = (const char*)GlobalLock(cbuf);
			sClipboardText = ptr;
			GlobalUnlock(cbuf);
			TurnClipboardTextToFile(sClipboardText);
			CloseClipboard();
		}


	}

}

void ClipboardMan::TurnClipboardTextToFile(const std::string& text)
{
	std::string sFilePath = sSaveFileToTempFolder(text);
	

	const char* sFiles = sFilePath.c_str();

	DROPFILES dobj = { 20, { 0, 0 }, 0, 1 };
	int nLen = sFilePath.length()+1;
	int nGblLen = sizeof(dobj) + nLen * 2 + 5;//lots of nulls and multibyte_char
	HGLOBAL hGbl = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE, nGblLen);
	char* sData = (char*)::GlobalLock(hGbl);
	memcpy(sData, &dobj, 20);
	char* sWStr = sData + 20;
	for (int i = 0; i < nLen * 2; i += 2)
	{
		sWStr[i] = sFiles[i / 2];
	}
	::GlobalUnlock(hGbl);
	EmptyClipboard();
	SetClipboardData(CF_HDROP, hGbl);

	
}

//Purpose:
//Saves text from Clipboard into Temp file and returns string to filepath
std::string ClipboardMan::sSaveFileToTempFolder(const std::string& text)
{
	std::string sWindowsTempFolderPath = std::filesystem::temp_directory_path().string();
	std::ofstream myfile;

	std::string sTempFileName = sGenerateFileNameBasedOnTime();

	myfile.open(sWindowsTempFolderPath + sTempFileName);
	myfile.write(text.c_str(), text.length() + 1);
	myfile.close();

	std::string sMyFilePath = sWindowsTempFolderPath + sTempFileName;

	return sMyFilePath;
}

std::string ClipboardMan::sGenerateFileNameBasedOnTime()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "text_%Y-%m-%d_%H_%M_%S.txt");

	return ss.str();

}