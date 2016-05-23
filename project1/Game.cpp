#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); 
BOOL CALLBACK SubDlgProc1(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam);

BOOL CALLBACK SubDlgProc2(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam);

BOOL CALLBACK SubDlgProc3(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam);

void Draw_Mode(HDC hdc);
void Score_Save(HWND hDlg);
void Success_Call_Dialog(HWND hDlg, int id, LPCWSTR sscore);
void find_willy(HWND hDlg,int id);
void dont_find_willy(HWND hDlg);
void Draw_Circle_or_not(HDC hdc,int x,int y);
void Draw_Hart_or_Devil(HDC hdc);
void Draw_GameOver_or_Clear(HWND hDlg, HDC hdc,HBITMAP MyBitmap,HDC MemDC); 

HINSTANCE g_hInst;
HWND hWndMain, hDlgMain;
HWND startBtn, quitBtn, easyBtn, normalBtn, hardBtn;
LPWSTR lpszClass=L"Game";

int level = 0;
int chance = 3;
int find = 0;
int time = 30;
int score = 100;


int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		100,100,800,650,NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	hWndMain=hWnd;

	HACCEL hAccel;
	hAccel = LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR1));

	while (GetMessage(&Message,NULL,0,0)) {
		if(!TranslateAccelerator(hWnd,hAccel,&Message)){
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc, MemDC;
	HBITMAP MyBitmap, OldBitmap;
	BITMAP bit;
	
	switch (iMessage) {
	case WM_CREATE:
		 hWndMain=hWnd;
		 MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
				
		 startBtn = CreateWindow(L"button",L"Play",WS_CHILD | WS_VISIBLE 
			| BS_PUSHBUTTON,550,480,200,30,hWnd,(HMENU)101,g_hInst,NULL);

		 quitBtn = CreateWindow(L"button",L"Quit", WS_CHILD | WS_VISIBLE 
			 | BS_PUSHBUTTON,550,520,200,30,hWnd,(HMENU)102, g_hInst, NULL);

		 easyBtn = CreateWindow(L"button",L"Easy",WS_CHILD | WS_VISIBLE 
			| BS_PUSHBUTTON,550,440,200,30,hWnd,(HMENU)103,g_hInst,NULL);

		 normalBtn = CreateWindow(L"button",L"Normal",WS_CHILD | WS_VISIBLE 
			| BS_PUSHBUTTON,550,480,200,30,hWnd,(HMENU)104,g_hInst,NULL);

		 hardBtn = CreateWindow(L"button",L"Difficult",WS_CHILD | WS_VISIBLE 
			| BS_PUSHBUTTON,550,520,200,30,hWnd,(HMENU)105,g_hInst,NULL);

		 ShowWindow(easyBtn,SW_HIDE);
		 ShowWindow(normalBtn,SW_HIDE);
		 ShowWindow(hardBtn,SW_HIDE);

		return 0;

	case WM_COMMAND:
		switch(LOWORD(wParam)){
			case 101:
				ShowWindow(startBtn,SW_HIDE);
				ShowWindow(quitBtn,SW_HIDE);
				ShowWindow(easyBtn,SW_SHOW);
			    ShowWindow(normalBtn,SW_SHOW);
				ShowWindow(hardBtn,SW_SHOW);
				break;
			case 102:
				DestroyWindow(hWnd);
				return 0;
			case 103:
				level = 1;
				ShowWindow(hWnd,SW_HIDE);
				DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,SubDlgProc1);
				break;
			case 104:
				level = 2;
				ShowWindow(hWnd,SW_HIDE);
				DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,SubDlgProc1);
				break;
			case 105:
				level = 3;
				ShowWindow(hWnd,SW_HIDE);
				DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,SubDlgProc1);
				break;

			case ID_MENU_A:
				DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG3),hWnd,SubDlgProc3);
				break;
			case ID_MENU_B:
				DestroyWindow(hWnd);
				return 0;
		}
		return 0;
	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MemDC = CreateCompatibleDC(hdc);
		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		OldBitmap = (HBITMAP) SelectObject(MemDC, MyBitmap);
		GetObject(MyBitmap, sizeof(BITMAP), &bit);
		BitBlt(hdc, 0, 0, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);
		SelectObject(MemDC, OldBitmap);
		DeleteObject(MyBitmap);
		DeleteDC(MemDC);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}


void Draw_Mode(HDC hdc)
{
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
		
	if(level == 1)
		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	else if(level == 2)
		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	else if(level == 3)
		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));

	OldBitmap = (HBITMAP) SelectObject(MemDC, MyBitmap);
	GetObject(MyBitmap, sizeof(BITMAP), &bit);
	BitBlt(hdc, 0, 0, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
}

void Score_Save(HWND hDlg)
{
	static HANDLE hFile;

	DWORD dwWritten;
	WCHAR buf[1024] = L"";
	WORD wd = 0xFEFF;
	
	wsprintf(buf,L" Your score is %d",score);

	
	hFile = CreateFile(L"Score.txt",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	memcpy(buf,&wd,2);

		
	WriteFile(hFile,buf,(wcslen(buf)+1)*sizeof(WCHAR),&dwWritten,NULL);
	SetFilePointer(hFile,0,NULL,FILE_END);
		
	CloseHandle(hFile);
}

void Success_Call_Dialog(HWND hDlg, int id, LPCWSTR sscore)
{
	KillTimer(hDlg,id);
			
	EndDialog(hDlg, 0);

	Score_Save(hDlg);

	MessageBox(hDlg,sscore,L"save score into Score.txt",MB_OK);

	DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG2),hDlg,SubDlgProc2);
		
	find = 0;
}

void find_willy(HWND hDlg,int id)
{
	find = 1;
	InvalidateRect(hDlg,NULL,FALSE);
	SetTimer(hDlg,id,10,NULL);
}

void dont_find_willy(HWND hDlg)
{
		find = 2;
		chance--;
		InvalidateRect(hDlg,NULL,FALSE);
		if(chance == 0)
		{
			EndDialog(hDlg, 0);
			DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG2),hDlg,SubDlgProc2);
			
			find = 0;
		}
}

void Draw_Circle_or_not(HDC hdc,int x,int y)
{
	HBRUSH MyBrush,OldBrush;
	HPEN MyPen,OldPen;

	MyBrush = CreateSolidBrush(NULL_BRUSH);
	OldBrush = (HBRUSH)SelectObject(hdc,MyBrush);
	MyPen = CreatePen(PS_SOLID,5,RGB(255,0,0));
	OldPen = (HPEN)SelectObject(hdc,MyPen);

	SelectObject(hdc,GetStockObject(NULL_BRUSH));
	SelectObject(hdc,GetStockObject(RGB(255,0,0)));

		if(find == 1)
		{
			Ellipse(hdc,x-20,y-20,x+20,y+20);
		}
		else if(find == 2)
		{
			MoveToEx(hdc,x-20,y-20,NULL);  
			LineTo(hdc,x+20,y+20);
			MoveToEx(hdc,x+20,y-20,NULL);  
			LineTo(hdc,x-20,y+20);
		}

		SelectObject(hdc,OldBrush);
		DeleteObject(MyBrush);
		SelectObject(hdc,OldPen);
		DeleteObject(MyPen);
}

void Draw_Hart_or_Devil(HDC hdc)
{
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	if(chance == 3)
		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP8));
	if(chance == 2)
		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP9));
	if(chance == 1)
		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP10));
			
	OldBitmap = (HBITMAP) SelectObject(MemDC, MyBitmap);
	GetObject(MyBitmap, sizeof(BITMAP), &bit);
	BitBlt(hdc, 1050, 200, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
}



BOOL CALLBACK SubDlgProc1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
		
	static int mouseX,mouseY;

	static int timeout = 0;
	static WCHAR stime[128];
	static WCHAR sscore[128];

	
	switch (iMessage) {
	case WM_INITDIALOG:
		hDlgMain = hDlg;
		SetTimer(hDlg,4,1000,NULL);
		SendMessage(hDlg,WM_TIMER,4,0);
		return TRUE;

	case WM_SYSCOMMAND:
        switch(wParam)
        {
			case SC_MINIMIZE:
				break;
			case SC_CLOSE:
				ShowWindow(hWndMain,SW_SHOW);
				EndDialog(hDlg, 0);
                break;
			default: 
                return FALSE;
        }
        return TRUE;

	case WM_ERASEBKGND:
		hdc = GetDC(hDlg);
		Draw_Mode(hdc);
		ReleaseDC(hDlg,hdc);
		return TRUE;

	case WM_TIMER:

		switch(wParam){
		case 1:
		    Success_Call_Dialog(hDlg,1,sscore);
			break;
		case 2:
			Success_Call_Dialog(hDlg,2,sscore);
			break;
		case 3:
			Success_Call_Dialog(hDlg,3,sscore);
			break;

		case 4:
			if(time == 0)
			{
				KillTimer(hDlg,4);
				break;
			}

			InvalidateRect(hDlg,NULL,FALSE);
			timeout = 1;
			time--;
			score-=3;
		
			wsprintf(sscore,L"Your score is %d",score);
			wsprintf(stime,L"Remaining time is %d seconds",time);
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		
		if(level == 1){
			if(mouseX >= 430 && mouseX <= 480  && mouseY >= 320 && mouseY <= 480)
				find_willy(hDlg,1); 
		
			else
				dont_find_willy(hDlg); 
		}

		else if(level == 2){
			if(mouseX >= 740 && mouseX <= 770 && mouseY >= 570 && mouseY <= 640)
				find_willy(hDlg,2);
	
			else
				dont_find_willy(hDlg);
		}

		else if(level == 3){
			if(mouseX <= 200 && mouseX >= 150 && mouseY <= 200 && mouseY >= 150)
				find_willy(hDlg,3);
		
			else
				dont_find_willy(hDlg);
		}
		return 0;

	case WM_PAINT:
		hdc=BeginPaint(hDlg, &ps);

		if(timeout == 1){
			TextOut(hdc,1050,100,stime,wcslen(stime));
			if(time == 0)
			{
				chance = 1;
				dont_find_willy(hDlg);
			}
		}

		Draw_Circle_or_not(hdc, mouseX, mouseY);
		Draw_Hart_or_Devil(hdc);

		EndPaint(hDlg,&ps);
	}
	return FALSE;
	
}



void Draw_GameOver_or_Clear(HWND hDlg, HDC hdc,HBITMAP MyBitmap,HDC MemDC)
{
	HBITMAP OldBitmap;
	BITMAP bit;
	WCHAR str[100]=L"Click anywhere if you want to restart the game";
	RECT r;

	GetClientRect(hDlg,&r);

	OldBitmap = (HBITMAP) SelectObject(MemDC, MyBitmap);
	GetObject(MyBitmap, sizeof(BITMAP), &bit);
	BitBlt(hdc, 0, 0, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);
	SetTextColor(hdc,RGB(255,0,0));
	SetBkMode(hdc,TRANSPARENT);
	DrawText(hdc,str,wcslen(str),&r,DT_RIGHT);
	
	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
}

BOOL CALLBACK SubDlgProc2(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc, MemDC;
	HBITMAP MyBitmap;


	switch (iMessage) {
	case WM_INITDIALOG:
		hDlgMain = hDlg;
		return TRUE;

	case WM_SYSCOMMAND:
        switch(wParam)
        {
			case SC_MINIMIZE:
				break;
			case SC_CLOSE:
				chance = 3;
				ShowWindow(hWndMain,SW_SHOW);
				EndDialog(hDlg, 0);  
                break;
			default: 
                return FALSE;
        }
        return TRUE;

	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		MemDC = CreateCompatibleDC(hdc);

		if(find == 1){
			MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
		
		}
		else if(find == 2){
			MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
		}

	    Draw_GameOver_or_Clear(hDlg,hdc,MyBitmap,MemDC);

		EndPaint(hDlg,&ps);
		return 0;
	
	case WM_LBUTTONDOWN:
		time = 30;
		score = 100;
		chance = 3;
		ShowWindow(hWndMain,SW_SHOW);
		EndDialog(hDlg, 0);
		return 0;
	}

	return FALSE;
	
}


BOOL CALLBACK SubDlgProc3(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{ 
	switch(iMessage){
	case WM_INITDIALOG:
		hDlgMain = hDlg;
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg,IDOK);
			return TRUE;
		}
		return FALSE;

	}
	return FALSE;


}