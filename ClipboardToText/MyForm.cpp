#include "stdafx.h"
#include "MyForm.h"
#include "ThreadWrapperCPPCLI.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;
using namespace System::Diagnostics;
void EnsureOnlyOneProgramRunning();

[STAThreadAttribute]
int main(array <String^>^ args) {
	EnsureOnlyOneProgramRunning();
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

void EnsureOnlyOneProgramRunning()
{
	String^ sThisProgramProcessName = Process::GetCurrentProcess()->ProcessName;

	array<Process^>^ arrListOfProcess =  Process::GetProcessesByName(sThisProgramProcessName);

	if (arrListOfProcess->Length > 1)
	{
		System::Windows::Forms::MessageBox::Show("Application has already started. Check the system tray.", String::Concat(sThisProgramProcessName, " is already Running!"), MessageBoxButtons::OK, MessageBoxIcon::Error);
		exit(1);
		
	}
	
}

