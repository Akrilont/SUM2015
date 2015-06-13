/* FILENAME: RENDER.C
 * PROGRAMMER: DK6
 * PURPOSE: Rendering system module.
 * LAST UPDATE: 09.06.2015
 */

#include <stdio.h>
#include <string.h>

#include "anim.h"
#include "render.h"


MATR
  DK6_RndMatrWorld = DK6_UNIT_MATR,
  DK6_RndMatrView = DK6_UNIT_MATR,
  DK6_RndMatrProj = DK6_UNIT_MATR,
  DK6_RndMatrWorldViewProj = DK6_UNIT_MATR;


DBL
  DK6_RndWp = 3, DK6_RndHp = 3,     
  DK6_RndProjDist = 5;



POINT DK6_RndWorldToScreen( VEC P )
{
  POINT Ps;

 
  P = PointTransform(P, DK6_RndMatrWorldViewProj);

  Ps.x = (P.X / 2 + 0.5) * DK6_Anim.W + DK6_Anim.PosModel.X;
  Ps.y = (-P.Y / 2 + 0.5) * DK6_Anim.H + DK6_Anim.PosModel.Y;

  return Ps;
} /* End of 'DK6_RndWorldToScreen' function */




BOOL DK6_RndGObjLoad( DK6GOBJ *GObj, CHAR *FileName )
{
  FILE *F;
  INT nv = 0, nf = 0;
  static CHAR Buf[10000];

  memset(GObj, 0, sizeof(DK6GOBJ));
  /* Open file */
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertices */
  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      nf++;
  }

  /* Allocate memory for data */
  if ((GObj->V = malloc(sizeof(VEC) * nv + sizeof(INT [3]) * nf)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  GObj->F = (INT (*)[3])(GObj->V + nv);

  /* Read vertices */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      sscanf(Buf + 2, "%lf%lf%lf",
        &GObj->V[nv].X, &GObj->V[nv].Y, &GObj->V[nv].Z);
      nv++;
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT a, b, c;

      sscanf(Buf + 2, "%i/%*i/%*i %i/%*i/%*i %i/%*i/%*i", &a, &b, &c) == 3 ||
        sscanf(Buf + 2, "%i//%*i %i//%*i %i//%*i", &a, &b, &c) == 3 ||
        sscanf(Buf + 2, "%i/%*i %i/%*i %i/%*i", &a, &b, &c) == 3 ||
        sscanf(Buf + 2, "%i %i %i", &a, &b, &c);

      GObj->F[nf][0] = a - 1;
      GObj->F[nf][1] = b - 1;
      GObj->F[nf][2] = c - 1;
      nf++;
    }
  }

  fclose(F);

  GObj->NumOfV = nv;
  GObj->NumOfF = nf;
  return TRUE;
} /* End of 'DK6_RndGObjLoad' function */



VOID DK6_RndGObjDraw( DK6GOBJ *GObj )
{
  INT i;
  POINT *pnts;

  if ((pnts = malloc(sizeof(POINT) * GObj->NumOfV)) == NULL)
    return;

  
  DK6_RndMatrWorldViewProj = MatrMulMatr(MatrMulMatr(DK6_RndMatrWorld, DK6_RndMatrView), DK6_RndMatrProj);
  for (i = 0; i < GObj->NumOfV; i++)
    pnts[i] = DK6_RndWorldToScreen(GObj->V[i]);

  
  for (i = 0; i < GObj->NumOfF; i++)
  {
    INT
      n1 = GObj->F[i][0],
      n2 = GObj->F[i][1],
      n3 = GObj->F[i][2];

    MoveToEx(DK6_Anim.hDC, pnts[n1].x, pnts[n1].y, NULL);
    LineTo(DK6_Anim.hDC, pnts[n2].x, pnts[n2].y);
    LineTo(DK6_Anim.hDC, pnts[n3].x, pnts[n3].y);
    LineTo(DK6_Anim.hDC, pnts[n1].x, pnts[n1].y);
  }

  free(pnts);
} /* End of 'DK6_RndGObjDraw' function */


VOID DK6_RndGObjFree( DK6GOBJ *GObj )
{
  free(GObj->V);
  memset(GObj, 0, sizeof(DK6GOBJ));
} /* End of 'DK6_RndGObjFree' function */

/* END OF 'RENDER.C' FILE */