/* FILENAME: UBALL.C
 * PROGRAMMER: DK6
 * PURPOSE: Bounce ball unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>
#include <time.h>

#include "anim.h"
#include "vec.h"

/* ��� ������������� ���� */
typedef struct tagDK6UNIT_BALL
{
  DK6_UNIT_BASE_FIELDS;

  VEC Pos;     /* ������� ���� */
  DWORD Color; /* ���� ���� */
  DBL
    Amplitude,  /* ��������� */
    PhaseShift, /* ����� �� ���� */
    ScaleShift; /* ������� ������� */
} DK6UNIT_BALL;

/* ������� ������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       DK6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       DK6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID DK6_AnimUnitInit( DK6UNIT_BALL *Uni, DK6ANIM *Ani )
{
  Uni->Pos = VecSet(rand() % 1000, rand() % 700, 0);
  Uni->Color = RGB(rand() % 256, rand() % 256, rand() % 256);
  Uni->PhaseShift = rand() % 3000;
  Uni->ScaleShift = 5 + 0.30 * rand() / RAND_MAX;
  Uni->Amplitude = 30 + 59.0 * rand() / RAND_MAX;
} /* End of 'DK6_AnimUnitInit' function */

/* ������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       DK6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       DK6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID DK6_AnimUnitClose( DK6UNIT_BALL *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitClose' function */

/* ������� ���������� ����������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       DK6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       DK6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID DK6_AnimUnitResponse( DK6UNIT_BALL *Uni, DK6ANIM *Ani )
{
  if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    DK6_AnimDoExit();
  if (GetAsyncKeyState('F') & 0x8000)
    DK6_AnimFlipFullScreen();
} /* End of 'DK6_AnimUnitResponse' function */

/* ������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       DK6UNIT_BALL *Uni;
 *   - ��������� �� �������� ��������:
 *       DK6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID DK6_AnimUnitRender( DK6UNIT_BALL *Uni, DK6ANIM *Ani )
{
  DBL shift = Uni->Amplitude * fabs(sin(Uni->ScaleShift * (DBL)clock() / CLOCKS_PER_SEC + Uni->PhaseShift));

  SetDCBrushColor(Ani->hDC, Uni->Color);
  Ellipse(Ani->hDC, Uni->Pos.X - 5, Uni->Pos.Y - 5 - shift, Uni->Pos.X + 5, Uni->Pos.Y + 5 - shift);
} /* End of 'DK6_AnimUnitRender' function */

/* ������� �������� ������� �������� "���".
 * ���������: ���.
 * ������������ ��������:
 *   (DK6UNIT *) ��������� �� ��������� ������ ��������.
 */
DK6UNIT * DK6_UnitBallCreate( VOID )
{
  DK6UNIT_BALL *Uni;

  if ((Uni = (VOID *)DK6_AnimUnitCreate(sizeof(DK6UNIT_BALL))) == NULL)
    return NULL;
  /* ��������� ���� */
  Uni->Init = (VOID *)DK6_AnimUnitInit;
  Uni->Close = (VOID *)DK6_AnimUnitClose;
  Uni->Response = (VOID *)DK6_AnimUnitResponse;
  Uni->Render = (VOID *)DK6_AnimUnitRender;
  return (DK6UNIT *)Uni;
} /* End of 'DK6_UnitBallCreate' function */

/* END OF 'UBALL.C' FILE */
