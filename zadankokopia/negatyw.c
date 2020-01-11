#define MAX 512
#include "negatyw.h"
void negatyw(int obraz_pgm[][MAX],int *wymx,int *wymy,int *szarosci)
{
  for(int i=0;i<*wymy;i++){
    for(int j=0;j<*wymx;j++)
      obraz_pgm[i][j]=*szarosci-(obraz_pgm[i][j]+1);
  }   
}
