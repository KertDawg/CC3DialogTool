#pragma once
#include <windows.h>
#include <XT_Entities.h>
#include "XP.H"

#define XPID 0x2457

void XPCALL About(void);

extern char CList[];
extern PCMDPROC PList[];
extern XP MyXP;
void XPCALL SetupDialog();
void XPCALL GetHandle();
void XPCALL SearchMemory();
bool XPCALL IsBufferAllZeroes(std::vector<char> Buffer);
bool XPCALL FindWord(std::vector<char> Haystack, unsigned int Needle, unsigned int *DLGIDIndex);
void XPCALL PatchMemory();
void XPCALL EndDialog();
