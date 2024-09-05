#pragma once
#include <windows.h>
#include <XT_Entities.h>
#include "XP.H"
#include "DialogManager.h"

#define XPID 0x2457

extern char CList[];
extern PCMDPROC PList[];
extern XP MyXP;

void XPCALL About(void);
void XPCALL SetupDialog();
void XPCALL EndDialog();
