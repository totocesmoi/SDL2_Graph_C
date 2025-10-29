#include "utils.h"
#include "../sorting/sorting.h"
#include "../visual/visual.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file utils.c
 * @brief Implémentation des fonctions utilitaires pour le projet de visualisation des algorithmes de tri.
 * @author MUZARD Thomas
 * @date 27/10/2025
 */

 /**
  * @brief Taille de l'échantillon de test.
  */
static int sampleSize = 100;

/**
 * @brief Type de mélange avant le tri.
 */
static int typeShuffleBeforeSort = 1;

/**
 * @brief Tableau d'échantillon de test.
 */
static int* tab = NULL;

/**
 * @brief Largeur de la fenêtre de visualisation.
 */
static int viz_width = 800;

/**
 * @brief Hauteur de la fenêtre de visualisation.
 */
static int viz_height = 600;

/**
 * @brief Délai de visualisation (en millisecondes).
 */
static int viz_delay_ms = 1; // delay for comparisons/swaps

/**
 * @brief Libère la mémoire allouée pour l'échantillon de test.
 */
void FreeTabSample() {
    if (tab != NULL) {
        free(tab);
        tab = NULL;
    }
}

/**
 * @brief Charge ou initialise l'échantillon de test.
 */
void LoadSample() {
    if (tab == NULL) {
        tab = (int*)malloc(sampleSize * sizeof(int));
        if (tab == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
    }

    int *tmp = realloc(tab, sampleSize * sizeof(int));
    if (tmp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    tab = tmp;

    /* Initialiser avec 1..sampleSize avant de mélanger */
    for (int i = 0; i < sampleSize; ++i) {
        tab[i] = i + 1;
    }

    ShuffleSample(typeShuffleBeforeSort);
}

/**
 * @brief Setteur de la taille de fenêtre pour la visualisation.
 * 
 * @param width Largeur en pixels.
 * @param height Hauteur en pixels.
 */
void SetVisualSize(int width, int height) {
    if (width > 0) viz_width = width;
    if (height > 0) viz_height = height;
}

/**
 * @brief Setteur du délai de visualisation.
 * 
 * @param delay_ms Délai en millisecondes.
 */
void SetVisualDelay(int delay_ms) {
    if (delay_ms >= 0) viz_delay_ms = delay_ms;
}

/**
 * @brief Getteur de la largeur de la fenêtre de visualisation.
 */
int GetVisualWidth(void) {
    return viz_width;
}

/**
 * @brief Getteur de la hauteur de la fenêtre de visualisation.
 */
int GetVisualHeight(void) {
    return viz_height;
}

/**
 * @brief Getteur du délai de visualisation.
 */
int GetVisualDelay(void) {
    return viz_delay_ms;
}

/**
 * @brief Mélange aléatoire du tableau.
 * 
 * @param tab Le tableau à mélanger.
 * @param n La taille du tableau.
 */
void RandomShuffle(int tab[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = tab[i];
        tab[i] = tab[j];
        tab[j] = temp;
    }
}

/**
 * @brief Rend le tableau presque trié en mélangeant une petite partie des éléments.
 * 
 * @param tab Le tableau à modifier.
 * @param n La taille du tableau.
 */
void NearlySorted(int tab[], int n) {
    RandomShuffle(tab, n / 10); // Shuffle 10% of the elements
}

/**
 * @brief Rend le tableau trié en ordre décroissant.
 * 
 * @param tab Le tableau à modifier.
 * @param n La taille du tableau.
 */
void ReverseSorted(int tab[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = tab[i];
        tab[i] = tab[n - i - 1];
        tab[n - i - 1] = temp;
    }
}

/**
 * @brief Remplit le tableau avec des valeurs triées en ordre croissant.
 * 
 * @param tab Le tableau à modifier.
 * @param n La taille du tableau.
 */
void Sorted(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = i + 1;
    }
}

/**
 * @brief Mélange le tableau selon le type spécifié.
 * 
 * @param type Type de mélange (1: aléatoire, 2: presque trié, 3: trié en ordre décroissant, 4: trié en ordre croissant).
 */
void ShuffleSample(int type) {
    switch (type)
    {
        case 1:
            // Simple random shuffle
            RandomShuffle(tab, sampleSize);
            break;

        case 2:
            // Nearly sorted
            NearlySorted(tab, sampleSize);
            break;

        case 3:
            // Reverse sorted
            ReverseSorted(tab, sampleSize);
            break;

        case 4:
            // Sorted
            Sorted(tab, sampleSize);
            break;
        
        default:
            break;
    }
}

/**
 * @brief Choisit et exécute l'algorithme de tri spécifié.
 * 
 * @param idxAlgo Indice de l'algorithme de tri à exécuter choisie par l'utilisateur.
 */
void ChooseAlgorithm(int idxAlgo) {
    switch (idxAlgo) {
        case 1:
            //SelectSort(tab, sampleSize);
            ShuffleSample(typeShuffleBeforeSort);
            VisualizeSort(tab, sampleSize, SelectSort_viz);
            break;

        case 2: 
            //BubbleSort(tab, sampleSize);
            ShuffleSample(typeShuffleBeforeSort);
            VisualizeSort(tab, sampleSize, BubbleSort_viz);
            break;

        case 3:
            //InsertionSort(tab, sampleSize);
            ShuffleSample(typeShuffleBeforeSort);
            VisualizeSort(tab, sampleSize, InsertionSort_viz);
            break;

        case 4:
            //QuickSort(tab, 0, sampleSize - 1);
            ShuffleSample(typeShuffleBeforeSort);
            VisualizeSort(tab, sampleSize, QuickSort_viz_wrapper);
            break;

        case 5:
            //MergeSort(tab, 0, sampleSize - 1);
            ShuffleSample(typeShuffleBeforeSort);
            VisualizeSort(tab, sampleSize, MergeSort_viz_wrapper);
            break;

        case 6:
            // Changer les paramètres de visualisation
            ShowSettingsMenu();
            break;

        case 9:
            printf("Exiting the sorting program.\n");
            break;
        
        default:
            printf("Unknown sorting algorithm: %d\n", idxAlgo);
    }
}

/**
 * @brief Imprime le contenu du tableau.
 * 
 * @param tab Le tableau à imprimer.
 * @param n La taille du tableau.
 */
void PrintTab(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

/**
 * @brief Affiche le menu des paramètres de visualisation et permet à l'utilisateur de les modifier.
 */
void SetDelay() {
    int d;
    printf("Enter delay in ms (0 for very fast): "); 
    if (scanf("%d", &d) != 1) { 
        int c; 
        while ((c = getchar()) != '\n' && c != EOF) {} 
        printf("Bad input\n"); 
    }
    SetVisualDelay(d);
}

/**
 * @brief Permet à l'utilisateur de définir une taille de fenêtre personnalisée.
 */
void SetViewSize() {
    int w, h;
    printf("Enter width: "); 
    if (scanf("%d", &w) != 1) { 
        int c; 
        while ((c = getchar()) != '\n' && c != EOF) {} 
        printf("Bad input\n"); 
    }

    printf("Enter height: "); 
    if (scanf("%d", &h) != 1) { 
        int c; 
        while ((c = getchar()) != '\n' && c != EOF) {} 
        printf("Bad input\n"); 
    }

    SetVisualSize(w, h);
}

/**
 * @brief Permet à l'utilisateur de définir la taille de l'échantillon de test.
 */
void SetTabSample() {
    printf("Enter sample size: "); 
    scanf("%d", &sampleSize);
    while (sampleSize <= 0) {
        printf("Sample size must be positive. Please enter again: ");
        scanf("%d", &sampleSize);
    }

    LoadSample();
}

/**
 * @brief Permet à l'utilisateur de définir le type de mélange avant le tri.
 */
void SetShuffleType() {
    printf("Choose type of shuffle before sort:\n");
    printf(" 1 - Simple random shuffle\n");
    printf(" 2 - Nearly sorted\n");
    printf(" 3 - Reverse sorted\n");
    printf(" 4 - Sorted\n");
    printf("Your choice: ");
    scanf("%d", &typeShuffleBeforeSort);

    while (typeShuffleBeforeSort < 1 || typeShuffleBeforeSort > 4) {
        printf("Invalid choice. Please enter again: ");
        scanf("%d", &typeShuffleBeforeSort);
    }
}

/**
 * @brief Affiche le menu des paramètres de visualisation et permet à l'utilisateur de les modifier.
 */
void ShowSettingsMenu(void) {
    int done = 0;
    while (!done) {
        printf("\n=== Visualizer Settings ===\n");
        printf("Current size: %dx%d\n", viz_width, viz_height);
        printf("Current delay: %d ms\n", viz_delay_ms);
        printf("Choose an option:\n");
        printf(" 1 - 640 x 480\n");
        printf(" 2 - 800 x 600\n");
        printf(" 3 - 1024 x 768\n");
        printf(" 4 - 1280 x 720\n");
        printf(" 5 - Custom size\n");
        printf(" 6 - Change delay (ms)\n");
        printf(" 7 - Change sample size\n");
        printf(" 8 - Change type of shuffle\n");
        printf(" 9 - Back\n");
        printf("Your choice: ");

        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input\n");
            continue;
        }

        switch (choice) {
            case 1: 
                SetVisualSize(640, 480); 
                break;

            case 2: 
                SetVisualSize(800, 600); 
                break;

            case 3: 
                SetVisualSize(1024, 768); 
                break;

            case 4: 
                SetVisualSize(1280, 720); 
                break;

            case 5: 
                SetViewSize();
                break;
            
            case 6:
                SetDelay();
                break;

            case 7: 
                SetTabSample();
                break;

            case 8 : 
                SetShuffleType();
                break;

            case 9: 
                done = 1; 
                break;

            default: 
                printf("Unknown option\n"); break;
        }
    }
}