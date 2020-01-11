/* Przetwarzanie obrazów - Maciej Putyra*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "negatyw.h"
#include "progowanie.h"
#include "wyswietl.h"
#include "zmiana_poziomow.h"
#include "konturowanie.h"
#include "rozmywanie_poziome.h"
#include "rozciaganie.h"
#include "zapisz.h"


#define MAX 512
#define DL_LINII 1024
	
int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? lub czy w poprzednim 
nie udalo sie*/
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",wymx,wymy,szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<*wymy;i++) {
    for (j=0;j<*wymx;j++) {
      if (fscanf(plik_we,"%d",&(obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return *wymx**wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */





int main()
{
  int obraz[MAX][MAX];
  int wymx,wymy,odcieni;
  int wybor;
  float P_PROG,ZM_POZIOMOW;//P_PROG okresla poziom progowania,wpisywany jako procent,ZM_POZIOMOW-
  int odpowiedz; //odpowiedz uzytkownika czy zapisac zmiany

  int odczytano=0;
  FILE *plik,*plik2;//plik2,do otwieranie pliku pomocniczego w ktorym dokonywane sa zmiany
  char nazwa[100];
  char nazwa2[100]="nazwa2.c";//nazwa pliku pomocniczego
  printf("Podaj nazwe pliku: \n");
  scanf("%s",nazwa);
  plik=fopen(nazwa,"r");

  if(plik!=NULL){ 
    odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
    fclose(plik);
  }

  if(odczytano != 0){ //mozemy wykonywac operacje na obrazie tylko wtedy gdy jest on poprawnego formatu
       while(wybor != 8)
      {	  
       printf("Proste menu:\n");
      printf("1 - WYŚWIETL ZAPISANY WYGLĄD\n");
      printf("2 - WYŚWIETL NEGATYW\n");
      printf("3 - PROGOWANIE\n");
      printf("4 - ZMIANA POZIOMOW\n");
      printf("5 - KONTUROWANIE\n");
      printf("6 - ROZMYWANIE POZIOME\n");
      printf("7 - ROZCIAGANIE\n");
      printf("8 - WYJŚCIE\n");
      printf("Twój wybór: ");
      scanf("%d",&wybor);
     
	
      
      switch(wybor)
	{
	case 1:
	  {
	    wyswietl(nazwa);//wyswietlanie wejsciowego/wczesniej zapisanego pliku
	    break;
	}
        case 2:
	{
	  negatyw(obraz,&wymx,&wymy,&odcieni); //wczytanie do tablicy obraz wartosci odpowiednich dla wykonywanego przetwarzania obrazu
	  plik2=fopen(nazwa2,"w"); //otwarcie pliku pomocniczego lub utworzenie go z opcja wpisywania do niego
	  zapisz(plik2,obraz,&wymx,&wymy,&odcieni); //zapisanie w pliku pomocniczym zmienionej tablicy
	  wyswietl(nazwa2);//wyswietlenie nowego wygladu obrazu
	  fclose(plik2);//zamkniecie pliku
	  //kazda funkcja przetwarzania obrazow dziala analogicznie,zmieniaja się jedynie wartości w tablicach
    break;
	}
      case 3:
	{
	printf("Jaki procent progowania?: \n");
	scanf("%f",&P_PROG);
	while(P_PROG<0 || P_PROG>100){//trzeba wprowadzić procent z zakresu od 0 do 100
	  printf("Wprowadź liczbę z przedziału <0,100>\n");
	  scanf("%f",&P_PROG);
	}
	progowanie(obraz,&wymx,&wymy,&odcieni,P_PROG);
	plik2=fopen(nazwa2,"w");
	zapisz(plik2,obraz,&wymx,&wymy,&odcieni);
	fclose(plik2);
	wyswietl(nazwa2);
      
	break;
        }
	case 4:
	  {
	    printf("Podaj procent czerni jaki chcesz uzyskac: \n");
	    scanf("%f",&ZM_POZIOMOW);
	    while(ZM_POZIOMOW < 0 || ZM_POZIOMOW > 100){//trzeba wprowadzić procent z zakresu od 0 do 100
	      printf("Podaj liczbę z przedziału <0,100>\n");
	      scanf("%f",&ZM_POZIOMOW);
	    }
	    printf("Twoj poziom czerni to %.0f procent a bieli %.0f procent \n",ZM_POZIOMOW,100-ZM_POZIOMOW);
	    zmiana_poziomow(obraz,&wymx,&wymy,&odcieni,ZM_POZIOMOW);
	    plik2=fopen(nazwa2,"w");
	    zapisz(plik2,obraz,&wymx,&wymy,&odcieni);
	    fclose(plik2);
	    wyswietl(nazwa2);
	    break;
	  }
	case 5:
	  {
	    konturowanie(obraz,&wymx,&wymy,&odcieni);
	    plik2=fopen(nazwa2,"w");
	    zapisz(plik2,obraz,&wymx,&wymy,&odcieni);
	    fclose(plik2);
	    wyswietl(nazwa2);
	    break;
	  }
	case 6:
	  {
	    rozmywanie_poziome(obraz,&wymx,&wymy,&odcieni);
	    plik2=fopen(nazwa2,"w");
	    zapisz(plik2,obraz,&wymx,&wymy,&odcieni);
	    fclose(plik2);
	    wyswietl(nazwa2);
	    break;
	  }
	case 7:
	  {
	    rozciaganie(obraz,&wymx,&wymy,&odcieni);
	    plik2=fopen(nazwa2,"w");
	    zapisz(plik2,obraz,&wymx,&wymy,&odcieni);
	    fclose(plik2);
	    wyswietl(nazwa2);
	    break;
	  }
	}//koniec switcha
      
      if(wybor != 8 && wybor != 1){ //jezeli uzytkownik chce zobaczyc aktualny stan obrazu lub wyjsc to program nie bedzie go pytac o zapisanie pliku
	printf("Zapisać zmiany?1-TAK 0-NIE\n");
	scanf("%d",&odpowiedz);
	while(odpowiedz != 1 && odpowiedz != 0){//dopóki do programu nie bedzie wprowadzona liczba 1 lub 0,program bedzie pytac uzytkownika czy zapisać
	  printf("Zapisać zmiany?1-TAK 0-NIE\n");
	  scanf("%d",&odpowiedz);
	}
		 if(odpowiedz==1){ //zapisz zmiany
		   plik=fopen(nazwa,"w");//otworz plik wejsciowy
		   zapisz(plik,obraz,&wymx,&wymy,&odcieni);//zapisz w nim zmiany
		   fclose(plik);
		 }
		 if(odpowiedz==0){ //nie zapisuj
		   plik=fopen(nazwa,"r");
		   plik2=fopen(nazwa2,"w");
		   czytaj(plik,obraz,&wymx,&wymy,&odcieni); //wczytaj obraz wjesciowy/wczesniej zapisany
		   zapisz(plik2,obraz,&wymx,&wymy,&odcieni);//zapisz w nazwa2 obraz wejsciowy/wczesniej zapisany
		   fclose(plik);
		   fclose(plik2);
		 }
      }
      }//koniec while
  }
}

/************************************************************
TESTY ORAZ DZIAŁANIE PROGRAMU
Obraz kubus.pgm
Program prawidloło odczytuje plik,dzieki czemu użytkownik
może przystąpić do ewentualnych przetwarzań obrazów.
Każda z powyższych funkcji prawidłowo przetwarza obraz,
tak samo jak w materiałach do zadania,ponadto program
po każdej operacji zmiany wyglądu obrazu wyświetla zmieniony
plik oraz daje możliwość zapisania lub cofnięcia zmian.
Użytkownik również ma możliwość wyświetlenia aktualnie
zapisanego stanu obrazu.
  

***********************************************************/
