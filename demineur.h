#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define ERREUR_SAISIE -1

typedef struct CASE
{
    bool minee; /*!< case minee */
    bool drapeau; /*!< case avec un drapeau */
    bool revelee; /*!< case revelee */
    int mines_voisines; /*!< nombre de mines voisines */
} Case;

void initialisation (Case** tableau, int N);
void tirage_alea (Case** tableau, int N, int nb_mines);
void mines_voisines (Case** tableau, int N);
void decouvrement (Case** tableau, int ligne, int colonne, int N);
int choix_position (Case** tableau, int ligne, int colonne, int choix, int N);