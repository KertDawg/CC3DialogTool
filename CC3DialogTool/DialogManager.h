#pragma once
#include <windows.h>
#include <string>
#include <XT_Entities.h>
#include "XP.H"

#define NUMBEROFDIALOGS 1

struct DialogDetail
{
    std::string Name;
    std::string ResourceID;
    unsigned int SizeOffset;
};

extern DialogDetail DialogList[];
extern int SelectedDialogIndex;
extern unsigned int SelectedSize;


void LoopThroughDialogs();
BOOL ProcessOneDialog(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG lParam);

