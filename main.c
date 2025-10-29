#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting/sorting.h"
#include "visual/visual.h"
#include "utils/utils.h"
#include "stats/stats.h"


int main() {
    int idxAlgo = 0;
    LoadSample();

    while (idxAlgo != 9) {
        printf("Choose sorting algorithm:\n\t1 - SelectSort\n\t2 - BubbleSort\n\t3 - InsertionSort\n\t4 - QuickSort\n\t5 - MergeSort\n\t6 - Settings\n\t9 - Exit\n");
        scanf(" %d", &idxAlgo);

        while ((idxAlgo < 1 || idxAlgo > 6) && idxAlgo != 9) {
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            scanf(" %d", &idxAlgo);
        }

        if (idxAlgo == 9) {
            break;
        }

        if (idxAlgo < 1 || idxAlgo > 6) {
            printf("%d is not a valid choice. Please enter your choice.\n", idxAlgo);
            continue;
        }

        ChooseAlgorithm(idxAlgo);
    }

    // Free the allocated memory
    FreeTabSample();
    return 0;
}
