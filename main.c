#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define DELIM ";"
#define BUFF_SIZE 128

typedef struct sommet
{
    char *nom;
    int altitude;
} Sommet;

typedef struct vec_sommet{
    Sommet * s;
    int nb_sommet;
} Vec_sommet_t;

typedef enum
{
    NOM,
    ALTITUDE,
    NB_CHAMPS
} Sommet_t;

typedef struct graph
{
    int nbs;
    int *vec;
} Graph_t;

Graph_t creegraphe(int nbs);
int voir(Graph_t g, int i, int j);
void placer(Graph_t g, int i, int j, int val);
void voirgraf(Graph_t g);
void print_tab2D(int **tab, int lin, int col);
Vec_sommet_t *alloc_sommet(const char *ccsv, const char *vcsv);

int main()
{
    Graph_t g = creegraphe(10);
    voirgraf(g);
    printf("Liste des cols et villes : \n");
    Vec_sommet_t * list_sommet = alloc_sommet("Docs/list_cols_alpes.csv", "Docs/list_ville_etapes.csv");
    int n = 0;
    printf("Nombre de sommets : %d \n", list_sommet->nb_sommet);
    while (n < list_sommet->nb_sommet)
    {
        printf("%3d\t%30s\t\t%6d m\n", n, list_sommet->s[n].nom, list_sommet->s[n].altitude);
        n++;
    }

    printf("\n");

    // voir(g, 9, 9);
    free(list_sommet);
    return 0;
}

Graph_t creegraphe(int nbs)
{
    int i, j, max, num;
    float v, taux;
    Graph_t g;
    g.nbs = nbs;
    max = nbs * nbs;
    taux = 25.0;
    num = nbs / 10;

    while (num > 1)
    {
        num /= 5;
        taux /= 3.0;
    }
    taux /= 100.0;
    printf("taux %g\n", taux);
    g.vec = (int *)malloc(max * sizeof(int));
    if (!g.vec)
        exit(1);
    memset(g.vec, 0, max);
    srand(time(NULL));
    for (num = 0, i = 0; i < nbs; i++)
    {
        for (j = 0; j < nbs; j++)
        {
            v = (float)rand() / RAND_MAX;
            g.vec[num++] = v < taux ? (int)(v * 1000.) : 0;
        }
    }
    return g;
}

void voirgraf(Graph_t g)
{
    int i, j, nb, num;
    nb = g.nbs;
    printf("Graphe\n");
    for (i = 0, num = 0; i < nb; i++)
    {
        for (j = 0; j < nb; j++)
            printf("%c ", g.vec[num++] ? '1' : ' ');
        printf("\n");
    }
}

/* Création et initialisation d'un pointeur de sommets à partir des csv */
Vec_sommet_t * alloc_sommet(const char *ccsv, const char *vcsv)
{
    Vec_sommet_t * vec = NULL; 
    FILE *fcol = NULL;
    FILE *fvil = NULL;
    char *token = NULL;
    char buff[BUFF_SIZE];
    int nb_ligne = 0;
    int row, colum, c, j;


    /* Ouverture de nos fichiers csv en lecture */
    fcol = fopen(ccsv, "r");
    fvil = fopen(vcsv, "r");

    if (!fcol && !fvil)
    {
        printf("Ouverture des fichiers impossible !");
        exit(0);
    }
    else
    {
        /* Compte le nb de ligne dans le fichier */
        while((c = fgetc(fcol)) != EOF)
        {
            if( c == '\n')
                nb_ligne++;
        }

        while ((c = fgetc(fvil)) != EOF)
        {
            if( c == '\n')
                nb_ligne++;
        }
        
        /* Replacer les pointeurs au début des fichiers */
        fseek(fcol, 0, SEEK_SET);
        fseek(fvil, 0, SEEK_SET);

        vec = (Vec_sommet_t*)malloc(sizeof(Vec_sommet_t));
        if(!vec) exit(0);
        vec->nb_sommet = nb_ligne;
        vec->s = (Sommet*)malloc(nb_ligne * sizeof(Sommet));
        if(!vec->s) exit(0);
        j = 0;

    
        while((fgets(buff, BUFF_SIZE, fcol)) != NULL)
        {

            char *p = buff;
            int i = 0;

            /* split la ligne par séparateur et renvoi le pointeur sur le 1er char de la lig. */
            while ((token = strtok(p, DELIM)) != NULL)
            {
                if (i == 0) p = NULL;
                switch (i)
                {
                case NOM:
                    vec->s[j].nom = strdup(token);
                    break;
                case ALTITUDE:
                    vec->s[j].altitude = strtol(token, NULL, 10);
                default:
                    break;
                }
                i++;
            }
            j++;
        }

        while((fgets(buff, BUFF_SIZE, fvil)) != NULL)
        {

            char *p = buff;
            int i = 0;

            /* split la ligne par séparateur et renvoi le pointeur sur le 1er char de la lig. */
            while ((token = strtok(p, DELIM)) != NULL)
            {
                if (i == 0) p = NULL;
                switch (i)
                {
                case NOM:
                    vec->s[j].nom = strdup(token);
                    break;
                case ALTITUDE:
                    vec->s[j].altitude = strtol(token, NULL, 10);
                default:
                    break;
                }
                i++;
            }
            j++;
        }
        fclose(fcol);
        fclose(fvil);
    }
    return vec;
}
