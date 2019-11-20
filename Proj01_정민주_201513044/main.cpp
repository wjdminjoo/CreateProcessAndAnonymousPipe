/*
1. �θ� process���� �б��, ����� anonymous pipe�� ���� �����Ѵ�.
	(�̶� �����Ǵ� handle�� ��� �����ϵ��� �����Ǿ�� �Ѵ�.)
2. �ڽ� process�� �����ϰ�, �б�� ����� pipe �ڵ��� �ڽ� ���μ����� ���� �����Ѵ�.
3. ������ �ڽ� ���μ����� �θ� ���μ����� Ű���� �Է��� �ΰ��� pipe�� ���� �ְ� �޾� ȭ�鿡 ǥ���ϵ��� �Ѵ�.
4. �Էµ� ���ڰ� exit �϶� �� ���μ����� ���� �Ѵ�.
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