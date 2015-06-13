/* FILENAME: UCONTRL.C
 * PROGRAMMER: DK6
 * PURPOSE: Control unit handle module.
 * LAST UPDATE: 08.06.2015
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "anim.h"
#include "vec.h"


typedef struct tagDK6UNIT_CTRL
{
  DK6_UNIT_BASE_FIELDS;
  HFONT hFnt; 
} DK6UNIT_CTRL;


static VOID DK6_AnimUnitInit( DK6UNIT_CTRL *Uni, DK6ANIM *Ani )
{
  Uni->hFnt = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE,
    FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH, "Bookman Old Style");
} 

static VOID DK6_AnimUnitClose( DK6UNIT_CTRL *Uni, DK6ANIM *Ani )
{
  DeleteObject(Uni->hFnt);
} /* End of 'DK6_AnimUnitClose' function */


static VOID DK6_AnimUnitResponse( DK6UNIT_CTRL *Uni, DK6ANIM *Ani )
{
  if (Ani->KeysClick[VK_ESCAPE])
    DK6_AnimDoExit();
  if (Ani->KeysClick['F'])
    DK6_AnimFlipFullScreen();
  if (Ani->KeysClick['P'])
    DK6_AnimSetPause(!Ani->IsPause);

  /* Controling by JoyStick */
  if (Ani->JButs[9])
    DK6_AnimFlipFullScreen();
  if (Ani->JButs[8])
    DK6_AnimSetPause(!Ani->IsPause);
/*  if (Ani->JButsClick[6])
    DK6_AnimDoExit();*/
} /* End of 'DK6_AnimUnitResponse' function */



static VOID DK6_AnimUnitRender( DK6UNIT_CTRL *Uni, DK6ANIM *Ani )
{
  HFONT hFntOld = SelectObject(Ani->hDC, Uni->hFnt);
  RECT rc;
  static CHAR Buf[1000];

  SetTextColor(Ani->hDC, RGB(255, 255, 255));
  SetBkMode(Ani->hDC, TRANSPARENT);

  rc.left = 8;
  rc.top = 5;
  rc.right = Ani->W;
  rc.bottom = Ani->H;
  DrawText(Ani->hDC, Buf,
    sprintf(Buf,
      "JoyStick parametrs:\n"
      "Buttons: %i %i %i %i\n"
      "POV:%i\n"
      "%.5f %.5f %.5f %.5f",
      Ani->JButs[0], Ani->JButs[1], Ani->JButs[2], Ani->JButs[3], Ani->JPOV,
      Ani->JX, Ani->JY, Ani->JZ, Ani->JR),
    &rc,
    DT_TOP | DT_LEFT);

  SelectObject(Ani->hDC, hFntOld);
} /* End of 'VG4_AnimUnitRender' function */



DK6UNIT * DK6_UnitControlCreate( VOID )
{
  DK6UNIT_CTRL *Uni;

  if ((Uni = (VOID *)DK6_AnimUnitCreate(sizeof(DK6UNIT_CTRL))) == NULL)
    return NULL;

  Uni->Init = (VOID *)DK6_AnimUnitInit;
  Uni->Close = (VOID *)DK6_AnimUnitClose;
  Uni->Response = (VOID *)DK6_AnimUnitResponse;
  Uni->Render = (VOID *)DK6_AnimUnitRender;
  return (DK6UNIT *)Uni;
} /* End of 'DK6_UnitBallCreate' function */

/* END OF 'UCONTRL.C' FILE */