#include "../header/coordonnees.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    
    ↑(y)
    |
    |
    |
    ------>(x)
ici on veut recuperer un type coordonnees donnant pour coordonnees par exemple 
entre cdn="J10V" retourne coord.x= 9 coord.y=9 et coord.placement = V
ici la demarche est de pouvoir convertir le type string en type coordonnees


*/
//retourne le type coordonnees avec comme valeur d'entree une chaine de caracteres
Coordonnees *caracToCdn(char cdn[])
{
    Coordonnees *coord=NULL;
    coord = (Coordonnees *)malloc(sizeof(Coordonnees));
    int i;
    char buffer[4];
 

    // ici on veut convertir deux caracteres en nombre que le caractere '10' devienne le nombre 9
    // pour pouvoir convertir les deux caracteres on doit l'envoyer dans un autre tableau sans le premier et dernier caractere
    // copie cdn vers buffer pour isoler la coordonnee x.

    for (i = 0; i < strlen(cdn) - 1; i++)
    {
        buffer[i] = cdn[i + 1];
    }
    //atoi() convertie des caracteres alphanumeriques en int mais comme le tableau commence en 0 on enleve 1 au resultat
    //obli
    coord->y = atoi(buffer)-1;


    // comme on demande d'abord la coordonnee y on recupere en debut du tableau
    // ici avec le code ASCII on convertit le caractere donc si coord.y = A on fait 'A'-'A'= 0
    coord->x = cdn[0] - 'A';
    // la direction devra etre rentree en dernier on la recupere en recuperant la derniere case du tableau cdn
    coord->placement = cdn[strlen(cdn) - 1];
    return coord;
    free(coord);
}
