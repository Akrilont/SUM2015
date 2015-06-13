/* FILENAME: UBALL.C
 * PROGRAMMER: DK6
 * PURPOSE: Bounce ball unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>
#include <time.h>

#include "anim.h"
#include "vec.h"

/* Тип представления мяча */
typedef struct tagDK6UNIT_BALL
{
  DK6_UNIT_BASE_FIELDS;

  VEC Pos;     /* Позиция мяча */
  DWORD Color; /* Цвет мяча */
  DBL
    Amplitude,  /* Амплитуда */
    PhaseShift, /* Сдвиг по фазе */
    ScaleShift; /* Масштаб времени */
} DK6UNIT_BALL;

/* Функция инициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       DK6UNIT_BALL *Uni;
 *   - указатель на контекст анимации:
 *       DK6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID DK6_AnimUnitInit( DK6UNIT_BALL *Uni, DK6ANIM *Ani )
{
  Uni->Pos = VecSet(rand() % 1000, rand() % 700, 0);
  Uni->Color = RGB(rand() % 256, rand() % 256, rand() % 256);
  Uni->PhaseShift = rand() % 3000;
  Uni->ScaleShift = 5 + 0.30 * rand() / RAND_MAX;
  Uni->Amplitude = 30 + 59.0 * rand() / RAND_MAX;
} /* End of 'DK6_AnimUnitInit' function */

/* Функция деинициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       DK6UNIT_BALL *Uni;
 *   - указатель на контекст анимации:
 *       DK6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID DK6_AnimUnitClose( DK6UNIT_BALL *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitClose' function */

/* Функция обновления межкадровых параметров объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       DK6UNIT_BALL *Uni;
 *   - указатель на контекст анимации:
 *       DK6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID DK6_AnimUnitResponse( DK6UNIT_BALL *Uni, DK6ANIM *Ani )
{
  if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    DK6_AnimDoExit();
  if (GetAsyncKeyState('F') & 0x8000)
    DK6_AnimFlipFullScreen();
} /* End of 'DK6_AnimUnitResponse' function */

/* Функция построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       DK6UNIT_BALL *Uni;
 *   - указатель на контекст анимации:
 *       DK6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID DK6_AnimUnitRender( DK6UNIT_BALL *Uni, DK6ANIM *Ani )
{
  DBL shift = Uni->Amplitude * fabs(sin(Uni->ScaleShift * (DBL)clock() / CLOCKS_PER_SEC + Uni->PhaseShift));

  SetDCBrushColor(Ani->hDC, Uni->Color);
  Ellipse(Ani->hDC, Uni->Pos.X - 5, Uni->Pos.Y - 5 - shift, Uni->Pos.X + 5, Uni->Pos.Y + 5 - shift);
} /* End of 'DK6_AnimUnitRender' function */

/* Функция создания объекта анимации "мяч".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (DK6UNIT *) указатель на созданный объект анимации.
 */
DK6UNIT * DK6_UnitBallCreate( VOID )
{
  DK6UNIT_BALL *Uni;

  if ((Uni = (VOID *)DK6_AnimUnitCreate(sizeof(DK6UNIT_BALL))) == NULL)
    return NULL;
  /* заполняем поля */
  Uni->Init = (VOID *)DK6_AnimUnitInit;
  Uni->Close = (VOID *)DK6_AnimUnitClose;
  Uni->Response = (VOID *)DK6_AnimUnitResponse;
  Uni->Render = (VOID *)DK6_AnimUnitRender;
  return (DK6UNIT *)Uni;
} /* End of 'DK6_UnitBallCreate' function */

/* END OF 'UBALL.C' FILE */
