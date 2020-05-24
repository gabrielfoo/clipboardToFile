#pragma once
#ifndef _CLIPBOARD_RETRIEVE_H
#define _CLIPBOARD_RETRIEVE_H
#include "stdafx.h"

class ClipboardRetrieveFactory
{
public:
	virtual ~ClipboardRetrieveFactory() {};
	virtual const int kiClipboardFormat() const = 0;
	
};


class ClipboardGetUnicodeTextProduct : public ClipboardRetrieveFactory
{
public:
	const int kiClipboardFormat() const override {
		return CF_UNICODETEXT;
	}
};

class ClipboardGetBitmapProduct : public ClipboardRetrieveFactory
{
public:
	const int kiClipboardFormat() const override {
		return CF_BITMAP;
	}
};

#endif