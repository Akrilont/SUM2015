 /* FILE NAME: T03PERM
  * PROGRAMMER: DK6
  * DATE: 03.06.2015
  * PURPOSE: Permutation Samples
  */

#include <stdio.h>
#define N 7
int P[N];
int Parity = 0;
FILE *F;

void Swap( int *a, int *b )
{
  int tmp = *a; 

  *a = *b;
  *b = tmp;

}

void WFile( int a)
{
  static int k = 0;
 
  if ((F = fopen("a.log", "a")) != NULL)
  {
    k++;
    fprintf(F, "%d", a);
    if (k % N == 0)
      fprintf(F, "- %s\n", Parity ? "Odd" : "Even");
    fclose(F);

  }
}


void Go( int Pos )
{
  int i;

  if (Pos == N)
  {
    for (i = 0; i < N; i++)
      WFile(P[i]);
    return;
  }

  for (i = Pos; i < N; i++)
  {
    if (Pos != i)
      Parity = !Parity;
    Swap(&P[Pos],&P[i]);
    
    Go(Pos + 1);
    if (Pos != i)
      Parity = !Parity;
    Swap(&P[Pos], &P[i]);
  }
}



void main( void )
{ 
  int i;

  if ((F = fopen("a.log", "w")) != NULL)
    fclose(F); 

  for (i = 0; i < N; i++)
    P[i] = i + 1; 
  Go(0);
  
}                                