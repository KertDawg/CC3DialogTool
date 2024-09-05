#pragma once
#include <windows.h>
#include <string>
#include <XT_Entities.h>
#include "XP.H"


struct DialogDetail
{
    std::string Name;
    std::string ResourceID;
    unsigned int SizeOffset;
};

extern DialogDetail DialogList[];
extern int SelectedDialogIndex;


void LoopThroughDialogs();
BOOL ProcessOneDialog(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG lParam);

