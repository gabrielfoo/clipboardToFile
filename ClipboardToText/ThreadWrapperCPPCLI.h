#pragma once
#include "ClipboardToTextmain.h"

using namespace System;
using namespace System::Threading;

public ref class ThreadWrapper
{
public:
	static Thread^ threadClipboardtoFile = nullptr;
public:
	static void BeginClipBoardFunction()
	{
		real_main();
	}
};