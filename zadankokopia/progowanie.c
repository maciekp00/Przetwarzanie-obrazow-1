#define MAX 512
#include "progowanie.h"//
void progowanie(int obraz_pgm[][MAX],int *wymx,int *wymy,int *szarosci,float P_PROG)
{
  float P_PROG_PRZELICZONY;//zmienna lokalna ktora przelicza procentowo odcien szarosci wedlug progowania
  P_PROG_PRZELICZONY=P_PROG/100;
  for(int i=0;i<*wymy;i++){
    for(int j=0;j<*wymx;j++){
      if(obraz_pgm[i][j]<=(*szarosci*P_PROG_PRZELICZONY))   
	obraz_pgm[i][j]=0;
      else
	obraz_pgm[i][j]=*szarosci;
    }
  }
}
