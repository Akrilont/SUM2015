/* FILENAME: ANIM.H
 * PROGRAMMER: dk6
 * PURPOSE: Animation system declaration module.
 * LAST UPDATE: 08.06.2015
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.h"
#include "vec.h"

/* ������������ ���������� ��������� �������� */
#define dk6_MAX_UNITS 3000

/* ���������� ���� �������� �������� "������" */
typedef struct tagdk6UNIT dk6UNIT;

/* ��������� �������� ��������� �������� */
typedef struct
{
  HWND hWnd;          /* ���� ������ */
  INT W, H;           /* ������ ���� ������ */
  HDC hDC;            /* �������� ������ ���� */
  HGLRC hGLRC;        /* �������� ���������� */

  /* ������ ��������� �������� � �� ���������� */
  dk6UNIT *Units[dk6_MAX_UNITS]; 
  INT NumOfUnits;

  /* ���������� ������������� */
  DBL
    Time,            /* ����� � �������� �� ������ �������� */
    GlobalTime,      /* ����� -"-, �� ��� ����� */
    DeltaTime,       /* ����������� ����� � �������� */
    GlobalDeltaTime, /* ����������� ����� � �������� ��� ����� */
    FPS;             /* ���������� ������ � ������� */
  BOOL
    IsPause;         /* ���� ����� */

  /* ���������� ����� */
  BYTE
    Keys[256],       /* �������� ������ ���������� � ���� */
    KeysOld[256],    /* �������� ������ �� ���������� ����� */
    KeysClick[256];  /* ����� ������������ ������� */
  INT
    MsDeltaX, MsDeltaY, /* ������������� ���������� ������� ���� */
    MsX, MsY,        /* ���������� ���������� ������� ���� */
    MsWheel;         /* ��������� ������ ���� */
  BYTE
    JButs[32],       /* �������� ������ ��������� */
    JButsOld[32],    /* �������� ������ ��������� �� ���������� ����� */
    JButsClick[32],  /* ����� ������������ ������� ������ ��������� */
    JPOV;            /* ������������� POV - 0..8 */
  DBL
    JX, JY, JZ, JR, JU, JV; /* ��� ��������� (-1.0 .. 1.0*/

  VEC PosModel;
  DBL AngleX, AngleY, AngleZ;
} dk6ANIM;

/* ���������� ���������� - ������� ��������� ������ ���� */
extern INT dk6_MouseWheel;

/* ��������� �������� �������� */
extern dk6ANIM dk6_Anim;

/* ������� ���� ������� ��������:
 * - ������ ��������� ��� ������������
 *     INT Size;
 * - ������������� ��������:
 *     INT Id;
 * - ��������� �� ������� �������������
 *     VOID (*Init)( dk6UNIT *Unit, dk6ANIM *Ani );
 * - ��������� �� ������� ���������������
 *     VOID (*Close)( dk6UNIT *Unit, dk6ANIM *Ani );
 * - ��������� �� ������� ���������� ����������� ����������
 *     VOID (*Response)( dk6UNIT *Unit, dk6ANIM *Ani );
 * - ��������� �� ������� ����������
 *     VOID (*Render)( dk6UNIT *Unit, dk6ANIM *Ani );
 */
#define dk6_UNIT_BASE_FIELDS \
  INT Size;                                          \
  VOID (*Init)( dk6UNIT *Unit, dk6ANIM *Ani );       \
  VOID (*Close)( dk6UNIT *Unit, dk6ANIM *Ani );      \
  VOID (*Response)( dk6UNIT *Unit, dk6ANIM *Ani );   \
  VOID (*Render)( dk6UNIT *Unit, dk6ANIM *Ani )

/* ������� ��� ������� �������� */
struct tagdk6UNIT
{
  dk6_UNIT_BASE_FIELDS;
};

/* ������� ������������� ��������.
 * ���������:
 *   - ���������� ����:
 *       HWND hWnd;
 * ������������ ��������: ���.
 */
BOOL dk6_AnimInit( HWND hWnd );

/* ������� ��������������� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID dk6_AnimClose( VOID );

/* ������� ��������� ��������� ������� ������� ������.
 * ���������:
 *   - ����� ������ ������� ������:
 *       INT W, H;
 * ������������ ��������: ���.
 */
VOID dk6_AnimResize( INT W, INT H );

/* ������� ���������� ����� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID dk6_AnimRender( VOID );

/* ������� ������ ����� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID dk6_AnimCopyFrame( VOID );

/* ������� ���������� � ������� ������� ��������.
 * ���������:
 *   - ����������� ������ ��������:
 *       dk6UNIT *Unit;
 * ������������ ��������: ���.
 */
VOID dk6_AnimAddUnit( dk6UNIT *Unit );

/* ������� ������������ �/�� �������������� ������
 * � ������ ���������� ���������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID dk6_AnimFlipFullScreen( VOID );

/* ������� �������� ������� ��������.
 * ���������:
 *   - ������ ��������� ������� ��������:
 *       INT Size;
 * ������������ ��������:
 *   (dk6UNIT *) ��������� �� ��������� ������ ��������.
 */
dk6UNIT * dk6_AnimUnitCreate( INT Size );

/* ������� ������ �� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID dk6_AnimDoExit( VOID );

/* ������� ��������� ����� ��������.
 * ���������:
 *   - ���� �����:
 *       BOOL NewPauseFlag;
 * ������������ ��������: ���.
 */
VOID dk6_AnimSetPause( BOOL NewPauseFlag );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */