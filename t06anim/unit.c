/* FILENAME: UNIT.C
 * PROGRAMMER: DK6
 * PURPOSE: Animation unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>

#include "anim.h"

/* Функция по-умолчанию инициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       DK6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       DK6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID DK6_AnimUnitInit( DK6UNIT *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitInit' function */

/* Функция по-умолчанию деинициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       DK6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       DK6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID DK6_AnimUnitClose( DK6UNIT *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitClose' function */

/* Функция по-умолчанию обновления межкадровых параметров объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       DK6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       DK6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID DK6_AnimUnitResponse( DK6UNIT *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitResponse' function */

/* Функция по-умолчанию построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       DK6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       DK6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID DK6_AnimUnitRender( DK6UNIT *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitRender' function */

/* Функция создания объекта анимации.
 * АРГУМЕНТЫ:
 *   - размер структуры объекта анимации:
 *       INT Size;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (DK6UNIT *) указатель на созданный объект анимации.
 */
DK6UNIT * DK6_AnimUnitCreate( INT Size )
{
  DK6UNIT *Uni;

  if (Size < sizeof(DK6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* заполняем поля по-умолчанию */
  Uni->Size = Size;
  Uni->Init = DK6_AnimUnitInit;
  Uni->Close = DK6_AnimUnitClose;
  Uni->Response = DK6_AnimUnitResponse;
  Uni->Render = DK6_AnimUnitRender;
  return Uni;
} /* End of 'DK6_AnimUnitCreate' function */

/* END OF 'UNIT.C' FILE */