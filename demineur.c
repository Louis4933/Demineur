/*!
* \file demineur.c
* \author Floreani Louis <floreanilo@cy-tech.fr>
* \version 0.1
* \date 29/12/2021
* \brief 
* \remarks Jeu du demineur
* 
* 
* 
*/

/*! Importation of librairies*/
#include "demineur.h"

/*!
* \fn void initialisation (Case** tableau, int N)
* \author Floreani Louis <floreanilo@cy-tech.fr>
* \version 0.1
* \date  29/12/2021
* \brief 
* \remarks None
* \param tableau 
* \param N 
*/

void initialisation (Case** tableau, int N)
{
    /* on initialise chaque champ de chaque case du tableau */
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            tableau[i][j].minee = false; // il n'y a pas de mine sur cette casse
            tableau[i][j].drapeau = false; // ni de drapeau
            tableau[i][j].revelee = false; // cette case n'est pas revelee
            tableau[i][j].mines_voisines = 0; // et n'a pas de mine voisine
        }
    }
}

/*!
* \fn void tirage_alea (Case** tableau, int N, int nb_mines)
* \author Floreani Louis <floreanilo@cy-tech.fr>
* \version 0.1
* \date  29/12/2021
* \brief 
* \remarks None
* \param tableau 
* \param N 
* \param nb_mines 
*/

void tirage_alea (Case** tableau, int N, int nb_mines)
{
    /* declaration de la variable comptant les mines, des variables ligne et colonne */
    int compt_mines=0;
    int i=0;
    int j=0;

    while (compt_mines != nb_mines) // tant qu'on a pas nb_mines mines dans le tableau
    {
        i = rand()%N; // ligne aleatoire entre 0 et N-1
        j = rand()%N; // colonne aleatoire entre 0 et N-1
        if ( tableau[i][j].minee == false ) // si la case n'est pas minee
        /* tableau[i][j] est une Case, type qu'on a defini dans le fichier .h */
        {
            tableau[i][j].minee = true ; // la case devient minee
            compt_mines = compt_mines + 1; // et le compteur de mines augmente
        }
    }
}

/*!
* \fn void mines_voisines (Case** tableau, int N)
* \author Floreani Louis <floreanilo@cy-tech.fr>
* \version 0.1
* \date  29/12/2021
* \brief 
* \remarks None
* \param tableau 
* \param N 
*/

void mines_voisines (Case** tableau, int N)
{
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        /* on parcourt chaque case du tableau */
        {
            if (tableau[i][j].minee == false) // si la case n'est pas minee
            {
                for (int k=0; k<3; k++)
                {
                    for (int l=0; l<3; l++)
                    /* alors on parcourt chaque case autour de cette case pour voir s'il y a une mine */
                    {
                        /* on verifie d'abord que ces cases sont bien dans le tableau */
                        if (((i-1+k)>=0) && ((j-1+l)>=0) && ((i-1+k)<N) && ((j-1+l)<N) && (tableau[i-1+k][j-1+l].minee == true)) 
                        {
                            tableau[i][j].mines_voisines ++; // s'il y a une mine, on augmente le compteur de mines voisines de la case
                        }

                    }
                }
            }
        }
    }
    /* resultat : toutes les cases non minees ont un nb de mines voisines */
}

/*!
* \fn void decouvrement (Case** tableau, int ligne, int colonne, int N)
* \author Floreani Louis <floreanilo@cy-tech.fr>
* \version 0.1
* \date  29/12/2021
* \brief 
* \remarks None
* \param tableau 
* \param ligne 
* \param colonne 
* \param N 
*/

void decouvrement (Case** tableau, int ligne, int colonne, int N)
{
    /* si la case choisie par l'utilisateur n'a pas de mine voisine, qu'elle n'est pas revelee, et pas minee */
    if ((tableau[ligne][colonne].mines_voisines == 0) && (tableau[ligne][colonne].revelee == false) && (tableau[ligne][colonne].minee == false))
    {
        tableau[ligne][colonne].revelee = true; // alors on la revele

        if (ligne<(N-1)) // et si la case du dessous est dans le tableau
        {
            decouvrement(tableau, ligne+1, colonne, N); // on fait un appel recursif de la fonction sur la case du dessous
        }
        if ((ligne<(N-1)) && (colonne>=1)) // si la case en bas a gauche est accessible
        {
            decouvrement(tableau, ligne+1, colonne-1, N); // on fait un appel recursif de la fonction sur la case en bas a gauche
        }
        if (ligne<(N-1) && (colonne<(N-1))) // si la case en base a droite est accessible
        {
            decouvrement(tableau,ligne+1,colonne+1, N); // on fait un appel recursif de la fonction sur la case en bas a droite
        }
        if (ligne>=1) // si la case du dessus est accessible
        {
            decouvrement(tableau, ligne-1, colonne, N); // on fait un appel recursif de la fonction sur la case du dessus
        }
        if ((ligne>=1) && (colonne >=1)) // si la case en haut a gauche est accesible
        {
            decouvrement(tableau,ligne-1,colonne-1,N); // on fait un appel recursif de la fonction sur la case en haut a gauche
        }
        if ((ligne>=1) && (colonne<(N-1))) // si la case en haut a droite est accessible
        {
            decouvrement(tableau,ligne-1,colonne+1,N); // on fait un appel recursif de la fonction sur la case en haut a droite
        }
        if (colonne<(N-1)) // si la case a droite est accessible
        {
            decouvrement(tableau, ligne, colonne+1, N); // on fait un appel recursif de la fonction sur la case a droite
        }
        if (colonne>=1) // si la case a gauche est accessible
        {
            decouvrement(tableau, ligne, colonne-1, N); // on fait un appel recursif de la fonction sur la case a gauche
        }
        return; // si on est bloque on arrete la fonction
    }
    /* si la case choisie par l'utilisateur n'a pas de mine voisine, n'est pas revelee et pas minee */
    else if ((tableau[ligne][colonne].mines_voisines != 0) && (tableau[ligne][colonne].revelee == false) && (tableau[ligne][colonne].minee == false))
    {
        tableau[ligne][colonne].revelee = true; // on la revele
        return; // et on s'arrete la
    }
}

/*!
* \fn int choix_position (Case** tableau, int ligne, int colonne, int choix, int N)
* \author Floreani Louis <floreanilo@cy-tech.fr>
* \version 0.1
* \date  29/12/2021
* \brief 
* \remarks None
* \param tableau 
* \param ligne 
* \param colonne 
* \param choix 
* \param N 
* \return 
*/

int choix_position (Case** tableau, int ligne, int colonne, int choix, int N)
{
    if (choix == 0) // si le choix est de poser un drapeau
    {
        tableau[ligne][colonne].drapeau = true; // le champ correspondant au drapeau de la case devient true
    }
    else if (choix == 1) // si le choix est de reveler la case
    {
        // il y a deux cas
        if (tableau[ligne][colonne].minee == true) // soit la case est minee
        {
            tableau[ligne][colonne].revelee = true; // on la revele alors simplement
        }
        else // soit elle ne l'est pas
        {
            /* on fait alors appel a la fonction decouvrement qui permet de decouvrir les cases alentour en chaine ou de simplement decouvrir la case */
            decouvrement(tableau, ligne, colonne, N);
        }
    }
}

/*!
* \fn int main ()
* \author Floreani Louis <floreanilo@cy-tech.fr>
* \version 0.1
* \date 29/12/2021
* \brief Main function of the program
* \remarks None
* \param argc number of arguments given as inputs
* \param argv value of arguments given as inputs
* \return 0 if all went good
*/
int main ()
{
    srand(time(NULL)); // pour que la fonction random renvoie bien des nombres aleatoires

    int N; // declaration de la dimension du tableau
    int nb_mines; // declaration du nombre de mines
    Case** tableau; // declaration d'un tableau de cases
    int decompte = 0; //declaration du decompte des mines

    int condi_win = 0; // declaration de la variable permettant de savoir si toutes les cases vides sont decouvertes
    bool perdu = false; // declaration de la variable permettant de savoir si une mine est touchee

    printf("Quelle dimension? \n");
    scanf("%d", &N); // l'utilisateur rentre la dimension souhaitee

    if (!(N>=0) | !(N<=100000000))
    {
        printf("La dimension n'est pas un entier ou est trop grande ou non positive\n");
        exit(ERREUR_SAISIE);
    }
    
    
    printf("Combien de mines? \n");
    scanf("%d", &nb_mines); // l'utilisateur rentre le nombre de mines souhaite

    if (!(nb_mines>=0) | !(nb_mines<=100000000))
    {
        printf("Le nombre de mines n'est pas un entier ou est trop grand ou non positif\n");
        exit(ERREUR_SAISIE);
    }
    
    
    // s'il y a plus de mines que de cases
    if (nb_mines>N*N)
    {
        printf("Il y a trop de mines \n");
        exit(ERREUR_SAISIE); // on sort du programme
    }

    /* on alloue de la memoire pour un tableau de tableaux de cases dynamique */
    tableau = (Case**)malloc(N*sizeof(Case*));
    for (int j=0; j<N; j++)
    {
        tableau[j] = (Case*)malloc(N*sizeof(Case));
    }
    
    initialisation(tableau, N); // on initialise tous les champs des cases du tableau
    tirage_alea(tableau, N, nb_mines); // on place aleatoirement nb_mines mines dans le tableau
    mines_voisines (tableau, N); // on compte pour chaque case son nombre de mines voisines

    // on affiche le tableau avec toutes ses cases dissimulees
    
    printf("\n");
    printf("    ");
    for (int k=0; k<N; k++)
    {
        printf("  %d ", k);
    }
    printf("\n");
    for (int i=0; i<N; i++)
    {
        printf("    ");
        for (int l=0; l<N; l++)
        {
            printf("+---");
        }
        printf("+");
        printf("\n");
        printf("  %d ", i);
        for (int j=0; j<N; j++)
        {
            printf("| # ");
        }
        printf("|");
        printf("\n");
    }
    printf("    ");
    for (int l=0; l<N; l++)
    {
        printf("+---");
    }
    printf("+");
    printf("\n");
    printf("     Mines : 0/%d", N);
    printf("\n\n");

    while ((condi_win != (N*N-nb_mines)) && (perdu == false))
    {
        int ligne = 0;
        int colonne = 0;
        int choix = 0;

        /* choix de l'utilisateur */
        printf("Ligne (entre 0 et %d): \n", N - 1);
        scanf("%d", &ligne);

        if (!(ligne>=0) | !(ligne<=(N-1)))
        {
            printf("La ligne rentree n'est pas comprise entre 0 et %d\n", N - 1);
            exit(ERREUR_SAISIE);
        }

        printf("Colonne (entre 0 et %d) : \n", N - 1);
        scanf("%d", &colonne);

        if (!(colonne>=0) | !(colonne<=(N-1)))
        {
            printf("La colonne rentree n'est pas comprise entre 0 et %d\n", N - 1);
            exit(ERREUR_SAISIE);
        }
        

        printf("0 pour poser un drapeau, 1 pour reveler : \n");
        scanf("%d", &choix);

        if ((choix !=0) && (choix != 1))
        {
            printf("Votre choix n'est pas egal a 0 ou 1\n");
            exit(ERREUR_SAISIE);
        }

        /* l'utilisateur depose un drapeau sur la case ou revele une case */
        choix_position (tableau, ligne, colonne, choix, N);

        if (choix==0)
        {
            decompte = decompte +1; // on augmente le decompte des mines de 1
        }

        if (tableau[ligne][colonne].minee == true && (choix==1))
        {
            perdu = true; // le joueur perd s'il choisit de reveler une case minee
        }

        condi_win = 0; // on re initialise condi_win a 0 a chaque tour de boucle

        for (int i=0; i<N; i++)
        {
            for (int j=0; j<N; j++)
            {
                if ((tableau[i][j].revelee == true) && (tableau[i][j].minee == false))
                {
                    condi_win ++; // on compte le nombre de cases vides revelees dans la grille
                }
            }
        }

        if (condi_win == N*N-nb_mines) // si ce decompte est egal au nombre total de cases vides
        {
            decompte = nb_mines; // alors on a decouvert toutes les bombes par elimination
        }

        // on affiche le tableau apres le choix et les modifications apportees

        printf("\n");
        printf("    ");
        for (int k=0; k<N; k++)
        {
            printf("  %d ", k);
        }
        printf("\n");
        for (int i=0; i<N; i++)
        {
            printf("    ");
            for (int l=0; l<N; l++)
            {
                printf("+---");
            }
            printf("+");
            printf("\n");
            printf("  %d ", i);
            for (int j=0; j<N; j++)
            {
                if ((tableau[i][j].revelee == false) && (tableau[i][j].drapeau == false))
                {
                    printf("| # ");
                }
                else if ((tableau[i][j].revelee == false) && (tableau[i][j].drapeau == true))
                {
                    printf("| D ");
                }
                else if((tableau[i][j].revelee == true) && (tableau[i][j].minee == false) && (tableau[i][j].mines_voisines != 0))
                {
                    printf("| %d ", tableau[i][j].mines_voisines);
                }
                else if((tableau[i][j].revelee == true) && (tableau[i][j].minee == false) && (tableau[i][j].mines_voisines == 0))
                {
                    printf("|   ");
                }
                else if((tableau[i][j].revelee == true) && (tableau[i][j].minee == true))
                {
                    printf("| ! ");
                }
            }
            printf("|");
            printf("\n");
        }
        printf("    ");
        for (int l=0; l<N; l++)
        {
            printf("+---");
        }
        printf("+");
        printf("\n");
        printf("     Mines : %d/%d", decompte, nb_mines);
        printf("\n\n");

        // l'utilisateur a perdu, on va sortir de la boucle, on affiche le message l'annoncant avant
        if (perdu==true)
        {
            printf("\nBOUM!!!!! Vous avez perdu...\n");
        }
        // de meme on va sortir de la boucle et on affiche le message que l'utilisateur a gagne
        else if (condi_win==N*N-nb_mines)
        {
            printf("\nVous avez gagne!!!!!!\n");
        }
    }

    // on libere la memoire allouee pour le tableau
    for (int j=0; j<N; j++)
    {
        free(tableau[j]);
    }
    free(tableau);

    return(0);
}