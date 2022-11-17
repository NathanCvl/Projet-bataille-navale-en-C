#ifndef _PARTIE_
#define _PARTIE_
#include <stdio.h>
#include "../header/grille.h"
void Bat_grille(Grille_j *j1, Grille_j *j2, int JouB);
int generer_borne(int n);
int etat(Grille_j *j1, Grille_j *j2);
int tourJ(Grille_j *j1, Grille_j *j2, int JouB, int difficulte);
void partie();

#endif