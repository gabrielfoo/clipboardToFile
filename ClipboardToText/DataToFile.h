#pragma once
#ifndef _CLIPBOARD_DATA_TO_FILE_H 
#define _CLIPBOARD_DATA_TO_FILE_H

#include "stdafx.h"

enum DataToFileFactoryChoice
{
	Choice_TextToFile = 1,
	Choice_ImageToFile,
};

class DataToFileFactory
{
public:
	//static object factory function that returns a unique_ptr to object requested in parameters
	static std::unique_ptr <DataToFileFactory> createChosenFileSaveProduct(const DataToFileFactoryChoice& choice);
	virtual ~DataToFileFactory() {};


protected:
	class FileNameStrategy
	{
	public:
		virtual ~FileNameStrategy() {};

		virtual const std::string ksFileType() const = 0;
		virtual const std::string ksFileExtension() const = 0;
	};
//Purpose of sGenerateFileNameBasedOnTime
//Generate file name easily. Use a FileNameStrategy implementation based on available examples to get a prefix name and extension name of your file type. Function is available for all DataToFileFactory implementations if you want generated name that says "text_YYYY_MM_DD_HH_MM_SS.txt"
	const std::string sGenerateFileNameBasedOnTime(const FileNameStrategy& kFiletypeDetails) const;


public:
	virtual const std::string SaveData(void const * const kvData) const = 0;

};




class TextDataToFile : public DataToFileFactory
{
private:
	class TextFileName : public FileNameStrategy
	{
		const std::string ksFileType() const override {
			return "text";
		}
		const std::string ksFileExtension() const override {
			return ".txt";
		}
	};
public:
	const std::string SaveData(void const * const kvData) const override;
};





class BitmapIMGDataToFile : public DataToFileFactory
{
private:
	class ImgFileName : public FileNameStrategy
	{
		const std::string ksFileType() const override {
			return "image";
		}
		const std::string ksFileExtension() const override {
			return ".bmp";
		}
	};
public:
	const std::string SaveData(void const * const kvData) const override;
};



#endif
