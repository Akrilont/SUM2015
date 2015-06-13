/* FILENAME: UMODEL.C
 * PROGRAMMER: dk6
 * PURPOSE: Model object unit handle module.
 * LAST UPDATE: 10.06.2015
 */

#include <string.h>

#include "anim.h"
#include "vec.h"
#include "render.h"


typedef struct tagdk6UNIT_MODEL
{
  dk6_UNIT_BASE_FIELDS;

  dk6GOBJ Model;  /* 3D objects */
} dk6UNIT_MODEL;


static VOID dk6_ModelUnitInit( dk6UNIT_MODEL *Uni, dk6ANIM *Ani )
{
  dk6_RndGObjLoad(&Uni->Model, "imac.object");
} /* End of 'dk6_AnimUnitInit' function */


static VOID dk6_ModelUnitClose( dk6UNIT_MODEL *Uni, dk6ANIM *Ani )
{
  dk6_RndGObjFree(&Uni->Model);
} /* End of 'dk6_AnimUnitClose' function */


static VOID dk6_ModelUnitResponse( dk6UNIT_MODEL *Uni, dk6ANIM *Ani )
{
  if (Ani->KeysClick['W'] || Ani->JButs[0])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->KeysClick['Q'] || Ani->JButs[2])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);

} /* End of 'dk6_AnimUnitResponse' function */


static VOID dk6_ModelUnitRender( dk6UNIT_MODEL *Uni, dk6ANIM *Ani )
{
  INT i, j;

  dk6_RndMatrView = MatrView(VecSet(8, 8, 8),
                             VecSet(0, 0, 0),
                             VecSet(0, 1, 0));

  for (i = 0; i < 1; i++)
    for (j = 0; j < 1; j++)
    {
      dk6_RndMatrWorld =
        MatrMulMatr(MatrMulMatr(MatrMulMatr(
          MatrTranslate(Ani->JX * 59, Ani->JY * 88, 0),
          MatrScale(3, 3, 3)),
          MatrRotateY(30 * Ani->Time + Ani->JR * 180)),
          MatrTranslate(j * 1.30, 0, i * 1.30 + 100 * Ani->JZ));
      glColor3d(i & 1, j & 1, 1 - ((i & 1) + (j & 1)) / 2);
      dk6_RndGObjDraw(&Uni->Model);
    }
} /* End of 'dk6_AnimUnitRender' function */


dk6UNIT * dk6_UnitModelCreate( VOID )
{
  dk6UNIT_MODEL *Uni;

  if ((Uni = (VOID *)dk6_AnimUnitCreate(sizeof(dk6UNIT_MODEL))) == NULL)
    return NULL;

  Uni->Init = (VOID *)dk6_ModelUnitInit;
  Uni->Close = (VOID *)dk6_ModelUnitClose;
  Uni->Response = (VOID *)dk6_ModelUnitResponse;
  Uni->Render = (VOID *)dk6_ModelUnitRender;
  return (dk6UNIT *)Uni;
} /* End of 'dk6_UnitCowCreate' function */

/* END OF 'UCOW.C' FILE */