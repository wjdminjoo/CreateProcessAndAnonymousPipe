#include <stdio.h>
#include <tchar.h>
#include <windows.h>


int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hReadPipe, hWritePipe;
	DWORD val1, val2;
	val1 = _ttoi(argv[1]);
	val2 = _ttoi(argv[2]);
	TCHAR sendString[] = _T("anonymous pipe");
	TCHAR recvString[100];
	DWORD bytesWritten;
	DWORD bytesRead;

	_tprintf(_T("%d + %d = %d \n"), val1, val2, val1 + val2);
	CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);
	WriteFile(hWritePipe, sendString, lstrlen(sendString) * sizeof(TCHAR), &bytesWritten, NULL);
	_tprintf(_T("string send: %s \n"), sendString);


	/* pipe�� �ٸ� ���� ���� �̿��� ������ ���� */
	ReadFile(hReadPipe, recvString, bytesWritten, &bytesRead, NULL);
	recvString[bytesRead / sizeof(TCHAR)] = 0;
	_tprintf(_T("string recv: %s \n"), recvString);
	_gettchar(); //���α׷��� ������ ��� ���߱� ����. 
	return 0;
}

