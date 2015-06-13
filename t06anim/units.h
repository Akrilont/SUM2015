/* FILENAME: UNITS.H
 * PROGRAMMER: DK6
 * PURPOSE: Animation units samples declaration module.
 * LAST UPDATE: 08.06.2015
 */

#ifndef __UNITS_H_
#define __UNITS_H_

#include "def.h"


/* ������� �������� ������� �������� "���".
 * ���������: ���.
 * ������������ ��������:
 *   (DK6UNIT *) ��������� �� ��������� ������ ��������.
 */
DK6UNIT * DK6_UnitBallCreate( VOID );

/* ������� �������� ������� �������� "������".
 * ���������: ���.
 * ������������ ��������:
 *   (DK6UNIT *) ��������� �� ��������� ������ ��������.
 */
DK6UNIT * DK6_UnitModelCreate( VOID );

/* ������� �������� ������� �������� "�������".
 * ���������: ���.
 * ������������ ��������:
 *   (DK6UNIT *) ��������� �� ��������� ������ ��������.
 */
DK6UNIT * DK6_UnitRectCreate( VOID );

/* ������� �������� ������� �������� "����������".
 * ���������: ���.
 * ������������ ��������:
 *   (DK6UNIT *) ��������� �� ��������� ������ ��������.
 */
DK6UNIT * DK6_UnitControlCreate( VOID );

/* ������� �������� ������� �������� "������".
 * ���������: ���.
 * ������������ ��������:
 *   (DK6UNIT *) ��������� �� ��������� ������ ��������.
 */
DK6UNIT * DK6_UnitCameraCreate( VOID );


#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */