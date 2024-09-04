//  https://rpgmaps.profantasy.com/developing-add-ons-for-cc3-part-1-getting-started/

#include "math.h"
#include "stdio.h"
#include <vector>
#include <string>
#include <windows.h>
#include <winuser.h>
#include <algorithm>
#include <iterator>

#include "Main.h"


char CList[] = "DIALOGTOOL\0\0";
PCMDPROC PList[] = { About, SetupDialog };
HANDLE m_CurrentProcess;
HANDLE m_CurrentThread;

XP MyXP = { 0, CList, PList, 0, 0, 0, XPID, 0, 620, 0, 0, 620 };


/////////////  DllMain - XP initialization & Unload code //////////////
BOOL WINAPI DllMain(const HINSTANCE hDLL, const DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		MyXP.ModHdl = hDLL;
		_XPRegCmd(&MyXP);
		break;
	case DLL_PROCESS_DETACH:
		_XPUnregCmd(&MyXP);
		break;
	default:
		break;
	}
	return TRUE;
}


void XPCALL About()
{
	FORMST(MyAPkt, "CC3+ Dialog Tool\nv0.0.1\n\n"
		"This edits the dialog sizes."
	)

	FormSt(&MyAPkt, RSC(FD_MsgBox));
	CmdEnd();
}

void XPCALL SetupDialog()
{
	GetHandle();
	SearchMemory();
	PatchMemory();
	EndDialog();

	CmdEnd();
}

void XPCALL GetHandle()
{
	//  Get a handle to the CC3 process.
	DWORD ProcessID;

	//CurrentProcess = GetCurrentProcess();
	//CurrentThread = GetCurrentThread();

	ProcessID = GetCurrentProcessId();

	//DuplicateHandle(CurrentProcess, CurrentThread, &m_CurrentProcess, &m_CurrentThread, 0, FALSE, DUPLICATE_SAME_ACCESS);
	m_CurrentProcess = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessID);
}

void XPCALL PatchMemory()
{
	CmdEnd();
}

BOOL EnumNamesFunc(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG lParam)
{
	TCHAR szBuffer[80];  // print buffer for info file
	DWORD cbWritten;     // number of bytes written to resource info file
	size_t cbString;
	HRESULT hResult;

	if (!strcmp(lpName, "IDD_DLGDRAWTOOLBASICSAMPLE"))
	{
		HRSRC myResource = FindResource(hModule, lpName, lpType);
		HGLOBAL LoadedResource = LoadResource(hModule, myResource);
		LPVOID ResourceMemory = LockResource(LoadedResource);
		DWORD OldProtect = 0;

		bool r = VirtualProtect(ResourceMemory, 100, PAGE_READWRITE, &OldProtect);


		char c;
		int k;

		for (int i = 0; i < 100; i += 2)
		{
			unsigned char* pointer;
			
			pointer = ((unsigned char*)ResourceMemory) + i;
			c = *pointer;
			k = c;

			pointer = ((unsigned char*)ResourceMemory) + i + 1;
			c = *pointer;
			k += (int)c << 8;


			if (k == 8)
			{
				int j = 0;
				pointer = ((unsigned char*)ResourceMemory) + i;
				*pointer = 16;
			}
		}

		FreeResource(LoadedResource);
		int i = 0;
	}

	return TRUE;
}

void XPCALL SearchMemory()
{
	DWORD ErrorCode;

	HMODULE hExe = LoadLibrary(TEXT("XPCC2.dll"));
	ErrorCode = GetLastError();

	EnumResourceNames(hExe, RT_DIALOG, (ENUMRESNAMEPROC)EnumNamesFunc, 0);

	ErrorCode = GetLastError();
	int i = 0;
}

void SearchMemory1()
{
	std::vector<char> Buffer;
	unsigned char* StartPosition = 0;
	DWORD BytesRead;
	MEMORY_BASIC_INFORMATION MemoryInfo;
	DWORD ErrorCode;

	for (StartPosition = NULL;
		VirtualQueryEx(m_CurrentProcess, StartPosition, &MemoryInfo, sizeof(MemoryInfo)) == sizeof(MemoryInfo);
		StartPosition += MemoryInfo.RegionSize)
	{
		if (MemoryInfo.State == MEM_COMMIT &&
			(MemoryInfo.Type == MEM_MAPPED || MemoryInfo.Type == MEM_PRIVATE))
		{
			Buffer.resize(MemoryInfo.RegionSize);
			ReadProcessMemory(m_CurrentProcess, StartPosition, &Buffer[0], MemoryInfo.RegionSize, &BytesRead);
			Buffer.resize(BytesRead);
			ErrorCode = GetLastError();

			//  Look for C0 00 C8 80 in this test.
			unsigned int DLGIDIndex;

			if (FindWord(Buffer, 3772900067, &DLGIDIndex))
			{
				//  We found the dialog ID;
				int i = 0;
			}

			if (FindWord(Buffer, 0xC000C880, &DLGIDIndex))
			{
				//  We found the dialog ID;
				int i = 0;
			}

			if (FindWord(Buffer, 0x80C800C0, &DLGIDIndex))
			{
				//  We found the dialog ID;
				int i = 0;
			}
		}
	}
}

bool XPCALL IsBufferAllZeroes(std::vector<char> Buffer)
{
	int Position;

	for (Position = 0; Position < Buffer.size(); Position++)
	{
		if (Buffer[Position] != 0)
		{
			return false;
		}
	}

	return true;
}

bool XPCALL FindWord(std::vector<char> Haystack, unsigned int Needle, unsigned int *DLGIDIndex)
{
	unsigned int Position;
	unsigned int CurrentWord;

	for (Position = 0; Position < Haystack.size(); Position += 4)
	{
		CurrentWord = ((unsigned char)&Haystack[Position] << 24) + ((unsigned char)&Haystack[Position + 1] << 16) + ((unsigned char)&Haystack[Position + 2] << 8) + (unsigned char)&Haystack[Position + 3];

		if (CurrentWord == Needle)
		{
			*DLGIDIndex = Position;
			return true;
		}
	}

	return false;
}

void XPCALL EndDialog()
{
	FORMST(MyAPkt, "The dialog was reszed.",
		"Dialog Tool"
	)

	FormSt(&MyAPkt, RSC(FD_MsgBox));
	CmdEnd();
}


