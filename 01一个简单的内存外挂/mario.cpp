//
//  01һ���򵥵��ڴ����.cpp
//  C/C++
//
//  Created by luguanxing.
//  Copyright @2016 LGX. All rights reserved.
//

#include <windows.h>
#include <stdio.h>

int main() {
	HWND h = ::FindWindow(NULL, "Super Mario XP");	//	Ѱ�Ҳ��򿪽���
	DWORD processid;
	GetWindowThreadProcessId(h, &processid);
	HANDLE hprocess = 0;
	hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);

	if (hprocess == 0) {	//	��Ӧ����
		printf("�򿪽���ʧ��!\n");
		return 1;
	} else {
		printf("�򿪽��̳ɹ�!\n");

		DWORD hp = 10;	//	Ҫ�޸ĵ���Ϸ�������ֵ	
		DWORD heart = 99;
		DWORD life = 99;

		DWORD addr = 0x00428282;	//	ͨ��CE�ҵ�����Ϸ���ݵ�ַ
		DWORD addr2 = 0x00428292;
		DWORD addr3 = 0x004282a2;
  
		DWORD res = WriteProcessMemory(hprocess, (LPVOID)addr, &hp, 4, 0);	//	д���ڴ��޸���Ϸ����
		DWORD res2 = WriteProcessMemory(hprocess, (LPVOID)addr2, &heart, 4, 0);
		DWORD res3 = WriteProcessMemory(hprocess, (LPVOID)addr3, &life, 4, 0);
	
		return 0;
	}
}