/* T01FWIN.C
 * Пример базового макета программы под WinAPI.
 * Создание и поддержка простейшего окна.
 *
 * Programmer: DK6
 * Date: 01.06.2015
 */

#include <windows.h>
#include <math.h>

/* Имя класса окна */
#define WND_CLASS_NAME "My window class"

/* Ссылка вперед */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam );
 

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;
  /* HINSTANCE hIns = LoadLibrary("shell32"); */

  /* Регистрация класса окна */
  wc.style = CS_VREDRAW | CS_HREDRAW;                   
                                                        
                                                        
                                                        
                                                        
  wc.cbClsExtra = 0;                                    
  wc.cbWndExtra = 0;                                    
  wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);             
  wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);              
  wc.hInstance = hInstance;                             
  wc.lpszMenuName = NULL;                               
  wc.lpfnWndProc = MyWindowFunc;                        
  wc.lpszClassName = WND_CLASS_NAME;

  /* Регистрация класса в системе */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  /* Создание окна */
  hWnd =
    CreateWindow(WND_CLASS_NAME,    /* Имя класса окна */
      "Eyes",                      /* Заголовок окна */
      WS_OVERLAPPEDWINDOW,          /* Стили окна - окно общего вида */
      CW_USEDEFAULT, CW_USEDEFAULT, /* Позиция окна (x, y) - по умолчанию */
      CW_USEDEFAULT, CW_USEDEFAULT, /* Размеры окна (w, h) - по умолчанию */
      NULL,                         /* Дескриптор родительского окна */
      NULL,                         /* Дескриптор загруженного меню */
      hInstance,                    /* Дескриптор приложения */
      NULL);                        /* Указатель на дополнительные параметры */

  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

  /* Запуск цикла сообщений окна */
  while (GetMessage(&msg, NULL, 0, 0))
    /* Передача сообщений в функцию окна */
    DispatchMessage(&msg);

  return 30;
} /* End of 'WinMain' function */


/* Функция рисования глаза.
 * АГРУМЕНТЫ:
 *   - сонтекст окна:
 *       HDC hDC;
 *   - абсцисса левого верхнего края прямоугольника, ограничивающего глаз:
 *       int left;
 *   - ордината левого верхнего края прямоугольника, ограничивающего глаз:
 *       int top;
 *   - абсцисса правого нижнего края прямоугольника, ограничивающего глаз:
 *       int right;
 *   - ордината правого нижнего края прямоугольника, ограничивающего глаз:
 *       int bottom;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (VOID) ничего
 */
void DrawEye( HDC hDC, int left, int top, int right, int bottom )
{
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(0, 0, 0));
  Ellipse(hDC, left, top, right, bottom);
  SetDCBrushColor(hDC, RGB(255, 255, 255));
} /* End of 'DrawEye' function */


/* Функция обработки сообщения окна.
 * АРГУМЕНТЫ:
 *   - дескриптор окна:
 *       HWND hWnd;
 *   - номер сообщения (см. WM_***):
 *       UINT Msg;
 *   - параметр сообшения ('word parameter'):
 *       WPARAM wParam;
 *   - параметр сообшения ('long parameter'):
 *       LPARAM lParam;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (LRESULT) - в зависимости от сообщения.
 */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  HDC hDC;         /* Display context */
  static int w, h, x, y;
  POINT pt;        /* The point of cursor */
  PAINTSTRUCT ps;
  int CEyeF = 240, CEyeFy = 240, CEyeS = 460, CEyeSy = 240, R = 65;
  int Rx1, Ry1, Rx2, Ry2; /* The coordinats of center */

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 111, 50, NULL);
    return 0;

  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    return 0;

  case WM_TIMER:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(255, 255, 0));
    Rectangle(hDC, 0, 0, w, h);
    SetDCBrushColor(hDC, RGB(255, 255, 255));


    x = pt.x;
    y = pt.y;

    Ellipse(hDC, 160, 160, 321, 321);
    Ellipse(hDC, 380, 160, 541, 321);

    Rx1 = R * abs(CEyeF - x) / (INT)sqrt((CEyeF - x) * (CEyeF - x) + (CEyeFy - y) * (CEyeFy - y));
    Ry1 = R * abs(CEyeFy - y) / (INT)sqrt((CEyeF - x) * (CEyeF - x) + (CEyeFy - y) * (CEyeFy - y));
    Rx2 = R * abs(CEyeS - x) / (INT)sqrt((CEyeS - x) * (CEyeS - x) + (CEyeSy - y) * (CEyeSy - y));
    Ry2 = R * abs(CEyeSy - y) / (INT)sqrt((CEyeS - x) * (CEyeS - x) + (CEyeSy - y) * (CEyeSy - y));

    if (x > CEyeF && x < CEyeS)
      Rx2 = -Rx2;
    if (x < CEyeF)
      Rx1 = -Rx1, Rx2 = -Rx2;
    if (y < CEyeFy)
      Ry1 = -Ry1, Ry2 = -Ry2;


    SelectObject(hDC, GetStockObject(DC_PEN));
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(0, 0, 0));
    SetDCPenColor(hDC, RGB(0, 0, 0));
    DrawEye(hDC, CEyeF + Rx1 - 16, CEyeFy + Ry1 - 16, CEyeF + Rx1 + 16, CEyeFy + Ry1 + 16);
    DrawEye(hDC, CEyeS + Rx2 - 16, CEyeSy + Ry2 - 16, CEyeS + Rx2 + 16, CEyeSy + Ry2 + 16);
    SelectObject(hDC, GetStockObject(NULL_PEN));
    SelectObject(hDC, GetStockObject(NULL_BRUSH));

    EndPaint(hWnd, &ps);
    return 0;

  case WM_KEYDOWN:
    if (wParam == 27)
      DestroyWindow(hWnd);
    return 0;

  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDNO)
      return 0;
    break;

  case WM_DESTROY:
    KillTimer(hWnd, 111);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} 
