#include "stdafx.h"
//#include "ClipboardReader.h"
//
//
//#using <system.dll>
//#using <system.Drawing.dll>
//#using <system.windows.forms.dll>
//
//
//using namespace System::Windows::Forms;
//using namespace System;
//using namespace System::IO;
//
//
//void ClipboardMan::RetrieveClipboardText()
//{
//	IDataObject^ data = Clipboard::GetDataObject();
//
//	if (data)
//	{
//		//if (data->GetDataPresent(DataFormats::FileDrop))
//		//{
//		//	Collections::Specialized::StringCollection^ a = Clipboard::GetFileDropList();
//		//	for each (String^ elem in a)
//		//	{
//		//		Console::WriteLine(elem);
//		//	}
//		//	//Console::WriteLine(text);
//		//}
//		if (data->GetDataPresent(DataFormats::Text))
//		{
//			String^ text = static_cast<String^>
//				(data->GetData(DataFormats::Text));
//
//			TurnClipboardTextToFile(text);
//		}
//		else
//			Console::WriteLine("Nontext data is in the Clipboard.");
//	}
//	else
//	{
//		Console::WriteLine("No data was found in the Clipboard.");
//	}
//}
//
//void ClipboardMan::TurnClipboardTextToFile(String^ text)
//{
//
//	String^ sTempPath = Path::GetTempPath();
//	String^ sFilePath = sTempPath + "lol.txt";
//
//	StreamWriter^ sw = gcnew StreamWriter(sFilePath);
//	sw->WriteLine(text);
//	sw->Close();
//
//
//	Collections::Specialized::StringCollection^ a = gcnew Collections::Specialized::StringCollection;
//	array<String^>^myArr = { "C:\\Users\\tanwq\\source\\repos\\ClipboardToText\\ClipboardToText\\lol.txt" }; //{ sFilePath };
//	a->AddRange(myArr);
//
//
//	Clipboard::SetFileDropList(a);
//
//}
//
//void ClipboardMan::Clear()
//{
//	Clipboard::Clear();
//}