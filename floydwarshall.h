#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H

#include "graphe.h"
//////////////////////////////////////
// Algorithme de Floyd Marshall
//   - Structure Matrice Adjacente
//             //
//////////////////////////////////////

#define INF 999999
#define MAXMAT 256
#define MIN(a,b) ((a) < (b) ? (a) : (b))
typedef int matrice[MAXMAT][MAXMAT];

typedef struct mat
{
    int nbs;
    matrice mat;
} Mat;


typedef struct path
{
    int size;
    int * path;
} Path;


void floydwarshall(Mat *m, Mat * pred);
void init_matrice(Graphe *grph, Mat *m, Mat * pred);
void print_matrice2D(Mat *m, int lin, int col, int digit);
void print_vector(int *vec, int nb);
void itineraryAtoB(Mat *pred, int src, int dst, Graphe *grph, Path *p);
void print_itinerary(Graphe * grph,Path * p, int src, int dst);
int elevation_gain(Graphe *grph, Mat * pred, Path * p);
void ecrirePlusCourt(Graphe *graphe, Mat * m, Mat * pred);
void ecrirePlusCourtUnChemin(Graphe *graphe, Mat *m, Mat *pred, int src);
void ecrireEtape(Mat *a, Mat *p, int k, int ns);


#endif // FLOYDWAGraphe_H
