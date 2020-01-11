#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"zapisz.h"
//baba
#define MAX 512

/*funkcja zapisz uzupełnia tablicę wedlug wprowadzonych do niej  danych*/
void zapisz(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy,int *szarosci)
{
  fprintf(plik_we,"P2\n");
  fprintf(plik_we,"%d %d\n",*wymx,*wymy);
  fprintf(plik_we,"%d\n",*szarosci);
  
  for (int i=0;i<*wymy;i++) {
    for (int j=0;j<*wymx;j++) {
      fprintf(plik_we,"%d ",obraz_pgm[i][j]); 
      }
    fprintf(plik_we,"\n");
    }   
}
