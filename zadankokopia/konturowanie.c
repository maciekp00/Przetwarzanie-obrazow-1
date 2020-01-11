#define MAX 512
#include <stdlib.h>
#include "konturowanie.h"
void konturowanie(int obraz_pgm[][MAX],int *wymx,int *wymy,int *szarosci)
{
  for(int i=0;i<*wymy;i++){
    for(int j=0;j<*wymx;j++){
      obraz_pgm[i][j]=(abs(obraz_pgm[i+1][j]-obraz_pgm[i][j])+abs(obraz_pgm[i][j+1]-obraz_pgm[i][j]));
      }
  }
}
