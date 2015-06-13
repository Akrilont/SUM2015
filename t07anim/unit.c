/* FILENAME: UNIT.C
 * PROGRAMMER: dk6
 * PURPOSE: Animation unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>

#include "anim.h"

/* Функция по-умолчанию инициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       dk6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       dk6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID dk6_AnimUnitInit( dk6UNIT *Uni, dk6ANIM *Ani )
{
} /* End of 'dk6_AnimUnitInit' function */

/* Функция по-умолчанию деинициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       dk6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       dk6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID dk6_AnimUnitClose( dk6UNIT *Uni, dk6ANIM *Ani )
{
} /* End of 'dk6_AnimUnitClose' function */

/* Функция по-умолчанию обновления межкадровых параметров объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       dk6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       dk6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID dk6_AnimUnitResponse( dk6UNIT *Uni, dk6ANIM *Ani )
{
} /* End of 'dk6_AnimUnitResponse' function */

/* Функция по-умолчанию построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       dk6UNIT *Uni;
 *   - указатель на контекст анимации:
 *       dk6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID dk6_AnimUnitRender( dk6UNIT *Uni, dk6ANIM *Ani )
{
} /* End of 'dk6_AnimUnitRender' function */

/* Функция создания объекта анимации.
 * АРГУМЕНТЫ:
 *   - размер структуры объекта анимации:
 *       INT Size;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (dk6UNIT *) указатель на созданный объект анимации.
 */
dk6UNIT * dk6_AnimUnitCreate( INT Size )
{
  dk6UNIT *Uni;

  if (Size < sizeof(dk6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* заполняем поля по-умолчанию */
  Uni->Size = Size;
  Uni->Init = dk6_AnimUnitInit;
  Uni->Close = dk6_AnimUnitClose;
  Uni->Response = dk6_AnimUnitResponse;
  Uni->Render = dk6_AnimUnitRender;
  return Uni;
} /* End of 'dk6_AnimUnitCreate' function */

/* END OF 'UNIT.C' FILE */