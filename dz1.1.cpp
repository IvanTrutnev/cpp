#include<windows.h>
#include<tchar.h>
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	TCHAR szTitleFirst[] = TEXT("������");
	TCHAR szName[] = TEXT("���� ����� ������� ����");
	TCHAR szSurname[] = TEXT("����� � �����");
	TCHAR szEndName[] = TEXT("����� �����:D");
	MessageBox(NULL, szName, szTitleFirst, MB_OK);
	MessageBox(NULL, szSurname, szTitleFirst, MB_OK);
	TCHAR szTitleEnd[100];
	INT count = ((strlen("���� ����� ������� ���� ") + strlen("����� � �����") + strlen("����� �����:D")) / 3);
	;
	wsprintf(szTitleEnd, LPCWSTR( "�� ���� ���:%i"), count);
	MessageBox(NULL, szEndName, szTitleEnd, MB_OK);
	return 0;
}