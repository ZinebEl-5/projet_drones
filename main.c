#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id;
    float x;
    float y;
    float z;
} Drone;

// distance entre 2 drones
float distance(Drone *a, Drone *b) {
    return sqrt(
        (a->x - b->x)*(a->x - b->x) +
        (a->y - b->y)*(a->y - b->y) +
        (a->z - b->z)*(a->z - b->z)
    );
}

int main() {
    int n = 5; // test

    Drone *essaim = (Drone *)malloc(n * sizeof(Drone));

    // remplir avec pointeurs (PAS DE [])
    for (int i = 0; i < n; i++) {
        (essaim + i)->id = i;
        (essaim + i)->x = rand() % 100;
        (essaim + i)->y = rand() % 100;
        (essaim + i)->z = rand() % 100;
    }

    // affichage
    for (int i = 0; i < n; i++) {
        printf("Drone %d: (%f, %f, %f)\n",
            (essaim + i)->id,
            (essaim + i)->x,
            (essaim + i)->y,
            (essaim + i)->z
        );
    }

    free(essaim);
    return 0;
}