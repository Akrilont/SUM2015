/* FILENAME: UCONTRL.C
 * PROGRAMMER: dk6
 * PURPOSE: Control unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "anim.h"
#include "vec.h"


typedef struct tagdk6UNIT_CTRL
{
  dk6_UNIT_BASE_FIELDS;
  HFONT hFnt;
} dk6UNIT_CTRL;


static VOID dk6_AnimUnitInit( dk6UNIT_CTRL *Uni, dk6ANIM *Ani )
{
  Uni->hFnt = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE,
    FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH, "Bookman Old Style");
} /* End of 'dk6_AnimUnitInit' function */


static VOID dk6_AnimUnitClose( dk6UNIT_CTRL *Uni, dk6ANIM *Ani )
{
  DeleteObject(Uni->hFnt);
} /* End of 'dk6_AnimUnitClose' function */


static VOID dk6_AnimUnitResponse( dk6UNIT_CTRL *Uni, dk6ANIM *Ani )
{
  if (Ani->KeysClick[VK_ESCAPE] || Ani->JButsClick[6])
    dk6_AnimDoExit();
  if (Ani->KeysClick['F'])
    dk6_AnimFlipFullScreen();
  if (Ani->KeysClick['P'])
    dk6_AnimSetPause(!Ani->IsPause);

  /* Controling by JoyStick */
  if (Ani->JButs[9])
    dk6_AnimFlipFullScreen();
  if (Ani->JButs[8])
    dk6_AnimSetPause(!Ani->IsPause);
/*  if (Ani->JButsClick[6])
    dk6_AnimDoExit();*/
} /* End of 'dk6_AnimUnitResponse' function */


static VOID dk6_AnimUnitRender( dk6UNIT_CTRL *Uni, dk6ANIM *Ani )
{
} /* End of 'dk6_AnimUnitRender' function */


dk6UNIT * dk6_UnitControlCreate( VOID )
{
  dk6UNIT_CTRL *Uni;

  if ((Uni = (VOID *)dk6_AnimUnitCreate(sizeof(dk6UNIT_CTRL))) == NULL)
    return NULL;

  Uni->Init = (VOID *)dk6_AnimUnitInit;
  Uni->Close = (VOID *)dk6_AnimUnitClose;
  Uni->Response = (VOID *)dk6_AnimUnitResponse;
  Uni->Render = (VOID *)dk6_AnimUnitRender;
  return (dk6UNIT *)Uni;
} /* End of 'dk6_UnitBallCreate' function */

/* END OF 'UCONTRL.C' FILE */