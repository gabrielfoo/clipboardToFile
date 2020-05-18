#include "stdafx.h"
#include "MyForm.h"
#include "ThreadWrapperCPPCLI.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;


[STAThreadAttribute]
int main(array <String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ClipboardToText::MyForm form;
	ThreadWrapper::threadClipboardtoFile = gcnew Thread(gcnew ThreadStart(&ThreadWrapper::BeginClipBoardFunction));
	ThreadWrapper::threadClipboardtoFile->Start();

	Application::Run(%form);
	atomicboolKeepThreadAlive = false;
	ThreadWrapper::threadClipboardtoFile->Join();
	return 0;
}

