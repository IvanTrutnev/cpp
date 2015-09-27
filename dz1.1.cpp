#include<windows.h>
#include<tchar.h>
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	TCHAR szTitleFirst[] = TEXT("Резюме");
	TCHAR szName[] = TEXT("Меня зовут Трутнев Иван");
	TCHAR szSurname[] = TEXT("Учусь в БГире");
	TCHAR szEndName[] = TEXT("Учусь плохо:D");
	MessageBox(NULL, szName, szTitleFirst, MB_OK);
	MessageBox(NULL, szSurname, szTitleFirst, MB_OK);
	TCHAR szTitleEnd[100];
	INT count = ((strlen("Меня зовут Трутнев Иван ") + strlen("Учусь в БГире") + strlen("Учусь плохо:D")) / 3);
	;
	wsprintf(szTitleEnd, LPCWSTR( "Ср числ сим:%i"), count);
	MessageBox(NULL, szEndName, szTitleEnd, MB_OK);
	return 0;
}