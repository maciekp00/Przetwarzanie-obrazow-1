#define MAX 512
#include "rozmywanie_poziome.h"
void rozmywanie_poziome(int obraz_pgm[][MAX],int *wymx,int *wymy,int *szarosci)
{
  for(int i=0;i<*wymy;i++){
    for(int j=0;j<*wymx;j++){
      if(i!=0) //zeby obraz_pgm[i-1][j] mialo sens
      obraz_pgm[i][j]=(obraz_pgm[i-1][j]+obraz_pgm[i][j]+obraz_pgm[i+1][j])/3;
    }
  }
}
