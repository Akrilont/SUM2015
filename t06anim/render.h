/* FILENAME: RENDER.H
 * PROGRAMMER: DK6
 * PURPOSE: Rendering system declaration module.
 * LAST UPDATE: 09.06.2015
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "vec.h"

/* ��� ������������� ������� - ����� ������ � ������������� */
typedef struct tagDK6GOBJ
{
  VEC *V;      /* ������ ������ ������� */
  INT NumOfV;  /* ���������� ������ */
  INT (*F)[3]; /* ������ ������ ������� */
  INT NumOfF;  /* ���������� ������ */
} DK6GOBJ;

/* ������� */
extern MATR
  DK6_RndMatrWorld,
  DK6_RndMatrView,
  DK6_RndMatrProj;

/* ��������� ������������� */
extern DBL
  DK6_RndWp, DK6_RndHp,    /* ������� ������� ������������� */
  DK6_RndProjDist;         /* ���������� �� ��������� �������� */

/* ������� �������������� �� ������� ������� ��������� � ����.
 * ���������:
 *   - �������� �����:
 *       VEC P;
 * ������������ ��������:
 *   (POINT) ���������� � �����.
 */
POINT DK6_RndWorldToScreen( VEC P );

/* ������� �������� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       DK6GOBJ *GObj;
 *   - ��� �����:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, FALSE �����.
 */
BOOL DK6_RndGObjLoad( DK6GOBJ *GObj, CHAR *FileName );

/* ������� ������������ ������ ��-��� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       DK6GOBJ *GObj;
 * ������������ ��������: ���.
 */
VOID DK6_RndGObjFree( DK6GOBJ *GObj );

/* ������� ��������� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       DK6GOBJ *GObj;
 * ������������ ��������: ���.
 */
VOID DK6_RndGObjDraw( DK6GOBJ *GObj );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */