#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 512

int _tmain(int argc, TCHAR * argv[])
{
	HANDLE hWritePipe;
	HANDLE hReadPipe;

	TCHAR sendStr[BUF_SIZE];
	TCHAR recvStr[BUF_SIZE + 1];
	DWORD bytes;

	FILE* file = _tfopen(_T("HandleTable.txt"), _T("r"));
	_ftscanf(file, _T("%p %p"), &hWritePipe, &hReadPipe);
	fclose(file);


	while (1)
	{
		_tprintf(_T("Send: "));
		_fgetts(sendStr, sizeof(sendStr) / sizeof(TCHAR), stdin);
		if (lstrlen(sendStr) > 0)
			sendStr[lstrlen(sendStr) / sizeof(TCHAR) - 1] = 0;

		WriteFile(hWritePipe, sendStr, lstrlen(sendStr) * sizeof(TCHAR), &bytes, NULL);

		if (_tcscmp(sendStr, _T("exit")) == 0)
			break;

		_tprintf(_T("Read: "));
		ReadFile(hReadPipe, recvStr, BUF_SIZE, &bytes, NULL);
		recvStr[bytes / sizeof(TCHAR)] = 0;
		_tprintf(_T("%s\n"), recvStr);

		if (_tcscmp(recvStr, _T("exit")) == 0)
			break;
	}

	CloseHandle(hWritePipe);
	return 0;
}