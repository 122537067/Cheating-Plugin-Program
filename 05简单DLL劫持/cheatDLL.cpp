//
//  05��DLL�ٳ�(����ģ��DLL����)
//  C/C++
//
//  Created by luguanxing.
//  Copyright @2016 LGX. All rights reserved.
//
#include <windows.h>
#define Dllfunciton extern "C" __declspec(dllexport)    //��C��ʽ����

Dllfunciton void lockdata();
Dllfunciton DWORD WINAPI inject(LPVOID);

void lockdata() {
    while (true) {
        DWORD hp = 10;
        DWORD heart = 99;
        DWORD life = 99;

        DWORD addr = 0x00428282;
        DWORD addr2 = 0x00428292;
        DWORD addr3 = 0x004282a2;

        DWORD res = WriteProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)addr, &hp, 4, 0);  //д�������޸���Ϸ����
        DWORD res2 = WriteProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)addr2, &heart, 4, 0);
        DWORD res3 = WriteProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)addr3, &life, 4, 0);

        Sleep(1000);
    }
}

DWORD WINAPI inject(LPVOID) {
    lockdata();
    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,  DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch(ul_reason_for_call) {
        case DLL_PROCESS_ATTACH: {
            ::DisableThreadLibraryCalls(hModule);   //�����̰߳�����ѭ����Ϊ��������������
            CreateThread(NULL, 0, inject, NULL, 0, NULL);
        }
        break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
        default:;
    }
    return true;
}