#include "../header/grille.h"
#include "../header/sauvegarde.h"
#include "../header/coordonnees.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

//initialise la grille avec de l'eau partout donc une valeur egale a 0. Retourne type Grille
void initialiser_grille(Grille_j *j1, Grille_j *j2)
{
    j1->vie=5;
    j2->vie=5;
    int i, j;
    for (i = 0; i < TGRILLE; i++)
    {
        for (j = 0; j < TGRILLE; j++)
        {
            j1->grille[i][j]=eau;
            j1->grilleTire[i][j]=eau;
            j2->grille[i][j] = eau;
            j2->grilleTire[i][j] = eau;
        }
    }
}

void iniBateau(Grille_j *j, Grille_j *h)
{
    j->contre_torpilleur.idBateau = ID_contre_torpilleur;
    j->porteAvion.idBateau = ID_porteAvion;
    j->sous_marin.idBateau = ID_sous_marin;
    j->torpilleur.idBateau = ID_torpilleur;
    j->croiseur.idBateau = ID_croiseur;

    j->porteAvion.vieBateau = t_porte_avion;
    j->sous_marin.vieBateau = t_sous_marin;
    j->torpilleur.vieBateau = t_torpilleur;
    j->croiseur.vieBateau = t_croiseur;
    j->contre_torpilleur.vieBateau = t_contre_torpilleur;

    j->porteAvion.nom= "porte_avion";
    j->sous_marin.nom = "sous marin";
    j->torpilleur.nom = "torpilleur";
    j->croiseur.nom = "croiseur";
    j->contre_torpilleur.nom = "contre torpilleur";

    h->contre_torpilleur.idBateau = ID_contre_torpilleur;
    h->porteAvion.idBateau = ID_porteAvion;
    h->sous_marin.idBateau = ID_sous_marin;
    h->torpilleur.idBateau = ID_torpilleur;
    h->croiseur.idBateau = ID_croiseur;

    h->porteAvion.vieBateau = t_porte_avion;
    h->sous_marin.vieBateau = t_sous_marin;
    h->torpilleur.vieBateau = t_torpilleur;
    h->croiseur.vieBateau = t_croiseur;
    h->contre_torpilleur.vieBateau = t_contre_torpilleur;

    h->porteAvion.nom = "porte_avion";
    h->sous_marin.nom = "sous marin";
    h->torpilleur.nom = "torpilleur";
    h->croiseur.nom = "croiseur";
    h->contre_torpilleur.nom = "contre torpilleur";
    
}

//on affiche la grille avec differentes couleurs pour chaque situation : eau , eau deja touchee par un tir, un bateau ou alors un bateau touche
#if defined(WIN32)
void afficherGrille(int grille[TGRILLE][TGRILLE])
{
    int i, j;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    GREEN
    printf("\n   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|\n");
    printf(" --+---+---+---+---+---+---+---+---+---+---+");

    for (i = 0; i < TGRILLE; i++)
    {
        printf(" \n %c |", 'A' + i);
        for (j = 0; j < TGRILLE; j++)
        {
            if (grille[i][j] == eau)
            {
                printf("%s", "   "
                             "|");
            }
            else if (grille[i][j] == eau_touche)
            {
                RED
                    printf("%s", " * ");
                RESET
                printf("|");
            }
            else if (grille[i][j] == ID_contre_torpilleur || grille[i][j] == ID_croiseur || grille[i][j] == ID_porteAvion || grille[i][j] == ID_sous_marin || grille[i][j] == ID_torpilleur)
            {
                CYAN
                    printf("%s", "[$]");
                RESET
                printf("|");
            }
            else
            {
                RED
                    printf("%s", "[$]");
                RESET
                printf("|");
            }
        }
        printf("\n");
        GREEN
        printf(" --+---+---+---+---+---+---+---+---+---+---+");
    }
    printf("\n");
}
#elif __APPLE__
void afficherGrille(int grille[TGRILLE][TGRILLE])
{
    int i,j;
    printf(MAGENTA "\n  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|\n" RESET);
    printf(MAGENTA "--+---+---+---+---+---+---+---+---+---+---+" RESET);
    for (i = 0; i < TGRILLE; i++)
    {
        printf(MAGENTA "\n%c |" RESET, 'A'+i);
        for (j = 0; j < TGRILLE; j++)
        {
            if (grille[i][j] == eau){
                printf("%s", BLUE "   "  MAGENTA "|" RESET);
            }
            else if (grille[i][j] == eau_touche){
                printf("%s", YELLOW " * " MAGENTA"|" RESET);
            }
            else if (grille[i][j] == ID_contre_torpilleur || grille[i][j] == ID_croiseur || grille[i][j] == ID_porteAvion || grille[i][j] == ID_sous_marin || grille[i][j] == ID_torpilleur)
            {
                printf("%s", GREEN "[$]" MAGENTA "|" RESET);
            }else
            {
                printf("%s", RED "[$]" MAGENTA "|" RESET);
            }
            
        }
        printf("\n");
        printf(MAGENTA "--+---+---+---+---+---+---+---+---+---+---+" RESET);
    }
    printf("\n");
}

#endif
        //fonction pour placer les bateaux en fonction de leurs coordonnees et de leurs directions
        //vie bateau est egale aussi a la taille du bateau en debut de partie
Grille_j *placerBateau(Grille_j *joueur1, Bateau *b, int JouB,Grille_j *joueur2){ 
        srand(time(NULL));
        bool fini = false;
        int i;
        //chaine de caracteres pour recuperer les coordonnees du bateau;
        char *coordonnee=NULL;
        coordonnee = (char*)malloc(14*sizeof(char));
        afficherGrille(joueur1->grille);
        printf("\n");
        Coordonnees *c_bateau = NULL;
        c_bateau = (Coordonnees *)malloc(sizeof(Coordonnees));
        while (fini == false)
        {
            bool c_valide=true;
            if (JouB == 2)
            {
                printf("Donnez la position du %s de taille : %d\n",b->nom,b->vieBateau);

                scanf("%s", coordonnee);
            
                if (strcmp(coordonnee, "Sauvegarde")==0)
                {
                    SaveGrille(joueur1->grille, "grilleJ1.txt");
                    SaveGrille(joueur1->grille, "grilleJ2.txt");
                    exit(0);
                }
            
                else
                {
                    c_bateau = caracToCdn(coordonnee);
                    
                }
            }
            else
            {
                c_bateau->x = generer_borne(10);
                c_bateau->y = generer_borne(10);
                if (generer_borne(2) == 0)
                {
                    c_bateau->placement = 'V';
                }
                else
                {
                    c_bateau->placement = 'H';
                }
            }

            //on teste ici si les coordonnes rentrees sont comprises entre 0 et 9 ;
            if (c_bateau->x < 0 || c_bateau->y < 0 || c_bateau->x > TGRILLE-1 || c_bateau->y > TGRILLE-1)
            {
                printf("Mauvaises coordonnees veuillez reessayer\n");
                c_valide = false;
            } //on teste ici quand on met le bateau a l'horizontal la taille du bateau ne depasse pas la grille
            else if (c_bateau->placement == 'V')
            {
                if (c_bateau->x + b->vieBateau > TGRILLE)
                {
                    if (JouB == 2)
                    {
                        printf("Limite de la grille depassee\n");
                    }
                    c_valide = false;
                }
                else
                //on verifie si un bateau n'a pas ete place avant
                {
                    for (i = c_bateau->x; i < b->vieBateau + c_bateau->x; i++)
                    {
                        if (joueur1->grille[i][c_bateau->y] != eau)
                        {
                            if (JouB == 2)
                            {
                                printf("Il y a deja un bateau ici ! \n");
                            }

                            c_valide = false;
                        }
                    }
                }
            }
            else if (c_bateau->y + b->vieBateau > TGRILLE-1)
            {
                if (JouB == 2)
                {
                    printf("Limite de la grille depassee\n");
                }
                c_valide = false;
            }
            else
            //on verifie si un bateau n'a pas ete place avant
            {
                for (i = c_bateau->y; i < c_bateau->y + b->vieBateau; i++)
                {
                    if (joueur1->grille[c_bateau->x][i] != eau)
                    {
                        if (JouB == 2)
                        {
                            printf("Il y a deja un bateau ici ! \n");
                        }

                        c_valide = false;
                    }
                }
            }
            if (c_valide == true)
            {
                fini = true;
            }
        }
        //on place le bateau sur la grille grace aux coordonnees
        if (c_bateau->placement == 'V')
        {
            for (i = c_bateau->x; i < c_bateau->x + b->vieBateau; i++)
            {
                joueur1->grille[i][c_bateau->y] = b->idBateau;
            }
        }
        else
        {
            for (i = c_bateau->y; i < c_bateau->y + b->vieBateau; i++)
            {
                joueur1->grille[c_bateau->x][i] = b->idBateau;
            }
        }
        free(c_bateau);
        return joueur1;
    }

//ici on cree la fonction tire qui va tirer sur la grille ennemie le but etant de montrer sur la grille si un bateau a ete touche,
//sans afficher la grille ennemie au joueur qui tire 
//si retourne 1 le joueur retire 
int attaque(Grille_j *joueur1,Grille_j *joueur2,int JouB,int difficulter,int RecupC){
    int BatOuEau=0;
    FILE* fichier = NULL;
    bool touche =false;
    afficherGrille(joueur1->grilleTire);
    Coordonnees *tire = NULL;
    tire = (Coordonnees *)malloc(sizeof(Coordonnees));
    int idcase;
    char *c_tire=NULL;
    c_tire=(char*)malloc(13*sizeof(char));


    while (touche==false)
    {

        if (JouB == 2)
        {
            printf("Donnez la coordonnees du tire\n");
            scanf("%s", c_tire);
            if (strcmp(c_tire, "Sauvegarde") == 0)
                {
                    SaveGrille(joueur1->grille, "grilleJ1.txt");
                    SaveGrille(joueur1->grilleTire, "grilleTireJ1.txt");
                    SaveGrille(joueur2->grille, "grilleJ2.txt");
                    SaveGrille(joueur2->grille, "grilleTireJ2.txt");
                    exit(0);
                }
                else
                {
                    tire = caracToCdn(c_tire);
                }
            }
        if (RecupC==0 && JouB ==1)
        {
            tire->x = generer_borne(10);
            tire->y = generer_borne(10);
        }
        if (RecupC == 1&&JouB==1 && difficulter == 1){
            fichier = fopen("coordonnee.txt", "r");

            fscanf(fichier, "%d%d", &tire->x, &tire->y);
            printf("x=%d y= %d \n", tire->x, tire->y);
            int a = generer_borne(4);
            {
            
            if (a==0)
            {
                tire->x--;
            }
            if (a == 1)
            {
                tire->y--;
            }
            if (a == 2)
            {
                tire->x++;
            }
            if (a == 3)
            {
                tire->y++;
            }
            }
            fclose(fichier);
        }
   
        
            
        
    idcase = joueur2->grille[tire->x][tire->y];
    if(idcase == eau || idcase==eau_touche)
    {
        printf("tir rate\n");
        joueur1->grilleTire[tire->x][tire->y] = eau_touche;
        joueur2->grille[tire->x][tire->y] = eau_touche;
        BatOuEau=0;
        break;
    }
    else if (idcase == joueur2->contre_torpilleur.idBateau || idcase == joueur2->croiseur.idBateau || idcase == joueur2->porteAvion.idBateau || idcase == joueur2->sous_marin.idBateau || idcase == joueur2->torpilleur.idBateau)
    {
        printf("Vous avez touche un bateau ! \n");
    
        joueur1->grilleTire[tire->x][tire->y] = bat_toucher;
        joueur2->grille[tire->x][tire->y]=bat_toucher;

        switch (idcase)
        {
        case ID_porteAvion:
            joueur2->porteAvion.vieBateau--;
            if(joueur2->porteAvion.vieBateau==0)
            {
               printf("Vous avez couler le porte avion de l'enemie\n");
            }
            
            break;
        case ID_contre_torpilleur:
            joueur2->contre_torpilleur.vieBateau--;
             if(joueur2->contre_torpilleur.vieBateau==0)
            {
               printf("Vous avez couler le contre torpilleur de l'enemie\n");
            }
            break;
        case ID_croiseur:
            joueur2->croiseur.vieBateau--;
            if (joueur2->croiseur.vieBateau == 0)
            {
                printf("Vous avez couler le croiseur de l'enemie\n");
            }

            break;
        case ID_sous_marin:
            joueur2->sous_marin.vieBateau--;
            if (joueur2->sous_marin.vieBateau == 0)
            {
                printf("Vous avez couler le sous marin de l'enemie\n");
            }

            break;
        case ID_torpilleur:
            joueur2->torpilleur.vieBateau--;
            break;
        default:
            break;
        }
        if (difficulter == 1 && JouB == 1)
        {
            fichier = fopen("coordonnee.txt", "w+");
            fprintf(fichier, "%d %d", tire->x, tire->y);
            fclose(fichier);
            free(c_tire);
            attaque(joueur1,joueur2,JouB,difficulter,1);
        }
        BatOuEau = 1;
        break;
        }
       
    
    }
    free(c_tire);

    return BatOuEau;
    
    
}
