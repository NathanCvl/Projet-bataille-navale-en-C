#ifndef SAUVEGARDE
#define SAUVEGARDE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/grille.h"
void SaveGrille(int grille[TGRILLE][TGRILLE], char nom[]);
void ChargerGrille(int grille[TGRILLE][TGRILLE], char nom[]);
#endif