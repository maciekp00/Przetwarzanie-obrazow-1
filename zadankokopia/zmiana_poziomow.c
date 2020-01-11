#define MAX 512
#include "zmiana_poziomow.h"

void zmiana_poziomow(int obraz_pgm[][MAX],int *wymx,int *wymy,int *szarosci,float ZM_POZIOMOW)
{
  float CZERN,BIEL,P_POZIOM;//lokalne zmienne pomocnicze
  P_POZIOM=ZM_POZIOMOW/100;
  CZERN=P_POZIOM*(*szarosci);
  BIEL=(1-P_POZIOM)*(*szarosci); //okreslenie progów na podstawie wartosci procentowej wprowadzonej przez użytkownika do programu
  for(int i=0;i<*wymy;i++){
    for(int j=0;j<*wymx;j++){
      if(obraz_pgm[i][j]<=CZERN)
	obraz_pgm[i][j]=0;
      if(obraz_pgm[i][j]>=BIEL)
	obraz_pgm[i][j]=*szarosci;
      if(obraz_pgm[i][j]>CZERN && obraz_pgm[i][j]<BIEL)
	obraz_pgm[i][j]=(obraz_pgm[i][j]-CZERN)*(*szarosci)/(BIEL-CZERN);
    }
  }

}
