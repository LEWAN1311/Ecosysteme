#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

float p_ch_dir=0.01;
float p_reproduce_proie=0.2;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-8;


int main(){
    srand(time(NULL));

    //Creation des listes de 20 proies et de 20 prédateurs 
    Animal *liste_proie = NULL;
    Animal *liste_preda = NULL;

    for (int i = 0; i < 20; i++)
    {
        ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y, 10.0, &liste_proie);
    }

    for (int i = 0; i < 20; i++)
    {
        ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y, 10.0, &liste_preda);
    }

    //Test écrire écosys
    ecrire_ecosys("TestProiPredaEcrire.txt",liste_proie,liste_preda);

    lire_ecosys("TestProiPredaEcrire.txt",&liste_proie,&liste_preda);

    afficher_ecosys(liste_proie,liste_preda);

    liberer_liste_animaux(liste_proie);
    liberer_liste_animaux(liste_preda);
    return 0;
}