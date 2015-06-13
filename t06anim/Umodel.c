/* FILENAME: UMODEL.C
 * PROGRAMMER: DK6
 * PURPOSE: Model object unit handle module.
 * LAST UPDATE: 10.06.2015
 */

#include <string.h>

#include "anim.h"
#include "vec.h"
#include "render.h"

typedef struct tagDK6UNIT_MODEL
{
  DK6_UNIT_BASE_FIELDS;

  DK6GOBJ Model;  /* 3D objects */
} DK6UNIT_MODEL;


static VOID DK6_ModelUnitInit( DK6UNIT_MODEL *Uni, DK6ANIM *Ani )
{
  Ani->PosModel = VecSet(0, 0, 0);
  Ani->AngleX = Ani->AngleY = Ani->AngleZ = 0.0;
  DK6_RndGObjLoad(&Uni->Model, "cow.object");
} /* End of 'DK6_AnimUnitInit' function */


static VOID DK6_ModelUnitClose( DK6UNIT_MODEL *Uni, DK6ANIM *Ani )
{
  DK6_RndGObjFree(&Uni->Model);
} /* End of 'DK6_AnimUnitClose' function */

\
static VOID DK6_ModelUnitResponse( DK6UNIT_MODEL *Uni, DK6ANIM *Ani )
{
  if (Ani->JButs[4])
    Ani->PosModel.X -= 10;
  if (Ani->JButs[5])
    Ani->PosModel.X += 10;
  if (Ani->JButs[6])
    Ani->PosModel.Y += 10;
  if (Ani->JButs[7])
    Ani->PosModel.Y -= 10;
} /* End of 'DK6_AnimUnitResponse' function */

\
static VOID DK6_ModelUnitRender( DK6UNIT_MODEL *Uni, DK6ANIM *Ani )
{
  static DBL MouseShift = 0;

  MouseShift += 30 * DK6_MouseWheel;
  DK6_RndMatrWorld = MatrMulMatr(MatrMulMatr(MatrMulMatr(MatrMulMatr(
    MatrRotateY(50 * Ani->Time), MatrScale(0.060, 0.060, 0.060)),
    MatrTranslate(Ani->JX, -Ani->JY, 0)), MatrRotateX(50 * sin(Ani->Time * 3))), MatrScale(0.10 + sin(Ani->Time * 3), 0.10 + sin(Ani->Time * 3), 0.10 + sin(Ani->Time * 3)));
  DK6_RndMatrView = MatrView(VecSet(8, 8, 8), VecSet(0, 0, 0), VecSet(0, 1, 0));


  SetDCPenColor(Ani->hDC, RGB(rand() % 255, rand() % 255, rand() % 255));
  DK6_RndGObjDraw(&Uni->Model);
} /* End of 'DK6_AnimUnitRender' function */



DK6UNIT * DK6_UnitModelCreate( VOID )
{
  DK6UNIT_MODEL *Uni;

  if ((Uni = (VOID *)DK6_AnimUnitCreate(sizeof(DK6UNIT_MODEL))) == NULL)
    return NULL;

  Uni->Init = (VOID *)DK6_ModelUnitInit;
  Uni->Close = (VOID *)DK6_ModelUnitClose;
  Uni->Response = (VOID *)DK6_ModelUnitResponse;
  Uni->Render = (VOID *)DK6_ModelUnitRender;
  return (DK6UNIT *)Uni;
} /* End of 'DK6_UnitCowCreate' function */

/* END OF 'UCOW.C' FILE */