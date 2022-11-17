#ifndef _COORDONNEES_
#define _COORDONNEES_

/* definiton d'une structure coordonnees pour stocker la direction et les coordonnees dans une seule variable*/
typedef struct{
    int x, y;
    char placement; /* pour definir la direction du bateau sur la grille */
} Coordonnees;
Coordonnees *caracToCdn(char cdn[]);

#endif