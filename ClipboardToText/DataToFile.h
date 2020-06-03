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

private:
	//credits to https://engineering.purdue.edu/ece264/16au/hw/HW13#:~:text=The%20structure%20of%20the%20BMP,red%2C%20green%2C%20and%20blue.
	//also https://stackoverflow.com/questions/30552255/how-to-read-a-bitmap-from-the-windows-clipboard
	typedef struct {             // Total: 54 bytes
		uint16_t  type;             // Magic identifier: 0x4d42
		uint32_t  size;             // File size in bytes
		uint16_t  reserved1;        // Not used
		uint16_t  reserved2;        // Not used
		uint32_t  offset;  // Offset to image data in bytes from beginning of file (54 bytes)
	}FirstPartOfHeader;

	typedef struct{
		uint32_t  dib_header_size;  // DIB Header size in bytes (40 bytes)
		int32_t   width_px;         // Width of the image
		int32_t   height_px;        // Height of image
		uint16_t  num_planes;       // Number of color planes
		uint16_t  bits_per_pixel;   // Bits per pixel
		uint32_t  compression;      // Compression type
		uint32_t  image_size_bytes; // Image size in bytes
		int32_t   x_resolution_ppm; // Pixels per meter
		int32_t   y_resolution_ppm; // Pixels per meter
		uint32_t  num_colors;       // Number of colors  
		uint32_t  important_colors; // Important colors 
	} DIBPartOfHeader;

	typedef struct {
		FirstPartOfHeader header;
		DIBPartOfHeader dib_header;
		unsigned char* data;
	}BMP;
};



#endif
