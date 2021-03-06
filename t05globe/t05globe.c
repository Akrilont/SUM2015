/* FILE NAME: T05GLOBE.C
* PROGRAMMER: DK6
* DATE: 04.06.2015
* PURPOSE: WinAPI sphere drawing.
*/
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include "globe.h"

/* ��� ������ ���� */
#define WND_CLASS_NAME "My window class"
/* �������� � ������ WireFrame ��� ��� */
BOOL IsWire = FALSE;
extern INT Radius;
/* ������ ������ */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
WPARAM wParam, LPARAM lParam );
/* ������� ������� ���������.
* - ���������� ���������� ����������:
* HINSTANCE hInstance;
* - ���������� ����������� ���������� ����������
* (�� ������������ � ������ ���� NULL):
* HINSTANCE hPrevInstance;
* - ��������� ������:
* CHAR *CmdLine;
* ������������ ��������:
* (INT) ��� �������� � ������������ �������.
* 0 - ��� ������.
*/
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
CHAR *CmdLine, INT ShowCmd )
{
WNDCLASS wc;
HWND hWnd;
MSG msg;
/* ����������� ������ ���� */
wc.style = CS_VREDRAW | CS_HREDRAW; /* ����� ����: ��������� ��������������
* ��� ��������� ������������� ���
* ��������������� ��������
* ��� ����� CS_DBLCLKS ��� ����������
* ��������� �������� ������� */
wc.cbClsExtra = 0; /* �������������� ���������� ���� ��� ������ */
wc.cbWndExtra = 0; /* �������������� ���������� ���� ��� ���� */
wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));
wc.hCursor = LoadCursor(NULL, IDC_ARROW); /* �������� ������� (����������) */
wc.hIcon = LoadIcon(NULL, IDI_ASTERISK); /* �������� ����������� (���������) */
wc.hInstance = hInstance; /* ���������� ����������, ��������������� ����� */
wc.lpszMenuName = NULL; /* ��� ������� ���� */
wc.lpfnWndProc = MyWindowFunc; /* ��������� �� ������� ��������� */
wc.lpszClassName = WND_CLASS_NAME;
/* ����������� ������ � ������� */
if (!RegisterClass(&wc))
{
MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
return 0;
}
/* �������� ���� */
hWnd =
CreateWindow(WND_CLASS_NAME, /* ��� ������ ���� */
"Sphera", /* ��������� ���� */
WS_OVERLAPPEDWINDOW, /* ����� ���� - ���� ������ ���� */
CW_USEDEFAULT, CW_USEDEFAULT, /* ������� ���� (x, y) - �� ��������� */
CW_USEDEFAULT, CW_USEDEFAULT, /* ������� ���� (w, h) - �� ��������� */
NULL, /* ���������� ������������� ���� */
NULL, /* ���������� ������������ ���� */
hInstance, /* ���������� ���������� */
NULL); /* ��������� �� �������������� ��������� */
ShowWindow(hWnd, ShowCmd);
UpdateWindow(hWnd);
/* ������ ����� ��������� ���� */
while (GetMessage(&msg, NULL, 0, 0))
/* �������� ��������� � ������� ���� */
DispatchMessage(&msg);
return 30;
} /* End of 'WinMain' function */
/* ������� ������������ �/�� �������������� ������
* � ������ ���������� ���������.
* ���������:
* - ���������� ����:
* HWND hWnd;
* ������������ ��������: ���.
*/
VOID FlipFullScreen( HWND hWnd )
{
static BOOL IsFullScreen = FALSE;
static RECT SaveRC;
if (!IsFullScreen)
{
RECT rc;
HMONITOR hmon;
MONITORINFOEX moninfo;
/* Save old size of window */
GetWindowRect(hWnd, &SaveRC);
hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
moninfo.cbSize = sizeof(moninfo);
GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);
/* ��������� � ������ ����� */
/* ��� ������ ��������:
rc.left = 0;
rc.top = 0;
rc.right = GetSystemMetrics(SM_CXSCREEN);
rc.bottom = GetSystemMetrics(SM_CXSCREEN);
*/
rc = moninfo.rcMonitor;
AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
SetWindowPos(hWnd, HWND_TOPMOST, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top + 201,
SWP_NOOWNERZORDER);
IsFullScreen = TRUE;
}
else
{
SetWindowPos(hWnd, HWND_TOPMOST, SaveRC.left, SaveRC.top,
SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
SWP_NOOWNERZORDER);
IsFullScreen = FALSE;
}
} /* End of 'FlipFullScreen' function */
/* ������� ��������� ��������� ����.
* ���������:
* - ���������� ����:
* HWND hWnd;
* - ����� ��������� (��. WM_***):
* UINT Msg;
* - �������� ��������� ('word parameter'):
* WPARAM wParam;
* - �������� ��������� ('long parameter'):
* LPARAM lParam;
* ������������ ��������:
* (LRESULT) - � ����������� �� ���������.
*/
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
WPARAM wParam, LPARAM lParam )
{
HDC hDC;
static HDC hMemDC;
static INT w, h;
static BITMAP bm;
static HBITMAP hBm;
switch (Msg)
{
case WM_CREATE:
SetTimer(hWnd, 111, 50, NULL);
/* ������� �������� � ������ */
hDC = GetDC(hWnd);
hMemDC = CreateCompatibleDC(hDC);
ReleaseDC(hWnd, hDC);
return 0;
case WM_SIZE:
w = LOWORD(lParam);
h = HIWORD(lParam);
/* ������� �������� �������� � ���� */
if (hBm != NULL)
DeleteObject(hBm);
hDC = GetDC(hWnd);
hBm = CreateCompatibleBitmap(hDC, w, h);
ReleaseDC(hWnd, hDC);
SelectObject(hMemDC, hBm);
SendMessage(hWnd, WM_TIMER, 111, 0);
return 0;
case WM_TIMER:
/* Clear Background */
SelectObject(hMemDC, GetStockObject(NULL_PEN));
SelectObject(hMemDC, GetStockObject(DC_BRUSH));
SetDCBrushColor(hMemDC, RGB(255, 255, 255));
Rectangle(hMemDC, 0, 0, w + 1, h + 1);
SelectObject(hMemDC, GetStockObject(NULL_PEN));
SelectObject(hMemDC, GetStockObject(DC_BRUSH));
SetDCBrushColor(hMemDC, RGB(255, 0, 0));
GlobeBuild();
GlobeDraw(hMemDC, w, h);
InvalidateRect(hWnd, NULL, TRUE);
return 0;
case WM_KEYDOWN:
if (wParam == 'F')
  FlipFullScreen(hWnd);
if (wParam == 27)
  SendMessage(hWnd, WM_CLOSE, 0, 0);
if (wParam == 'W')
  IsWire = !IsWire;
return 0;

case WM_CLOSE:
if (MessageBox(hWnd, "Are you shure to exit from program?",
"Exit", MB_YESNO | MB_ICONQUESTION) == IDNO)
return 0;
break;
case WM_ERASEBKGND:
BitBlt((HDC)wParam, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
return 0;
case WM_DESTROY:
DeleteDC(hMemDC);
DeleteObject(hBm);
KillTimer(hWnd, 111);
PostQuitMessage(0);
return 0;
}
return DefWindowProc(hWnd, Msg, wParam, lParam);
}