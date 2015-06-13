/* FILENAME: RENDER.H
 * PROGRAMMER: dk6
 * PURPOSE: Rendering system declaration module.
 * LAST UPDATE: 09.06.2015
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "vec.h"

#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

/* ��� ������������� ������� - ����� ������ � ������������� */
typedef struct tagdk6GOBJ
{
  INT
    VA,          /* ������ ������ */
    VBuf, IBuf,  /* ������ ������ � �������� */
    NumOfV,      /* ���������� ������ */
    NumOfF;      /* ���������� ������ */
} dk6GOBJ;

/* ������� */
extern MATR
  dk6_RndMatrWorld,
  dk6_RndMatrView,
  dk6_RndMatrProj;

/* ��������� ������������� */
extern DBL
  dk6_RndWp, dk6_RndHp,    /* ������� ������� ������������� */
  dk6_RndProjDist;         /* ���������� �� ��������� �������� */


/* ������ �� ��������� */
extern UINT dk6_RndProg;

/* ������� �������������� �� ������� ������� ��������� � ����.
 * ���������:
 *   - �������� �����:
 *       VEC P;
 * ������������ ��������:
 *   (POINT) ���������� � �����.
 */
POINT dk6_RndWorldToScreen( VEC P );

/* ������� �������� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       dk6GOBJ *GObj;
 *   - ��� �����:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, FALSE �����.
 */
BOOL dk6_RndGObjLoad( dk6GOBJ *GObj, CHAR *FileName );

/* ������� ������������ ������ ��-��� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       dk6GOBJ *GObj;
 * ������������ ��������: ���.
 */
VOID dk6_RndGObjFree( dk6GOBJ *GObj );

/* ������� ��������� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       dk6GOBJ *GObj;
 * ������������ ��������: ���.
 */
VOID dk6_RndGObjDraw( dk6GOBJ *GObj );

static VOID dk6_SaveLog( CHAR *Text );


static CHAR * dk6_TextLoad( CHAR *FileName );


UINT dk6_ShaderLoad( CHAR *FileNamePrefix );


VOID dk6_ShaderFree( UINT PrgId );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */