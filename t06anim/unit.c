/* FILENAME: UNIT.C
 * PROGRAMMER: DK6
 * PURPOSE: Animation unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>

#include "anim.h"

/* ������� ��-��������� ������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       DK6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       DK6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID DK6_AnimUnitInit( DK6UNIT *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitInit' function */

/* ������� ��-��������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       DK6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       DK6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID DK6_AnimUnitClose( DK6UNIT *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitClose' function */

/* ������� ��-��������� ���������� ����������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       DK6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       DK6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID DK6_AnimUnitResponse( DK6UNIT *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitResponse' function */

/* ������� ��-��������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       DK6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       DK6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID DK6_AnimUnitRender( DK6UNIT *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitRender' function */

/* ������� �������� ������� ��������.
 * ���������:
 *   - ������ ��������� ������� ��������:
 *       INT Size;
 * ������������ ��������:
 *   (DK6UNIT *) ��������� �� ��������� ������ ��������.
 */
DK6UNIT * DK6_AnimUnitCreate( INT Size )
{
  DK6UNIT *Uni;

  if (Size < sizeof(DK6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* ��������� ���� ��-��������� */
  Uni->Size = Size;
  Uni->Init = DK6_AnimUnitInit;
  Uni->Close = DK6_AnimUnitClose;
  Uni->Response = DK6_AnimUnitResponse;
  Uni->Render = DK6_AnimUnitRender;
  return Uni;
} /* End of 'DK6_AnimUnitCreate' function */

/* END OF 'UNIT.C' FILE */