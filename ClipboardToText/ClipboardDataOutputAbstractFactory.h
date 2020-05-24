#pragma once
#ifndef _CLIPBOARD_ABSTRACT_FACTORY_H
#define _CLIPBOARD_ABSTRACT_FACTORY_H
#include "DataToFile.h"
#include "ClipboardReaderFactory.h"


class ClipboardToFileAbstractFactory {
public:
	virtual ~ClipboardToFileAbstractFactory() {}
	virtual ClipboardRetrieveFactory& GetClipboardDataProduct() const = 0;
	virtual DataToFileFactory& ConvertDataToFileProduct() const = 0;
	
};




#endif