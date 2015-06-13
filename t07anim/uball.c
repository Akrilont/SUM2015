/* FILENAME: UBALL.C
 * PROGRAMMER: dk6
 * PURPOSE: Bounce ball unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <string.h>
#include <time.h>

#include "anim.h"
#include "vec.h"


typedef struct tagdk6UNIT_BALL
{
  dk6_UNIT_BASE_FIELDS;

  VEC Pos;
  DWORD Color;
  DBL
    Amplitude,
    PhaseShift,
    ScaleShift;
} dk6UNIT_BALL;


static VOID dk6_AnimUnitInit( dk6UNIT_BALL *Uni, dk6ANIM *Ani )
{
  Uni->Pos = VecSet(rand() % 1920, rand() % 1080, 0);
  Uni->Color = RGB(rand() % 256, rand() % 256, rand() % 256);
  Uni->PhaseShift = rand() % 3000;
  Uni->ScaleShift = 5 + 0.30 * rand() / RAND_MAX;
  Uni->Amplitude = 30 + 59.0 * rand() / RAND_MAX;
} /* End of 'dk6_AnimUnitInit' function */


static VOID dk6_AnimUnitClose( dk6UNIT_BALL *Uni, dk6ANIM *Ani )
{
} /* End of 'dk6_AnimUnitClose' function */


static VOID dk6_AnimUnitResponse( dk6UNIT_BALL *Uni, dk6ANIM *Ani )
{
  if (Ani->JButs[3])
    //Uni->Amplitude += 30 * Ani->MsWheel;
    Uni->Amplitude += 5;
  if (Ani->JButs[1])
    Uni->Amplitude -= 5;

} /* End of 'dk6_AnimUnitResponse' function */


static VOID dk6_AnimUnitRender( dk6UNIT_BALL *Uni, dk6ANIM *Ani )
{
  DBL shift = Uni->Amplitude * fabs(sin(Uni->ScaleShift * Ani->Time + Uni->PhaseShift));

  SetDCBrushColor(Ani->hDC, Uni->Color);
  Ellipse(Ani->hDC, Uni->Pos.X - 5, Uni->Pos.Y - 5 - shift, Uni->Pos.X + 5, Uni->Pos.Y + 5 - shift);
} /* End of 'dk6_AnimUnitRender' function */


dk6UNIT * dk6_UnitBallCreate( VOID )
{
  dk6UNIT_BALL *Uni;

  if ((Uni = (VOID *)dk6_AnimUnitCreate(sizeof(dk6UNIT_BALL))) == NULL)
    return NULL;

  Uni->Init = (VOID *)dk6_AnimUnitInit;
  Uni->Close = (VOID *)dk6_AnimUnitClose;
  Uni->Response = (VOID *)dk6_AnimUnitResponse;
  Uni->Render = (VOID *)dk6_AnimUnitRender;
  return (dk6UNIT *)Uni;
} /* End of 'dk6_UnitBallCreate' function */

/* END OF 'UBALL.C' FILE */