#include "stdafx.h"
#include "DataToFile.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <locale>
#include <fcntl.h>
#include <io.h>


//Purpose of sGenerateFileNameBasedOnTime
//Generate file name easily. Use a FileNameStrategy implementation based on available examples to get a prefix name and extension name of your file type. Function is available for all DataToFileFactory implementations if you want generated name that says "text_YYYY_MM_DD_HH_MM_SS.txt"
const std::string DataToFileFactory::sGenerateFileNameBasedOnTime(const DataToFileFactory::FileNameStrategy& kFiletypeDetails) const
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	std::string filenameToFormat = kFiletypeDetails.ksFileType() + "_%Y-%m-%d_%H-%M-%S" + kFiletypeDetails.ksFileExtension();

	ss << std::put_time(std::localtime(&in_time_t), filenameToFormat.c_str());//filename: text_YYYY-MM-DD-HH-MM-SS.txt

	return ss.str();
}




const std::string TextDataToFile::SaveData(void const * const kvData) const
{
	std::wstring sClipboardText = (const wchar_t*)kvData;

	std::string sWindowsTempFolderPath = std::filesystem::temp_directory_path().string();

	

	TextFileName describeFileAsText;

	std::string sTempFileNameWithTempFolder = sWindowsTempFolderPath + sGenerateFileNameBasedOnTime(describeFileAsText);

	_setmode(_fileno(stdout), _O_U8TEXT);//wcout instead of cout
	std::locale loc_utf8(std::locale(), new std::codecvt_utf8<wchar_t>);
	std::wofstream fout(sTempFileNameWithTempFolder, std::ios::binary);

	try
	{
		if (fout)
		{
			fout.imbue(loc_utf8);
			fout << sClipboardText;
			fout.close();
		}
	}
	catch (std::exception const & ex)
	{
		std::cerr << ex.what() << std::endl;
	}


	return sTempFileNameWithTempFolder;

}


const std::string BitmapIMGDataToFile::SaveData(void const * const kvData) const
{
	std::string sWindowsTempFolderPath = std::filesystem::temp_directory_path().string();
	ImgFileName describeFileAsImg;
	std::string sTempFileNameWithTempFolder = sWindowsTempFolderPath + sGenerateFileNameBasedOnTime(describeFileAsImg);

	std::ofstream fout(sTempFileNameWithTempFolder, std::ios::binary);

	if (fout)
	{
		fout << (char*)kvData;
		fout.close();
	}

	return sTempFileNameWithTempFolder;
}

std::unique_ptr <DataToFileFactory> DataToFileFactory::createChosenFileSaveProduct(const DataToFileFactoryChoice& choice)
{
	switch (choice)
	{
	case Choice_TextToFile:
		return std::make_unique <TextDataToFile>();
	case Choice_ImageToFile:
		return std::make_unique <BitmapIMGDataToFile>();
	}

}