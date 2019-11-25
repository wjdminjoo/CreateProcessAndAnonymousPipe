#include <stdio.h>
#include <tchar.h>
#include <windows.h>


#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR * argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	si.lpTitle = (LPTSTR)_T("child");

	HANDLE hReadPipe, hWritePipe; //pipe handle

	TCHAR sendString[] = _T("anonymous pipe");
	TCHAR recvString[100];

	DWORD bytesWritten;
	DWORD bytesRead;

	TCHAR command[] = _T("ChildProcess.exe 10 20");
	TCHAR cDir[DIR_LEN];
	BOOL state;

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(si);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	GetCurrentDirectory(DIR_LEN, cDir);	//현재 디렉토리 확인.
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	SetCurrentDirectory(_T("C:\\WinSystem"));

	GetCurrentDirectory(DIR_LEN, cDir);	//현재 디렉토리 확인.
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);


	state = CreateProcess(NULL,     // 프로세스 생성.
		command,
		NULL,
		NULL,
		TRUE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi
	);  //CreateProcess

	CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);
	WriteFile(hWritePipe, sendString, lstrlen(sendString) * sizeof(TCHAR), &bytesWritten, NULL);
	_tprintf(_T("string send: %s \n"), sendString);


	/* pipe의 다른 한쪽 끝을 이용한 데이터 수신 */
	//ReadFile(hReadPipe, recvString, bytesWritten, &bytesRead, NULL);
	//recvString[bytesRead / sizeof(TCHAR)] = 0;
	//_tprintf(_T("string recv: %s \n"), recvString);
	if (state != 0)
		_fputts(_T("Create OK! \n"), stdout);
	else
		_fputts(_T("Create Error! \n"), stdout);
	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	return 0;
}


