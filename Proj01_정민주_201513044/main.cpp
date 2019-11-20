/*
1. 부모 process에서 읽기용, 쓰기용 anonymous pipe를 각각 생성한다.
	(이때 생성되는 handle은 상속 가능하도록 생성되어야 한다.)
2. 자식 process를 생성하고, 읽기용 쓰기용 pipe 핸들을 자식 프로세스에 각각 전달한다.
3. 생성된 자식 프로세스와 부모 프로세스간 키보드 입력을 두개의 pipe를 통해 주고 받아 화면에 표시하도록 한다.
4. 입력된 글자가 exit 일때 두 프로세스를 종료 한다.
*/

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

void _tmain(int argc, TCHAR* argv[]) {

	STARTUPINFO startInfo = { 0, };
	PROCESS_INFORMATION processInfo;

	startInfo.cb = sizeof(startInfo);
	startInfo.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	startInfo.dwX = 100;
	startInfo.dwY = 200;
	startInfo.dwXSize = 500;
	startInfo.dwYSize = 600;
	startInfo.lpTitle = (LPWSTR)_T("Process Child");
}