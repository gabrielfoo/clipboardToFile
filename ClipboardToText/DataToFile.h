#pragma once
#ifndef _CLIPBOARD_DATA_TO_FILE_H 
#define _CLIPBOARD_DATA_TO_FILE_H

#include "stdafx.h"

class DataToFileFactory
{
public:
	virtual ~DataToFileFactory() {};
protected:
	class FileNameStrategy
	{
	public:
		virtual ~FileNameStrategy() {};

		virtual const std::string ksFileType() const = 0;
		virtual const std::string ksFileExtension() const = 0;
	};
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
