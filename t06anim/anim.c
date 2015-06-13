/* FILENAME: ANIM.C
 * PROGRAMMER: DK6
 * PURPOSE: Animation system module.
 * LAST UPDATE: 08.06.2015
 */

#include "anim.h"
#include "render.h"
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm")


#define DK6_GET_AXIS_VALUE(Axis) \
  (2.0 * (ji.dw ## Axis ## pos - jc.w ## Axis ## min) / (jc.w ## Axis ## max - jc.w ## Axis ## min) - 1.0)


static INT64
  TimeFreq,  
  TimeStart,
  TimeOld,  
  TimePause,
  TimeFPS; 
static INT
  FrameCounter; 


static INT
  DK6_MouseOldX, DK6_MouseOldY;


DK6ANIM DK6_Anim;

VOID DK6_AnimInit( HWND hWnd )
{
  HDC hDC = GetDC(hWnd);
  LARGE_INTEGER li;
  POINT pt;

  memset(&DK6_Anim, 0, sizeof(DK6ANIM));
  DK6_Anim.hWnd = hWnd;
  DK6_Anim.hDC = CreateCompatibleDC(hDC);
  DK6_Anim.hBmFrame = CreateCompatibleBitmap(hDC, 30, 30);
  SelectObject(DK6_Anim.hDC, DK6_Anim.hBmFrame);
  DK6_Anim.W = 30;
  DK6_Anim.H = 30;
  DK6_Anim.NumOfUnits = 0;
  ReleaseDC(hWnd, hDC);


  QueryPerformanceFrequency(&li);
  TimeFreq = li.QuadPart;
  QueryPerformanceCounter(&li);
  TimeStart = TimeOld = TimeFPS = li.QuadPart;
  DK6_Anim.IsPause = FALSE;
  FrameCounter = 0;

 
  GetCursorPos(&pt);
  ScreenToClient(DK6_Anim.hWnd, &pt);
  DK6_MouseOldX = pt.x;
  DK6_MouseOldY = pt.y;
  GetKeyboardState(DK6_Anim.KeysOld);
} /* End of 'DK6_AnimInit' function */


VOID DK6_AnimClose( VOID )
{
  INT i;

 
  for (i = 0; i < DK6_Anim.NumOfUnits; i++)
  {
    DK6_Anim.Units[i]->Close(DK6_Anim.Units[i], &DK6_Anim);
    free(DK6_Anim.Units[i]);
    DK6_Anim.Units[i] = NULL;
  }


  DeleteObject(DK6_Anim.hBmFrame);
  DeleteDC(DK6_Anim.hDC);
} /* End of 'DK6_AnimClose' function */


VOID DK6_AnimResize( INT W, INT H )
{
  HDC hDC = GetDC(DK6_Anim.hWnd);

 
  DeleteObject(DK6_Anim.hBmFrame);
  DK6_Anim.hBmFrame = CreateCompatibleBitmap(hDC, W, H);
  SelectObject(DK6_Anim.hDC, DK6_Anim.hBmFrame);


  DK6_Anim.W = W;
  DK6_Anim.H = H;

  ReleaseDC(DK6_Anim.hWnd, hDC);

  if (W > H)
    DK6_RndWp = (DBL)W / H * 3, DK6_RndHp = 3;
  else
    DK6_RndHp = (DBL)H / W * 3, DK6_RndWp = 3;

  DK6_RndMatrProj = MatrFrustum(-DK6_RndWp / 2, DK6_RndWp / 2, -DK6_RndHp / 2, DK6_RndHp / 2, DK6_RndProjDist, 800);
} /* End of 'DK6_AnimResize' function */


VOID DK6_AnimRender( VOID )
{
  INT i;
  LARGE_INTEGER li;
  static CHAR Buf[100];
  HFONT hFnt, hOldFnt;
  POINT pt;


  SelectObject(DK6_Anim.hDC, GetStockObject(DC_BRUSH));
  SelectObject(DK6_Anim.hDC, GetStockObject(NULL_PEN));
  SetDCBrushColor(DK6_Anim.hDC, RGB(0, 0, 0));
  Rectangle(DK6_Anim.hDC, 0, 0, DK6_Anim.W + 1, DK6_Anim.H + 1);


  QueryPerformanceCounter(&li);
  DK6_Anim.GlobalTime = (DBL)(li.QuadPart - TimeStart) / TimeFreq;
  DK6_Anim.GlobalDeltaTime = (DBL)(li.QuadPart - TimeOld) / TimeFreq;

  if (!DK6_Anim.IsPause)
    DK6_Anim.DeltaTime = DK6_Anim.GlobalDeltaTime;
  else
  {
    TimePause += li.QuadPart - TimeOld;
    DK6_Anim.DeltaTime = 0;
  }

  DK6_Anim.Time = (DBL)(li.QuadPart - TimePause - TimeStart) / TimeFreq;

 
  if (li.QuadPart - TimeFPS > TimeFreq)
  {
    DK6_Anim.FPS = FrameCounter / ((DBL)(li.QuadPart - TimeFPS) / TimeFreq);
    TimeFPS = li.QuadPart;
    FrameCounter = 0;
  }

  
  TimeOld = li.QuadPart;


 

  
  GetKeyboardState(DK6_Anim.Keys);
  for (i = 0; i < 256; i++)
    DK6_Anim.Keys[i] >>= 7;
  for (i = 0; i < 256; i++)
    DK6_Anim.KeysClick[i] = DK6_Anim.Keys[i] && !DK6_Anim.KeysOld[i];
  memcpy(DK6_Anim.KeysOld, DK6_Anim.Keys, sizeof(DK6_Anim.KeysOld));

  
  DK6_Anim.MsWheel = DK6_MouseWheel;
  DK6_MouseWheel = 0;
 
  GetCursorPos(&pt);
  ScreenToClient(DK6_Anim.hWnd, &pt);
  DK6_Anim.MsX = pt.x;
  DK6_Anim.MsY = pt.y;
  
  DK6_Anim.MsDeltaX = pt.x - DK6_MouseOldX;
  DK6_Anim.MsDeltaY = pt.y - DK6_MouseOldY;
  DK6_MouseOldX = pt.x;
  DK6_MouseOldY = pt.y;

  
  if ((i = joyGetNumDevs()) > 0)
  {
    JOYCAPS jc;

   
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      
      ji.dwSize = sizeof(JOYCAPS);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        
        memcpy(DK6_Anim.JButsOld, DK6_Anim.JButs, sizeof(DK6_Anim.JButs));
        for (i = 0; i < 32; i++)
          DK6_Anim.JButs[i] = (ji.dwButtons >> i) & 1;
        for (i = 0; i < 32; i++)
          DK6_Anim.JButsClick[i] = DK6_Anim.JButs[i] && !DK6_Anim.JButsOld[i];

        
        DK6_Anim.JX = DK6_GET_AXIS_VALUE(X);
        DK6_Anim.JY = DK6_GET_AXIS_VALUE(Y);
        if (jc.wCaps & JOYCAPS_HASZ)
          DK6_Anim.JZ = DK6_GET_AXIS_VALUE(Z);
        if (jc.wCaps & JOYCAPS_HASU)
          DK6_Anim.JU = DK6_GET_AXIS_VALUE(U);
        if (jc.wCaps & JOYCAPS_HASV)
          DK6_Anim.JV = DK6_GET_AXIS_VALUE(V);
        if (jc.wCaps & JOYCAPS_HASR)
          DK6_Anim.JR = DK6_GET_AXIS_VALUE(R);

        if (jc.wCaps & JOYCAPS_HASPOV)
        {
          if (ji.dwPOV == 0xFFFF)
            DK6_Anim.JPOV = 0;
          else
            DK6_Anim.JPOV = ji.dwPOV / 4500 + 1;
        }
      }
    }
  }

  
  for (i = 0; i < DK6_Anim.NumOfUnits; i++)
    DK6_Anim.Units[i]->Response(DK6_Anim.Units[i], &DK6_Anim);

  
  for (i = 0; i < DK6_Anim.NumOfUnits; i++)
  {
    SelectObject(DK6_Anim.hDC, GetStockObject(DC_BRUSH));
    SelectObject(DK6_Anim.hDC, GetStockObject(DC_PEN));
    SetDCBrushColor(DK6_Anim.hDC, RGB(255, 255, 255));
    SetDCPenColor(DK6_Anim.hDC, RGB(255, 255, 255));

    DK6_Anim.Units[i]->Render(DK6_Anim.Units[i], &DK6_Anim);
  }

  /* Writing the time and the date at the moment */
  hFnt = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE,
    FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH | FF_ROMAN, "");
  hOldFnt = SelectObject(DK6_Anim.hDC, hFnt);

  SetTextColor(DK6_Anim.hDC, RGB(59, 255, 230));
  SetBkColor(DK6_Anim.hDC, RGB(255, 255, 0));
  SetBkMode(DK6_Anim.hDC, TRANSPARENT);

  TextOut(DK6_Anim.hDC, DK6_Anim.W - 200, DK6_Anim.H / 30 - 15, Buf,
      sprintf(Buf, "FPS: %.5f", DK6_Anim.FPS));

  SetTextColor(DK6_Anim.hDC, RGB(255, 55, 30));
  SetBkColor(DK6_Anim.hDC, RGB(255, 255, 0));
  SetBkMode(DK6_Anim.hDC, TRANSPARENT);

  TextOut(DK6_Anim.hDC, DK6_Anim.W - 200, DK6_Anim.H / 30 + 15, Buf,
      sprintf(Buf, "The time: %.2f", DK6_Anim.Time));

  DeleteObject(hFnt);

  SelectObject(DK6_Anim.hDC, hOldFnt);
  DeleteObject(hFnt);

  FrameCounter++;
} /* End of 'DK6_AnimRender' function */


VOID DK6_AnimCopyFrame( VOID )
{
  HDC hDC;

  
  hDC = GetDC(DK6_Anim.hWnd);
  BitBlt(hDC, 0, 0, DK6_Anim.W, DK6_Anim.H, DK6_Anim.hDC, 0, 0, SRCCOPY);
  ReleaseDC(DK6_Anim.hWnd, hDC);
} /* End of 'DK6_AnimCopyFrame' function */


VOID DK6_AnimAddUnit( DK6UNIT *Unit )
{
  if (DK6_Anim.NumOfUnits < DK6_MAX_UNITS)
  {
    DK6_Anim.Units[DK6_Anim.NumOfUnits++] = Unit;
    Unit->Init(Unit, &DK6_Anim);
  }
} /* End of 'DK6_AnimAddUnit' function */



VOID DK6_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE; 
  static RECT SaveRC;

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    
    GetWindowRect(DK6_Anim.hWnd, &SaveRC);

    
    hmon = MonitorFromWindow(DK6_Anim.hWnd, MONITOR_DEFAULTTONEAREST);

    
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    
    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(DK6_Anim.hWnd, GWL_STYLE), FALSE);

    SetWindowPos(DK6_Anim.hWnd, HWND_TOPMOST,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    
    SetWindowPos(DK6_Anim.hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'DK6_AnimFlipFullScreen' function */


VOID DK6_AnimDoExit( VOID )
{
  PostMessage(DK6_Anim.hWnd, WM_CLOSE, 0, 0);
} /* End of 'DK6_AnimDoExit' function */


VOID DK6_AnimSetPause( BOOL NewPauseFlag )
{
  DK6_Anim.IsPause = NewPauseFlag;
} /* End of 'DK6_AnimSetPause' function */

/* END OF 'ANIM.C' FILE */