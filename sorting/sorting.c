#include "sorting.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Tri par sélection. Il va chercher l'élément minimum dans le tableau non trié et le place au début.
 *
 * @param tab Tableau à trier.
 * @param n Nombre d'éléments dans le tableau.
 */
void SelectSort(int tab[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int index = i;
        for (int j = i + 1; j < n; j++) {
            if (tab[j] < tab[index]) {
                index = j;
            }
        }
        if (index != i) {
            int temp = tab[i];
            tab[i] = tab[index];
            tab[index] = temp;
        }
    }

    PrintTab(tab, n);
}

/**
 * @brief Tri à bulles. Il compare chaque paire d'éléments adjacents et les échange s'ils sont supérieurs ou inférieurs entre eux.
 * 
 * @param tab Tableau à trier.
 * @param n Nombre d'éléments dans le tableau.
 */
void BubbleSort(int tab[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }

    PrintTab(tab, n);
}

/**
 * @brief Tri par insertion. Il construit le tableau trié un élément à la fois en insérant chaque nouvel élément à sa position correcte.
 * 
 * @param tab Tableau à trier.
 * @param n Nombre d'éléments dans le tableau.
 */
void InsertionSort(int tab[], int n) {
    for (int i = 1; i < n; i++) {
        int key = tab[i];
        int j = i - 1;
        while (j >= 0 && tab[j] > key) {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = key;
    }

    PrintTab(tab, n);
}

/**
 * @brief Tri rapide (QuickSort). Il utilise la méthode du pivot pour diviser le tableau en sous-tableaux.
 * 
 * @param tab Tableau à trier.
 * @param low Indice de début.
 * @param high Indice de fin.
 */
void QuickSort(int tab[], int low, int high) {
    if (low < high) {
        int pivot = tab[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (tab[j] < pivot) {
                i++;
                int temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
        int temp = tab[i + 1];
        tab[i + 1] = tab[high];
        tab[high] = temp;
        int pi = i + 1;

        QuickSort(tab, low, pi - 1);
        QuickSort(tab, pi + 1, high);
    }

    PrintTab(tab, high - low + 1);
}

/**
 * @brief Fusionne deux sous-tableaux pour le tri par fusion.
 * 
 * @param tab Tableau à trier.
 * @param left Indice de début.
 * @param mid Indice du milieu.
 * @param right Indice de fin.
 */
void Merge(int tab[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = tab[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = tab[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            tab[k] = L[i];
            i++;
        } else {
            tab[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        tab[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        tab[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

/**
 * @brief Tri par fusion (MergeSort). Il divise le tableau en deux moitiés, trie chaque moitié et les fusionne.
 * 
 * @param tab Tableau à trier.
 * @param left Indice de début.
 * @param right Indice de fin.
 */
void MergeSort(int tab[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSort(tab, left, mid);
        MergeSort(tab, mid + 1, right);

        Merge(tab, left, mid, right);
    }

    PrintTab(tab, right - left + 1);
}


// ------------------------- Versions instrumentées -------------------------
// Se sont les même fonctions que précédemment, mais avec un callback de visualisation.
// afin d'afficher les comparaisons et les échanges de positions pas à pas.
// Cela me permet d'utiliser une méthode de visualisation générique pour tous les algorithmes de tri, 
// en passant la fonction de tri appropriée en paramètre.
// M'évitant de dupliquer le code de gestion de la fenêtre SDL et du rendu graphique pour chaque algorithme de tri.

/**
 * @brief Tri par sélection prévue pour la visualisation.
 * 
 * @param tab Tableau à trier.
 * @param n Nombre d'éléments dans le tableau.
 * @param cb Callback de visualisation.
 */
void SelectSort_viz(int tab[], int n, VizCallback cb) {
    for (int i = 0; i < n - 1; i++) {
        int index = i;
        for (int j = i + 1; j < n; j++) {
            if (cb) cb(tab, n, index, j); // show comparison
            if (tab[j] < tab[index]) {
                index = j;
            }
        }
        if (index != i) {
            int temp = tab[i];
            tab[i] = tab[index];
            tab[index] = temp;
            if (cb) cb(tab, n, i, index); // show swap
        }
    }
}

/**
 * @brief Tri à bulles prévu pour la visualisation.
 * 
 * @param tab Tableau à trier.
 * @param n Nombre d'éléments dans le tableau.
 * @param cb Callback de visualisation.
 */
void BubbleSort_viz(int tab[], int n, VizCallback cb) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (cb) 
                cb(tab, n, j, j+1); // comparison
            if (tab[j] > tab[j + 1]) {
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
                if (cb) 
                    cb(tab, n, j, j+1); // swap
            }
        }
    }
}

/**
 * @brief Tri par insertion prévu pour la visualisation.
 * 
 * @param tab Tableau à trier.
 * @param n Nombre d'éléments dans le tableau.
 * @param cb Callback de visualisation.
 */
void InsertionSort_viz(int tab[], int n, VizCallback cb) {
    for (int i = 1; i < n; i++) {
        int key = tab[i];
        int j = i - 1;
        while (j >= 0) {
            if (cb) cb(tab, n, j, i);
            if (tab[j] > key) {
                tab[j + 1] = tab[j];
                j--;
                if (cb) cb(tab, n, j+1, j+2);
            } else {
                break;
            }
        }
        tab[j + 1] = key;
        if (cb) cb(tab, n, j+1, i);
    }
}

/**
 * @brief Fonction récursive de tri rapide prévue pour la visualisation. La méthode permet de garder la taille totale du tableau pour le callback de visualisation.
 * 
 * @param tab Tableau à trier.
 * @param low Indice de début.
 * @param high Indice de fin.
 * @param total_n Taille totale du tableau pour le callback.
 * @param cb Callback de visualisation.
 */
static void QuickSort_viz_rec(int tab[], int low, int high, int total_n, VizCallback cb) {
    if (low < high) {
        int pivot = tab[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (cb) cb(tab, total_n, j, high);
            if (tab[j] < pivot) {
                i++;
                int temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
                if (cb) cb(tab, total_n, i, j);
            }
        }
        int temp = tab[i + 1];
        tab[i + 1] = tab[high];
        tab[high] = temp;
        if (cb) cb(tab, total_n, i+1, high);

        QuickSort_viz_rec(tab, low, i - 0, total_n, cb);
        QuickSort_viz_rec(tab, i + 2, high, total_n, cb);
    }
}

/**
 * @brief Tri rapide prévu pour la visualisation.
 * 
 * @param tab Tableau à trier.
 * @param debut Indice de début.
 * @param fin Indice de fin.
 */
void QuickSort_viz(int tab[], int debut, int fin, VizCallback cb) {
    // Not used directly for wrapper; keep signature for compatibility.
    QuickSort_viz_rec(tab, debut, fin, fin - debut + 1, cb);
}

/**
 * @brief Wrapper pour le tri rapide prévu pour la visualisation.
 * 
 * @param tab Tableau à trier.
 * @param n Nombre d'éléments dans le tableau.
 * @param cb Callback de visualisation.
 */
void QuickSort_viz_wrapper(int tab[], int n, VizCallback cb) {
    QuickSort_viz_rec(tab, 0, n - 1, n, cb);
}

/**
 * @brief Fusionne deux sous-tableaux pour le tri par fusion prévu pour la visualisation.
 * 
 * @param tab Tableau à trier.
 * @param gauche Indice de début.
 * @param centre Indice du milieu.
 * @param droite Indice de fin.
 * @param total_n Taille totale du tableau pour le callback.
 * @param cb Callback de visualisation.
 */
static void Merge_viz(int tab[], int gauche, int centre, int droite, int total_n, VizCallback cb) {
    int n1 = centre - gauche + 1;
    int n2 = droite - centre;

    int* Gauche = (int*)malloc(n1 * sizeof(int));
    int* Droite = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        Gauche[i] = tab[gauche + i];
    for (int j = 0; j < n2; j++)
        Droite[j] = tab[centre + 1 + j];

    int i = 0;
    int j = 0;
    int k = gauche;
    while (i < n1 && j < n2) {
        if (cb) cb(tab, total_n, k, centre+1+j);
            if (Gauche[i] <= Droite[j]) {
                tab[k] = Gauche[i];
                i++;
            } else {
                tab[k] = Droite[j];
                j++;
            }
        if (cb) 
            cb(tab, total_n, k, k);
        k++;
    }

    while (i < n1) {
        tab[k] = Gauche[i];
        i++;
        k++;
        if (cb) 
            cb(tab, total_n, k-1, k-1);
    }

    while (j < n2) {
        tab[k] = Droite[j];
        j++;
        k++;
    if (cb) 
        cb(tab, total_n, k-1, k-1);
    }

    free(Gauche);
    free(Droite);
}

/**
 * @brief Fonction récursive de tri par fusion prévue pour la visualisation. La méthode permet de garder la taille totale du tableau pour le callback de visualisation.
 * 
 * @param tab Tableau à trier.
 * @param gauche Indice de début.
 * @param droite Indice de fin.
 * @param total_n Taille totale du tableau pour le callback.
 * @param cb Callback de visualisation.
 */
static void MergeSort_viz_rec(int tab[], int gauche, int droite, int total_n, VizCallback cb) {
    if (gauche < droite) {
        int centre = gauche + (droite - gauche) / 2;

        MergeSort_viz_rec(tab, gauche, centre, total_n, cb);
        MergeSort_viz_rec(tab, centre + 1, droite, total_n, cb);

        Merge_viz(tab, gauche, centre, droite, total_n, cb);
    }
}

/**
 * @brief Tri par fusion prévu pour la visualisation.
 * 
 * @param tab Tableau à trier.
 * @param n Nombre d'éléments dans le tableau.
 * @param cb Callback de visualisation.
 */
void MergeSort_viz_wrapper(int tab[], int n, VizCallback cb) {
    MergeSort_viz_rec(tab, 0, n - 1, n, cb);
}








