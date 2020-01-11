#define MAX 512 
#include "rozciaganie.h"
void rozciaganie(int obraz_pgm[][MAX],int *wymx,int *wymy,int *szarosci)
{
  int Lmax=1,Lmin=*szarosci;
  //szukanie najwiekszego elementu
  for(int i=0;i<*wymy;i++){
    for(int j=0;j<*wymx;j++){
      if(obraz_pgm[i][j]>=Lmax)
	Lmax=obraz_pgm[i][j];
    }
  }
  //szukanie najmniejszego elementu
  for(int i=0;i<*wymy;i++){
    for(int j=0;j<*wymx;j++){
      if(obraz_pgm[i][j]<=Lmin)
	Lmin=obraz_pgm[i][j];
    }
  }
  //uzupelnianie tablicy nowymi wartosciami
  for(int i=0;i<*wymy;i++){
    for(int j=0;j<*wymx;j++){
      obraz_pgm[i][j]=(obraz_pgm[i][j]-Lmin)*(*szarosci)/(Lmax-Lmin);
    }
  }
  
}
