//
//  04��DLLע����Ϸ(ע����EXE����)
//  C/C++
//
//  Created by luguanxing.
//  Copyright @2016 LGX. All rights reserved.
//
#include <windows.h>
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

HWND hwnd = NULL;
DWORD processid = NULL;
HANDLE hprocess = NULL;
PVOID procdlladdr = NULL;

char dllname[25] = "cheatDLL";
char loadfunc[25] = "LoadLibraryA";
FARPROC loadfuncaddr = NULL;
HANDLE hfile;

void getwindow() {
    hwnd = ::FindWindow(NULL, "Super Mario XP");
	if (hwnd == NULL)
		MessageBox(NULL, "�Ҳ�����Ϸ", "����",  MB_OK);
    GetWindowThreadProcessId(hwnd, &processid);
    hprocess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,processid);
	if (hprocess == NULL)
		MessageBox(NULL, "����Ϸʧ��", "����", MB_OK);
}


void inject() {
	int size = strlen(dllname)+5;
	procdlladdr = ::VirtualAllocEx(hprocess, NULL, size, MEM_COMMIT, PAGE_READWRITE);	//��Ŀ������ռ䣬�õ��¿ռ��ַ
	if (procdlladdr == NULL)
		MessageBox(NULL, "����ռ�ʧ��", "����", MB_OK);
	DWORD writenum;
	::WriteProcessMemory(hprocess, procdlladdr, dllname, size, &writenum);	//���¿ռ�д��Ҫע���DLL����
	loadfuncaddr = ::GetProcAddress(::GetModuleHandle("kernel32.dll"), loadfunc);	//���LoadLibraryA�ĵ�ַ,���κν��̿ռ䶼һ��
	HANDLE hthread = ::CreateRemoteThread(hprocess, NULL, 0, (LPTHREAD_START_ROUTINE)loadfuncaddr, (LPVOID)procdlladdr, 0, NULL);
	//�½��߳�ִ��LoadLibrary����������Ŀ������¿ռ�д���DLL����,ע�����������64λ���޷��ɹ�
	::WaitForSingleObject(hthread, INFINITE); 
	::CloseHandle(hthread);
	::CloseHandle(hprocess);
}

int main() {
	getwindow();
	inject();
	return 0;
}