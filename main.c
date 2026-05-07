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

// distance entre 2 drones
float distanceDrone(Drone *a, Drone *b) {
    return sqrt(
        (a->x - b->x)*(a->x - b->x) +
        (a->y - b->y)*(a->y - b->y) +
        (a->z - b->z)*(a->z - b->z)
    );
}

// déplacement aléatoire
void deplacerDrone(Drone *d) {
    d->x += (rand() % 11) - 5;
    d->y += (rand() % 11) - 5;
    d->z += (rand() % 11) - 5;
}

// affichage
void afficherDrone(Drone *d) {
    printf("Drone %d -> (%.2f, %.2f, %.2f)\n",
           d->id,
           d->x,
           d->y,
           d->z);
}

int main() {

    srand(time(NULL));

    int n = 5;

    Drone *essaim = (Drone *)malloc(n * sizeof(Drone));

    // initialisation
    for (int i = 0; i < n; i++) {

        (essaim + i)->id = i + 1;
        (essaim + i)->x = rand() % 100;
        (essaim + i)->y = rand() % 100;
        (essaim + i)->z = rand() % 100;
    }

    // simulation
    for (int tour = 1; tour <= 5; tour++) {

        printf("\n===== TOUR %d =====\n", tour);

        // déplacement + affichage
        for (int i = 0; i < n; i++) {

            deplacerDrone(essaim + i);
            afficherDrone(essaim + i);
        }

        // distances
        printf("\nDistances entre drones :\n");

        for (int i = 0; i < n; i++) {

            for (int j = i + 1; j < n; j++) {

                float d = distanceDrone(
                    essaim + i,
                    essaim + j
                );

                printf("Drone %d <-> Drone %d = %.2f\n",
                       (essaim + i)->id,
                       (essaim + j)->id,
                       d);

                // collision
                if (d < 10) {
                    printf("!!! ALERTE COLLISION !!!\n");
                }
            }
        }
    }

    free(essaim);

    return 0;
}