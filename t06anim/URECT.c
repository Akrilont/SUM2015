/* FILENAME: URECT.C
 * PROGRAMMER: DK6
 * PURPOSE: Bounce rectangle unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>
#include <time.h>

#include "anim.h"
#include "vec.h"


typedef struct tagDK6UNIT_RECT
{
  DK6_UNIT_BASE_FIELDS;

  VEC Pos;     
  DWORD Color; 
  DBL
    PhaseShift; 
} DK6UNIT_RECT;



static VOID DK6_RectUnitInit( DK6UNIT_RECT *Uni, DK6ANIM *Ani )
{
  DBL t = clock() / (DOUBLE)CLOCKS_PER_SEC;

  Uni->Pos = VecSet(rand() % 1920, rand() % 1080, 0);
  Uni->Color = RGB(rand() % 256, rand() % 256, rand() % 256);
  Uni->PhaseShift = t * 30 * 59;
} /* End of 'DK6_AnimUnitInit' function */


static VOID DK6_RectUnitClose( DK6UNIT_RECT *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitClose' function */


static VOID DK6_RectUnitResponse( DK6UNIT_RECT *Uni, DK6ANIM *Ani )
{
} /* End of 'DK6_AnimUnitResponse' function */



static VOID DK6_RectUnitRender( DK6UNIT_RECT *Uni, DK6ANIM *Ani )
{
  DBL shift = fabs(sin(Uni->PhaseShift + (DBL)clock() / CLOCKS_PER_SEC * 3)) * 30;

  SetDCBrushColor(Ani->hDC, Uni->Color);
  Rectangle(Ani->hDC, Uni->Pos.X - 5 - shift, Uni->Pos.Y - 5, Uni->Pos.X + 5, Uni->Pos.Y + 5 - shift);
} /* End of 'DK6_AnimUnitRender' function */


DK6UNIT * DK6_UnitRectCreate( VOID )
{
  DK6UNIT_RECT *Uni;

  if ((Uni = (VOID *)DK6_AnimUnitCreate(sizeof(DK6UNIT_RECT))) == NULL)
    return NULL;

  Uni->Init = (VOID *)DK6_RectUnitInit;
  Uni->Close = (VOID *)DK6_RectUnitClose;
  Uni->Response = (VOID *)DK6_RectUnitResponse;
  Uni->Render = (VOID *)DK6_RectUnitRender;
  return (DK6UNIT *)Uni;
} /* End of 'DK6_UnitRectCreate' function */

/* END OF 'URECT.C' FILE */