#include<windows.h>
#include<iostream>
#include<string.h>
#include<string>
#include<queue>
#include<stdio.h>
using namespace std;


HWND gameh;
RECT r1;
POINT p;
DWORD byread;
DWORD processid = 0;
HANDLE processh = 0;
int t = 100;
byte chessdata[11][19];		//���ݱ��滺����,��������Ϊ11*19
const char *gamename = "������";

struct point {
	int x, y, direct;	//�����"������BFS�㷨"
	int step, hp;
};

void readchess() {	//������
	gameh = ::FindWindow(NULL, gamename);
	::GetWindowThreadProcessId(gameh, &processid);
	processh = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	LPCVOID pbase = (LPCVOID)���̻�ַ;
	LPVOID  nbuffer = (LPVOID)&chessdata;
	::ReadProcessMemory(processh, pbase, nbuffer, 11*19, &byread);
}

void click2p(POINT p1, POINT p2) {	//���������Ĳ�������
	HWND hwnd=FindWindow(NULL, gamename);
	int lparam;
	lparam=((p1.y*35+192)<<16)+(p1.x*31+21);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);
	lparam=((p2.y*35+192)<<16)+(p2.x*31+21);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);
}


void clearapair() {	//�ҵ�����ȥ�������㲢���
	 POINT p1, p2;
	 int x1, y1, x2, y2;
	  for (y1=0; y1<11; y1++)
		  for (x1=0; x1<19; x1++) {
		  	 if (!chessdata[y1][x1])
		 	  	continue;
			  for (y2=0; y2<11; y2++)
				for (x2=0; x2<19; x2++)
				  if (chessdata[y2][x2] && (chessdata[y1][x1]==chessdata[y2][x2]) && (x1!=x2 || y1!=y2) )  {  
					  p1.x=x1; p1.y=y1;
					  p2.x=x2; p2.y=y2;
					  readchess();
					  if (llk_bfs(y1, x1, y2, x2) != -1) {
					  	click2p(p1, p2);
					  	return;	
					  }
				  }
		  }

}

