/* FILENAME: UNIT.C
 * PROGRAMMER: dk6
 * PURPOSE: Animation unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>

#include "anim.h"

/* ������� ��-��������� ������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       dk6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       dk6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID dk6_AnimUnitInit( dk6UNIT *Uni, dk6ANIM *Ani )
{
} /* End of 'dk6_AnimUnitInit' function */

/* ������� ��-��������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       dk6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       dk6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID dk6_AnimUnitClose( dk6UNIT *Uni, dk6ANIM *Ani )
{
} /* End of 'dk6_AnimUnitClose' function */

/* ������� ��-��������� ���������� ����������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       dk6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       dk6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID dk6_AnimUnitResponse( dk6UNIT *Uni, dk6ANIM *Ani )
{
} /* End of 'dk6_AnimUnitResponse' function */

/* ������� ��-��������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       dk6UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       dk6ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID dk6_AnimUnitRender( dk6UNIT *Uni, dk6ANIM *Ani )
{
} /* End of 'dk6_AnimUnitRender' function */

/* ������� �������� ������� ��������.
 * ���������:
 *   - ������ ��������� ������� ��������:
 *       INT Size;
 * ������������ ��������:
 *   (dk6UNIT *) ��������� �� ��������� ������ ��������.
 */
dk6UNIT * dk6_AnimUnitCreate( INT Size )
{
  dk6UNIT *Uni;

  if (Size < sizeof(dk6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* ��������� ���� ��-��������� */
  Uni->Size = Size;
  Uni->Init = dk6_AnimUnitInit;
  Uni->Close = dk6_AnimUnitClose;
  Uni->Response = dk6_AnimUnitResponse;
  Uni->Render = dk6_AnimUnitRender;
  return Uni;
} /* End of 'dk6_AnimUnitCreate' function */

/* END OF 'UNIT.C' FILE */