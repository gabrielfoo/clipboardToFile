#include "stdafx.h"
#include "ClipboardAPIHandler.h"
#define UNICODE

#include <ShlObj_core.h>



//Purpose:
//this class will directly talk to the Windows API. Code for this should be left alone as much as possible, as the API is not easy to handle. Non-Windows API operations should be delegated to other classes as much as possible
void ClipboardAPIHandler::RetrieveClipboardData()
{
	
	const void* clipboard_ptr = nullptr;

	if (::IsClipboardFormatAvailable(CF_UNICODETEXT)) 
	{ 
		if (::OpenClipboard(NULL))
		{
			clipboard_ptr = AcquireClipboardData(CF_UNICODETEXT);

			ClipboardToFileToClipboardOperation(clipboard_ptr, DataToFileFactory::createChosenFileSaveProduct(Choice_TextToFile));

			::GlobalUnlock(GlobalHandle((HGLOBAL)clipboard_ptr));
			::CloseClipboard();
		}

	}
	else if (::IsClipboardFormatAvailable(CF_BITMAP) || ::IsClipboardFormatAvailable(CF_DIB) || ::IsClipboardFormatAvailable(CF_DIBV5))
	{
		if (::OpenClipboard(NULL))
		{
			clipboard_ptr = AcquireClipboardData(CF_BITMAP);

			ClipboardToFileToClipboardOperation(clipboard_ptr, DataToFileFactory::createChosenFileSaveProduct(Choice_ImageToFile));

			::GlobalUnlock(GlobalHandle((HGLOBAL)clipboard_ptr));
			::CloseClipboard();
		}
	}

}


const void* ClipboardAPIHandler::AcquireClipboardData(const unsigned int& WindowsDefinedClipboardFormat)
{
	HGLOBAL cbuf;
	if (WindowsDefinedClipboardFormat == CF_BITMAP)
	{
		cbuf = GetClipboardData(CF_DIB);

		if (!cbuf)
		{
			cbuf = GetClipboardData(CF_DIBV5);
		}
	}
	else
	{
		cbuf = ::GetClipboardData(WindowsDefinedClipboardFormat);
	}
	
	void* ClipboardDataPtr = (void*)::GlobalLock(cbuf);

	return ClipboardDataPtr;
}


void ClipboardAPIHandler::ClipboardToFileToClipboardOperation(const void* clipboardData,const std::unique_ptr <DataToFileFactory>& SaveDataStrategy)
{
	if (clipboardData == NULL)return;

	std::string pathToTempFileOfClipboardData = SaveDataStrategy->SaveToFileFirst(clipboardData);

	if (pathToTempFileOfClipboardData == "ERROR") return; //silent error handling, but user will be confused as they aren't told why it doesnt work. May need to consider something else..

	PutFileLocationIntoClipboard(pathToTempFileOfClipboardData);
}



void ClipboardAPIHandler::PutFileLocationIntoClipboard(const std::string& sFilePath)
{
	//put filePath into a char buffer for legacy API compatibility
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

