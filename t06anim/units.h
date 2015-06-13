/* FILENAME: UNITS.H
 * PROGRAMMER: DK6
 * PURPOSE: Animation units samples declaration module.
 * LAST UPDATE: 08.06.2015
 */

#ifndef __UNITS_H_
#define __UNITS_H_

#include "def.h"


/* Функция создания объекта анимации "мяч".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (DK6UNIT *) указатель на созданный объект анимации.
 */
DK6UNIT * DK6_UnitBallCreate( VOID );

/* Функция создания объекта анимации "корова".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (DK6UNIT *) указатель на созданный объект анимации.
 */
DK6UNIT * DK6_UnitModelCreate( VOID );

/* Функция создания объекта анимации "квадрат".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (DK6UNIT *) указатель на созданный объект анимации.
 */
DK6UNIT * DK6_UnitRectCreate( VOID );

/* Функция создания объекта анимации "управление".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (DK6UNIT *) указатель на созданный объект анимации.
 */
DK6UNIT * DK6_UnitControlCreate( VOID );

/* Функция создания объекта анимации "камера".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (DK6UNIT *) указатель на созданный объект анимации.
 */
DK6UNIT * DK6_UnitCameraCreate( VOID );


#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */