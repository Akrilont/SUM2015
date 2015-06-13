/* FILENAME: ANIM.C
 * PROGRAMMER: dk6
 * PURPOSE: Animation system module.
 * LAST UPDATE: 08.06.2015
 */

#include "anim.h"
#include "render.h"
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm")


#define dk6_GET_AXIS_VALUE(Axis) \
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
  dk6_MouseOldX, dk6_MouseOldY;


dk6ANIM dk6_Anim;


BOOL dk6_AnimInit( HWND hWnd )
{
  INT i;
  LARGE_INTEGER li;
  POINT pt;
  PIXELFORMATDESCRIPTOR pfd = {0};

  memset(&dk6_Anim, 0, sizeof(dk6ANIM));
  dk6_Anim.hWnd = hWnd;
  dk6_Anim.hDC = GetDC(hWnd);

  dk6_Anim.W = 30;
  dk6_Anim.H = 30;
  dk6_Anim.NumOfUnits = 0;

  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(dk6_Anim.hDC, &pfd);
  DescribePixelFormat(dk6_Anim.hDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(dk6_Anim.hDC, i, &pfd);

  dk6_Anim.hGLRC = wglCreateContext(dk6_Anim.hDC);
  wglMakeCurrent(dk6_Anim.hDC, dk6_Anim.hGLRC);

  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(dk6_Anim.hGLRC);
    ReleaseDC(dk6_Anim.hWnd, dk6_Anim.hDC);
    memset(&dk6_Anim, 0, sizeof(dk6ANIM));
    return FALSE;
  }

  dk6_RndProg = dk6_ShaderLoad("TEST");

  QueryPerformanceFrequency(&li);
  TimeFreq = li.QuadPart;
  QueryPerformanceCounter(&li);
  TimeStart = TimeOld = TimeFPS = li.QuadPart;
  dk6_Anim.IsPause = FALSE;
  FrameCounter = 0;

  GetCursorPos(&pt);
  ScreenToClient(dk6_Anim.hWnd, &pt);
  dk6_MouseOldX = pt.x;
  dk6_MouseOldY = pt.y;
  GetKeyboardState(dk6_Anim.KeysOld);
  return TRUE;
} /* End of 'dk6_AnimInit' function */


VOID dk6_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < dk6_Anim.NumOfUnits; i++)
  {
    dk6_Anim.Units[i]->Close(dk6_Anim.Units[i], &dk6_Anim);
    free(dk6_Anim.Units[i]);
    dk6_Anim.Units[i] = NULL;
  }

  dk6_ShaderFree(dk6_RndProg);
  dk6_RndProg = 0;
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(dk6_Anim.hGLRC);
  ReleaseDC(dk6_Anim.hWnd, dk6_Anim.hDC);
} /* End of 'dk6_AnimClose' function */


VOID dk6_AnimResize( INT W, INT H )
{

  dk6_Anim.W = W;
  dk6_Anim.H = H;

  glViewport(0, 0, W, H);

  if (W > H)
    dk6_RndWp = (DBL)W / H * 3, dk6_RndHp = 3;
  else
    dk6_RndHp = (DBL)H / W * 3, dk6_RndWp = 3;

  dk6_RndMatrProj = MatrFrustum(-dk6_RndWp / 2, dk6_RndWp / 2, -dk6_RndHp / 2, dk6_RndHp / 2, dk6_RndProjDist, 800);
} /* End of 'dk6_AnimResize' function */


VOID dk6_AnimRender( VOID )
{
  INT i;
  LARGE_INTEGER li;
  static CHAR Buf[100];
  HFONT hFnt, hOldFnt;
  POINT pt;


  QueryPerformanceCounter(&li);
  dk6_Anim.GlobalTime = (DBL)(li.QuadPart - TimeStart) / TimeFreq;
  dk6_Anim.GlobalDeltaTime = (DBL)(li.QuadPart - TimeOld) / TimeFreq;

  if (!dk6_Anim.IsPause)
    dk6_Anim.DeltaTime = dk6_Anim.GlobalDeltaTime;
  else
  {
    TimePause += li.QuadPart - TimeOld;
    dk6_Anim.DeltaTime = 0;
  }

  dk6_Anim.Time = (DBL)(li.QuadPart - TimePause - TimeStart) / TimeFreq;


  if (li.QuadPart - TimeFPS > TimeFreq)
  {
    dk6_Anim.FPS = FrameCounter / ((DBL)(li.QuadPart - TimeFPS) / TimeFreq);
    TimeFPS = li.QuadPart;
    FrameCounter = 0;
  }


  TimeOld = li.QuadPart;



  GetKeyboardState(dk6_Anim.Keys);
  for (i = 0; i < 256; i++)
    dk6_Anim.Keys[i] >>= 7;
  for (i = 0; i < 256; i++)
    dk6_Anim.KeysClick[i] = dk6_Anim.Keys[i] && !dk6_Anim.KeysOld[i];
  memcpy(dk6_Anim.KeysOld, dk6_Anim.Keys, sizeof(dk6_Anim.KeysOld));



  dk6_Anim.MsWheel = dk6_MouseWheel;
  dk6_MouseWheel = 0;

  GetCursorPos(&pt);
  ScreenToClient(dk6_Anim.hWnd, &pt);
  dk6_Anim.MsX = pt.x;
  dk6_Anim.MsY = pt.y;

  dk6_Anim.MsDeltaX = pt.x - dk6_MouseOldX;
  dk6_Anim.MsDeltaY = pt.y - dk6_MouseOldY;
  dk6_MouseOldX = pt.x;
  dk6_MouseOldY = pt.y;


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

        memcpy(dk6_Anim.JButsOld, dk6_Anim.JButs, sizeof(dk6_Anim.JButs));
        for (i = 0; i < 32; i++)
          dk6_Anim.JButs[i] = (ji.dwButtons >> i) & 1;
        for (i = 0; i < 32; i++)
          dk6_Anim.JButsClick[i] = dk6_Anim.JButs[i] && !dk6_Anim.JButsOld[i];


        dk6_Anim.JX = dk6_GET_AXIS_VALUE(X);
        dk6_Anim.JY = dk6_GET_AXIS_VALUE(Y);
        if (jc.wCaps & JOYCAPS_HASZ)
          dk6_Anim.JZ = dk6_GET_AXIS_VALUE(Z);
        if (jc.wCaps & JOYCAPS_HASU)
          dk6_Anim.JU = dk6_GET_AXIS_VALUE(U);
        if (jc.wCaps & JOYCAPS_HASV)
          dk6_Anim.JV = dk6_GET_AXIS_VALUE(V);
        if (jc.wCaps & JOYCAPS_HASR)
          dk6_Anim.JR = dk6_GET_AXIS_VALUE(R);

        if (jc.wCaps & JOYCAPS_HASPOV)
        {
          if (ji.dwPOV == 0xFFFF)
            dk6_Anim.JPOV = 0;
          else
            dk6_Anim.JPOV = ji.dwPOV / 4500 + 1;
        }
      }
    }
  }


  for (i = 0; i < dk6_Anim.NumOfUnits; i++)
    dk6_Anim.Units[i]->Response(dk6_Anim.Units[i], &dk6_Anim);

  glClearColor(0.3, 0.5, 0.7, 1);
  glClearDepth(1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColorMask(TRUE, TRUE, TRUE, FALSE);

  /* Writing the time and the date at the moment */
  hFnt = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE,
    FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH | FF_ROMAN, "");
  hOldFnt = SelectObject(dk6_Anim.hDC, hFnt);

  SetTextColor(dk6_Anim.hDC, RGB(59, 255, 230));
  SetBkColor(dk6_Anim.hDC, RGB(255, 255, 0));
  SetBkMode(dk6_Anim.hDC, TRANSPARENT);

  TextOut(dk6_Anim.hDC, dk6_Anim.W - 200, dk6_Anim.H / 30 - 15, Buf,
      sprintf(Buf, "FPS: %.5f", dk6_Anim.FPS));

  SetTextColor(dk6_Anim.hDC, RGB(255, 55, 30));
  SetBkColor(dk6_Anim.hDC, RGB(255, 255, 0));
  SetBkMode(dk6_Anim.hDC, TRANSPARENT);

  TextOut(dk6_Anim.hDC, dk6_Anim.W - 200, dk6_Anim.H / 30 + 15, Buf,
      sprintf(Buf, "The time: %.2f", dk6_Anim.Time));

  DeleteObject(hFnt);

  SelectObject(dk6_Anim.hDC, hOldFnt);
  DeleteObject(hFnt);

  /*
  glColor3d(0.3, 0.5, 0.7);
  glRectd(-2, -2, 2, 2);
  glColor3d(1, 0, 0);
  glRectd(0, 0, 0.88, 0.30);
  */

  for (i = 0; i < dk6_Anim.NumOfUnits; i++)
  {
    static DBL time = 5;

    time += dk6_Anim.GlobalDeltaTime;
    if (time > 5)
    {
      time = 0;
      dk6_ShaderFree(dk6_RndProg);
      dk6_RndProg = dk6_ShaderLoad("TEST");
    }

    dk6_RndMatrWorld = MatrIdentity();

    dk6_Anim.Units[i]->Render(dk6_Anim.Units[i], &dk6_Anim);
  }
  glFinish();
  FrameCounter++;
} /* End of 'dk6_AnimRender' function */


VOID dk6_AnimCopyFrame( VOID )
{
  SwapBuffers(dk6_Anim.hDC);
} /* End of 'dk6_AnimCopyFrame' function */


VOID dk6_AnimAddUnit( dk6UNIT *Unit )
{
  if (dk6_Anim.NumOfUnits < dk6_MAX_UNITS)
  {
    dk6_Anim.Units[dk6_Anim.NumOfUnits++] = Unit;
    Unit->Init(Unit, &dk6_Anim);
  }
} /* End of 'dk6_AnimAddUnit' function */



VOID dk6_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRC;

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;


    GetWindowRect(dk6_Anim.hWnd, &SaveRC);

  
    hmon = MonitorFromWindow(dk6_Anim.hWnd, MONITOR_DEFAULTTONEAREST);


    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    
    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(dk6_Anim.hWnd, GWL_STYLE), FALSE);

    SetWindowPos(dk6_Anim.hWnd, HWND_TOPMOST,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    
    SetWindowPos(dk6_Anim.hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'dk6_AnimFlipFullScreen' function */


VOID dk6_AnimDoExit( VOID )
{
  PostMessage(dk6_Anim.hWnd, WM_CLOSE, 0, 0);
} /* End of 'dk6_AnimDoExit' function */


VOID dk6_AnimSetPause( BOOL NewPauseFlag )
{
  dk6_Anim.IsPause = NewPauseFlag;
} /* End of 'dk6_AnimSetPause' function */

/* END OF 'ANIM.C' FILE */