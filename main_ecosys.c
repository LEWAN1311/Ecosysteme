#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 50
#define NB_PREDATEURS 50
#define T_WAIT 40000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.2;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-8;


int main(void) {
 
  /* A completer. Part 2:
   * exercice 4, questions 2 et 4 
   * exercice 6, question 2
   * exercice 7, question 3
   * exercice 8, question 1
   */

  srand(time(NULL));

  Animal *liste_proie = NULL;
  Animal *liste_preda = NULL;

  int compte_nb_proies = 0;
  int compte_nb_predas = 0;

  /*Creer 20 proies aléatoirement*/
  for (int i = 0; i < NB_PROIES; i++)
  {
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,10,&liste_proie);
  }
  compte_nb_proies = compte_animal_it(liste_proie); //20 proies

  /* Creer 20 prédateurs aléatoirement*/
  for (int i = 0; i < NB_PREDATEURS; i++)
  {
      ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y,10, &liste_preda);
  }
  compte_nb_predas = compte_animal_it(liste_preda); //20 prédateurs

  /*Ecrire et lire fichier*/
  ecrire_ecosys("ProiePredaAvantParcourir.txt",liste_proie,liste_preda);

  /*Affichage*/
  afficher_ecosys(liste_proie,liste_preda);
  
  /*Bouger*/
  bouger_animaux(liste_proie);
  bouger_animaux(liste_preda);
  
  /* Reproduce*/
  reproduce(&liste_proie,p_reproduce_proie);
  reproduce(&liste_preda,p_reproduce_predateur);

  /*Ecrire et lire fichier*/
  ecrire_ecosys("ProiePredaApresParcourir.txt",liste_proie,liste_preda);

  afficher_ecosys(liste_preda,liste_proie);

  /* Creation de tableau */
  int monde[SIZE_X][SIZE_Y];
  for (int k = 0; k < SIZE_X; k++)
  {
    for (int l = 0; l < SIZE_Y; l++)
    {
      monde[k][l] = 0;
    }
  }

  /*Rafraichissement dans une boucle*/
  FILE *f = fopen("Evol_Pop.txt","w");

  for (int i = 0; i < 400; i++)
  {
    compte_nb_proies = compte_animal_it(liste_proie); 
    compte_nb_predas = compte_animal_it(liste_preda); 

    fprintf(f,"%d %d %d\n",i,compte_nb_proies,compte_nb_predas);

    if (compte_nb_proies == 0)
    {
      printf("Terminer\n");
      break;
    }
    
    rafraichir_monde(monde);
    rafraichir_predateurs(&liste_preda,&liste_proie);
    rafraichir_proies(&liste_proie,monde);
    

    usleep(T_WAIT);
    afficher_ecosys(liste_proie,liste_preda);
    // clear_screen();
  }

  /* Gnuplot */
  // FILE * gnuplotPipe = popen("gnuplot -persistent","w");
  // if(gnuplotPipe){
  //   FILE *gnuFile = fopen("graphe.gnu","r");
  //   if (gnuFile)
  //   {
  //     char buffet[256];
  //     while (fgets(buffet,sizeof(buffet),gnuFile) != NULL)
  //     {
  //       fputs(buffet,gnuplotPipe);
  //     }
  //     fclose(gnuFile);
  //   }
  //   fputs("plot 'Evol_Pop.txt' using 1:2 with lines title 'proie' \n",gnuplotPipe);
  //   fputs("replot 'Evol_Pop.txt' using 1:3 with lines title 'predateur' \n",gnuplotPipe);
  //   fflush(gnuplotPipe);
  //   fprintf(gnuplotPipe,"exit\n");
  //   pclose(gnuplotPipe);
  // }
  // else
  // {
  //   fprintf(stderr, "Pas pouvoir d'ouvrir Gnuplot\n");
  // }
  
  /*Liberer*/
  liste_preda = liberer_liste_animaux(liste_preda);
  liste_proie = liberer_liste_animaux(liste_proie);

  return 0;
}



