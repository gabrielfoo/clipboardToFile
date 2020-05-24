#include "stdafx.h"
#include "ClipboardReader.h"
#define UNICODE
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <locale>
#include <ShlObj_core.h>
#include <fcntl.h>
#include <io.h>



void ClipboardMan::RetrieveClipboardData()
{
	HGLOBAL cbuf;
	const wchar_t *ptr;
	std::wstring sClipboardText;

	if (IsClipboardFormatAvailable(CF_UNICODETEXT)) { //if not found, will return and do a Ctrl-V nevertheless
		if (OpenClipboard(NULL))
		{
			cbuf = GetClipboardData(CF_UNICODETEXT);

			ptr = (const wchar_t*)GlobalLock(cbuf);
			
			sClipboardText = ptr;

			GlobalUnlock(cbuf);
			TurnClipboardTextToFile(sClipboardText);
			CloseClipboard();
		}

	}
}

void ClipboardMan::TurnClipboardTextToFile(const std::wstring& text)
{
	//put filePath into a char buffer for legacy API compatibility
	std::string sFilePath = sSaveFileToTempFolder(text);
	int iLengthOfFilePath = sFilePath.length() + 2;
	std::unique_ptr<char> pszFiles(new char[iLengthOfFilePath]());
	sprintf(pszFiles.get(), "%s", sFilePath.c_str());
	
	//put the file path into clipboard by initializing DROPFILES struct and putting filepath into pData member
	int nSize = sizeof(DROPFILES) + iLengthOfFilePath;
	HANDLE hData = ::GlobalAlloc(GHND, nSize);
	LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock(hData);
	pDropFiles->pFiles = sizeof(DROPFILES);

	//if fileName is UNICODE, change to TRUE
	pDropFiles->fWide = FALSE;

	LPBYTE pData = (LPBYTE)pDropFiles + sizeof(DROPFILES);
	::CopyMemory(pData, pszFiles.get(), iLengthOfFilePath);
	::GlobalUnlock(hData);
	::EmptyClipboard();
	::SetClipboardData(CF_HDROP, hData);

	
}

//Purpose:
//Saves text from Clipboard into Temp file and returns string to filepath
std::string ClipboardMan::sSaveFileToTempFolder(const std::wstring& text)
{
	std::string sWindowsTempFolderPath = std::filesystem::temp_directory_path().string();
	std::ofstream myfile;

	std::string sTempFileNameWithTempFolder = sWindowsTempFolderPath+ sGenerateFileNameBasedOnTime();

	_setmode(_fileno(stdout), _O_U8TEXT);//wcout instead of cout
	std::locale loc_utf8(std::locale(), new std::codecvt_utf8<wchar_t>);
	std::wofstream fout(sTempFileNameWithTempFolder, std::ios::binary);

	try
	{
		if (fout)
		{
			fout.imbue(loc_utf8);
			fout << text;
			fout.close();
		}
	}
	catch (std::exception const & ex)
	{
		std::cerr << ex.what() << std::endl;
	}


	return sTempFileNameWithTempFolder;
}

std::string ClipboardMan::sGenerateFileNameBasedOnTime()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "text_%Y-%m-%d_%H-%M-%S.txt");//filename: text_YYYY-MM-DD-HH-MM-SS.txt

	return ss.str();

}