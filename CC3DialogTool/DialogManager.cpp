#include "DialogManager.h"


DialogDetail DialogList[1] = {
	{
		"Custom Drawing Tools",
		"IDD_DLGDRAWTOOLBASICSAMPLE",
		62
	} 
};

int SelectedDialogIndex = 0;


void LoopThroughDialogs()
{
	DWORD ErrorCode;

	HMODULE hExe = LoadLibrary(TEXT("XPCC2.dll"));
	EnumResourceNames(hExe, RT_DIALOG, (ENUMRESNAMEPROC)ProcessOneDialog, 0);
}

//  This gets called in a loop for each dialog resource.
BOOL ProcessOneDialog(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG lParam)
{
	//  Only act if this is the correct dialog resource.
	if (!DialogList[SelectedDialogIndex].ResourceID.compare(lpName))
	{
		HRSRC myResource = FindResource(hModule, lpName, lpType);
		HGLOBAL LoadedResource = LoadResource(hModule, myResource);
		LPVOID ResourceMemory = LockResource(LoadedResource);
		DWORD OldProtect = 0;
		unsigned char* FontSizePointer;

		VirtualProtect(ResourceMemory, 100, PAGE_READWRITE, &OldProtect);
		FontSizePointer = ((unsigned char*)ResourceMemory) + DialogList[SelectedDialogIndex].SizeOffset;
		*FontSizePointer = 16;
		FreeResource(LoadedResource);
	}

	return TRUE;
}
