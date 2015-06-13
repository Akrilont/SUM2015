/* FILENAME: ANIM.H
 * PROGRAMMER: DK6
 * PURPOSE: Animation system declaration module.
 * LAST UPDATE: 08.06.2015
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.h"
#include "vec.h"

/* ������������ ���������� ��������� �������� */
#define DK6_MAX_UNITS 3000

/* ���������� ���� �������� �������� "������" */
typedef struct tagDK6UNIT DK6UNIT;

/* ��������� �������� ��������� �������� */
typedef struct
{
  HWND hWnd;          /* ���� ������ */
  INT W, H;           /* ������ ���� ������ */
  HBITMAP hBmFrame;   /* ����� ����� */
  HDC hDC;            /* �������� ������ */

  /* ������ ��������� �������� � �� ���������� */
  DK6UNIT *Units[DK6_MAX_UNITS]; 
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
} DK6ANIM;

/* ���������� ���������� - ������� ��������� ������ ���� */
extern INT DK6_MouseWheel;

/* ��������� �������� �������� */
extern DK6ANIM DK6_Anim;

/* ������� ���� ������� ��������:
 * - ������ ��������� ��� ������������
 *     INT Size;
 * - ������������� ��������:
 *     INT Id;
 * - ��������� �� ������� �������������
 *     VOID (*Init)( DK6UNIT *Unit, DK6ANIM *Ani );
 * - ��������� �� ������� ���������������
 *     VOID (*Close)( DK6UNIT *Unit, DK6ANIM *Ani );
 * - ��������� �� ������� ���������� ����������� ����������
 *     VOID (*Response)( DK6UNIT *Unit, DK6ANIM *Ani );
 * - ��������� �� ������� ����������
 *     VOID (*Render)( DK6UNIT *Unit, DK6ANIM *Ani );
 */
#define DK6_UNIT_BASE_FIELDS \
  INT Size;                                          \
  VOID (*Init)( DK6UNIT *Unit, DK6ANIM *Ani );       \
  VOID (*Close)( DK6UNIT *Unit, DK6ANIM *Ani );      \
  VOID (*Response)( DK6UNIT *Unit, DK6ANIM *Ani );   \
  VOID (*Render)( DK6UNIT *Unit, DK6ANIM *Ani )

/* ������� ��� ������� �������� */
struct tagDK6UNIT
{
  DK6_UNIT_BASE_FIELDS;
};

/* ������� ������������� ��������.
 * ���������:
 *   - ���������� ����:
 *       HWND hWnd;
 * ������������ ��������: ���.
 */
VOID DK6_AnimInit( HWND hWnd );

/* ������� ��������������� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID DK6_AnimClose( VOID );

/* ������� ��������� ��������� ������� ������� ������.
 * ���������:
 *   - ����� ������ ������� ������:
 *       INT W, H;
 * ������������ ��������: ���.
 */
VOID DK6_AnimResize( INT W, INT H );

/* ������� ���������� ����� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID DK6_AnimRender( VOID );

/* ������� ������ ����� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID DK6_AnimCopyFrame( VOID );

/* ������� ���������� � ������� ������� ��������.
 * ���������:
 *   - ����������� ������ ��������:
 *       DK6UNIT *Unit;
 * ������������ ��������: ���.
 */
VOID DK6_AnimAddUnit( DK6UNIT *Unit );

/* ������� ������������ �/�� �������������� ������
 * � ������ ���������� ���������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID DK6_AnimFlipFullScreen( VOID );

/* ������� �������� ������� ��������.
 * ���������:
 *   - ������ ��������� ������� ��������:
 *       INT Size;
 * ������������ ��������:
 *   (DK6UNIT *) ��������� �� ��������� ������ ��������.
 */
DK6UNIT * DK6_AnimUnitCreate( INT Size );

/* ������� ������ �� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID DK6_AnimDoExit( VOID );

/* ������� ��������� ����� ��������.
 * ���������:
 *   - ���� �����:
 *       BOOL NewPauseFlag;
 * ������������ ��������: ���.
 */
VOID DK6_AnimSetPause( BOOL NewPauseFlag );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */