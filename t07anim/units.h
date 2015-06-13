/* FILENAME: UNITS.H
 * PROGRAMMER: dk6
 * PURPOSE: Animation units samples declaration module.
 * LAST UPDATE: 08.06.2015
 */

#ifndef __UNITS_H_
#define __UNITS_H_

#include "def.h"


/* ������� �������� ������� �������� "���".
 * ���������: ���.
 * ������������ ��������:
 *   (dk6UNIT *) ��������� �� ��������� ������ ��������.
 */
dk6UNIT * dk6_UnitBallCreate( VOID );

/* ������� �������� ������� �������� "������".
 * ���������: ���.
 * ������������ ��������:
 *   (dk6UNIT *) ��������� �� ��������� ������ ��������.
 */
dk6UNIT * dk6_UnitModelCreate( VOID );

/* ������� �������� ������� �������� "�������".
 * ���������: ���.
 * ������������ ��������:
 *   (dk6UNIT *) ��������� �� ��������� ������ ��������.
 */
dk6UNIT * dk6_UnitRectCreate( VOID );

/* ������� �������� ������� �������� "����������".
 * ���������: ���.
 * ������������ ��������:
 *   (dk6UNIT *) ��������� �� ��������� ������ ��������.
 */
dk6UNIT * dk6_UnitControlCreate( VOID );

/* ������� �������� ������� �������� "������".
 * ���������: ���.
 * ������������ ��������:
 *   (dk6UNIT *) ��������� �� ��������� ������ ��������.
 */
dk6UNIT * dk6_UnitCameraCreate( VOID );


#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */