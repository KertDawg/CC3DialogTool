//  https://rpgmaps.profantasy.com/developing-add-ons-for-cc3-part-1-getting-started/

#include "math.h"
#include "stdio.h"
#include <vector>
#include <string>
#include <tchar.h>
#include <windows.h>
#include <winuser.h>
#include <algorithm>
#include <iterator>

#include "Main.h"
#include "DialogManager.h"
#include "resource.h"


char CList[] = "DIALOGTOOL\0\0";
PCMDPROC PList[] = { About, SetupDialog };

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
	int DialogHandle = DefDlg("IDD_DLGOPTIONS", 0, 0, NULL, NULL, NULL);
	//EDCTL(DialogHandle, IDC_SELECT, 0, FT_UDec4, 6, &SelectedDialogIndex, NULL);
	EDCTL(DialogHandle, IDC_EDTSIZE, 0, FT_UDec4, 6, &SelectedSize, NULL);
	int DialogResult = XPDlog(DialogHandle, MyXP.ModHdl, 0);
	RelDlg(DialogHandle);

	if (DialogResult == IDOK)
	{
		LoopThroughDialogs();
		EndDialog();
	}

	CmdEnd();
}


void XPCALL EndDialog()
{
	FORMST(MyAPkt, "The dialog was reszed.",
		"Dialog Tool"
	)

	FormSt(&MyAPkt, RSC(FD_MsgBox));
	CmdEnd();
}


