#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    int id;
    float x;
    float y;
    float z;
} Drone;

/* =====================================================
   Calcul de la distance entre deux drones
===================================================== */
float distanceDrone(Drone *a, Drone *b) {

    return sqrt(
        (a->x - b->x) * (a->x - b->x) +
        (a->y - b->y) * (a->y - b->y) +
        (a->z - b->z) * (a->z - b->z)
    );
}

/* =====================================================
   Déplacement aléatoire d’un drone
===================================================== */
void deplacerDrone(Drone *d) {

    d->x += (rand() % 11) - 5;
    d->y += (rand() % 11) - 5;
    d->z += (rand() % 11) - 5;
}

/* =====================================================
   Affichage d’un drone
===================================================== */
void afficherDrone(Drone *d) {

    printf(
        "Drone %d -> (%.2f, %.2f, %.2f)\n",
        d->id,
        d->x,
        d->y,
        d->z
    );
}

/* =====================================================
   Tri des drones selon la coordonnée x
   (Tri à bulles avec pointeurs uniquement)
===================================================== */
void trierParX(Drone *essaim, int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if ((essaim + j)->x > (essaim + j + 1)->x) {

                Drone temp;

                temp = *(essaim + j);
                *(essaim + j) = *(essaim + j + 1);
                *(essaim + j + 1) = temp;
            }
        }
    }
}

/* =====================================================
   Recherche des deux drones les plus proches
===================================================== */
void trouverPlusProches(Drone *essaim, int n) {

    float minDistance = 999999.0;

    Drone *drone1 = NULL;
    Drone *drone2 = NULL;

    /* ---------------------------------------------
       Comparaison des drones voisins après tri
    ---------------------------------------------- */
    for (int i = 0; i < n - 1; i++) {

        float d = distanceDrone(
            essaim + i,
            essaim + i + 1
        );

        printf(
            "Drone %d <-> Drone %d = %.2f\n",
            (essaim + i)->id,
            (essaim + i + 1)->id,
            d
        );

        if (d < minDistance) {

            minDistance = d;

            drone1 = essaim + i;
            drone2 = essaim + i + 1;
        }
    }

    /* ---------------------------------------------
       Affichage du résultat final
    ---------------------------------------------- */
    printf("\n====================================\n");
    printf("DRONES LES PLUS PROCHES :\n");

    printf(
        "Drone %d et Drone %d\n",
        drone1->id,
        drone2->id
    );

    printf(
        "Distance minimale = %.2f\n",
        minDistance
    );

    /* ---------------------------------------------
       Alerte collision
    ---------------------------------------------- */
    if (minDistance < 10) {

        printf("!!! ALERTE COLLISION !!!\n");
    }

    printf("====================================\n");
}

/* =====================================================
   Programme principal
===================================================== */
int main() {

    srand(time(NULL));

    int n = 10;

    /* ---------------------------------------------
       Allocation dynamique mémoire
    ---------------------------------------------- */
    Drone *essaim = (Drone *)malloc(
        n * sizeof(Drone)
    );

    /* Vérification malloc */
    if (essaim == NULL) {

        printf("Erreur allocation mémoire\n");
        return 1;
    }

    /* ---------------------------------------------
       Initialisation des drones
    ---------------------------------------------- */
    for (int i = 0; i < n; i++) {

        (essaim + i)->id = i + 1;

        (essaim + i)->x = rand() % 100;
        (essaim + i)->y = rand() % 100;
        (essaim + i)->z = rand() % 100;
    }

    /* =============================================
       Simulation sur plusieurs tours
    ============================================== */
    for (int tour = 1; tour <= 5; tour++) {

        printf(
            "\n=========== TOUR %d ===========\n",
            tour
        );

        /* -----------------------------------------
           Déplacement des drones
        ------------------------------------------ */
        for (int i = 0; i < n; i++) {

            deplacerDrone(essaim + i);
        }

        /* -----------------------------------------
           Tri des drones
        ------------------------------------------ */
        trierParX(essaim, n);

        /* -----------------------------------------
           Affichage des drones triés
        ------------------------------------------ */
        printf("\nDrones apres tri :\n");

        for (int i = 0; i < n; i++) {

            afficherDrone(essaim + i);
        }

        /* -----------------------------------------
           Recherche des drones les plus proches
        ------------------------------------------ */
        printf("\nDistances entre voisins :\n");

        trouverPlusProches(essaim, n);
    }

    /* ---------------------------------------------
       Libération mémoire
    ---------------------------------------------- */
    free(essaim);

    return 0;
}