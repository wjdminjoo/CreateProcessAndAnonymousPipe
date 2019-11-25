#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 512

int _tmain(int argc, TCHAR * argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	TCHAR command[] = _T("child.exe");

	HANDLE hReadPipe, hWritePipe;
	HANDLE hReadPipe2, hWritePipe2;

	TCHAR sendStr[BUF_SIZE];
	TCHAR recvStr[BUF_SIZE + 1];

	DWORD bytes;

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0);

	FILE* file = _tfopen(_T("HandleTable.txt"), _T("w"));
	_ftprintf(file, _T("%p %p"), hWritePipe, hReadPipe2);
	fclose(file);
	

	si.cb = sizeof(si);

	CreateProcess(NULL, command, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	CloseHandle(pi.hThread);

	while (1)
	{
		_tprintf(_T("Read: "));
		ReadFile(hReadPipe, recvStr, BUF_SIZE, &bytes, NULL);
		recvStr[bytes / sizeof(TCHAR)] = 0;
		_tprintf(_T("%s\n"), recvStr);

		if (_tcscmp(recvStr, _T("exit")) == 0)
			break;

		_tprintf(_T("Send: "));
		_fgetts(sendStr, sizeof(sendStr) / sizeof(TCHAR), stdin);
		if (lstrlen(sendStr) > 0)
			sendStr[lstrlen(sendStr) / sizeof(TCHAR) - 1] = 0;

		WriteFile(hWritePipe2, sendStr, lstrlen(sendStr) * sizeof(TCHAR), &bytes, NULL);

		if (_tcscmp(sendStr, _T("exit")) == 0)
			break;
	}

	CloseHandle(hReadPipe);
	CloseHandle(hReadPipe2);
	CloseHandle(hWritePipe);
	CloseHandle(hWritePipe2);
	CloseHandle(pi.hProcess);
	return 0;
}