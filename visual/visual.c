#include "visual.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/utils.h"
#include "../sorting/sorting.h"

/**
 * @file visual.c
 * @brief Implémentation des fonctions de visualisation des algorithmes de tri.
 * @author MUZARD Thomas
 * @date 27/10/2025
 */

 /**
  * @brief Rendu du tableau sous forme de barres verticales.
  * 
  * @param renderer Le renderer SDL.
  * @param tab Le tableau à afficher.
  * @param nbValue Le nombre d'éléments dans le tableau.
  * @param highlight_a Indice du premier élément à mettre en évidence.
  * @param highlight_b Indice du second élément à mettre en évidence.
  */
static void render_array(SDL_Renderer *renderer, int tab[], int nbValue, int highlight_a, int highlight_b) {
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    // find max value
    int maxvalue = 1;
    for (int i = 0; i < nbValue; ++i) {
        if (tab[i] > maxvalue) {
            maxvalue = tab[i];
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int bar_width = width / (nbValue > 0 ? nbValue : 1);
    for (int i = 0; i < nbValue; ++i) {
        float normalized = (float)tab[i] / (float)maxvalue;
        int bar_height = (int)(normalized * (height - 20)); // margin

        SDL_Rect bar;
        bar.x = i * bar_width;
        bar.w = bar_width > 1 ? bar_width - 1 : 1; // small gap
        bar.y = height - bar_height;
        bar.h = bar_height;

        if (i == highlight_a || i == highlight_b) {
            SDL_SetRenderDrawColor(renderer, 220, 40, 40, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        }

        SDL_RenderFillRect(renderer, &bar);
    }

    SDL_RenderPresent(renderer);
}

/**
 * @brief Renderer SDL global pour la visualisation.
 */
static SDL_Renderer *graph_renderer = NULL;
/**
 * @brief Indicateur d'exécution de la boucle principale de visualisation.
 */
static int graph_running = 0;
/**
 * @brief Indicateur de pause de la visualisation.
 */
static int graph_paused = 0;

/**
 * @brief Callback de visualisation appelé par les algorithmes de tri instrumentés.
 * 
 * @param tab Le tableau en cours de tri.
 * @param nbValue Le nombre d'éléments dans le tableau.
 * @param a Indice du premier élément à mettre en évidence.
 * @param b Indice du second élément à mettre en évidence.
 */
static void viz_callback(int tab[], int nbValue, int a, int b) {
    if (!graph_renderer) return;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) { graph_running = 0; return; }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE)
                graph_paused = !graph_paused;
            if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE) {
                graph_running = 0;
                return;
            }
        }
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            render_array(graph_renderer, tab, nbValue, a, b);
        }
    }

    while (graph_paused && graph_running) {
        SDL_Event event2;
        while (SDL_WaitEvent(&event2)) {
            if (event2.type == SDL_QUIT) {
                graph_running = 0;
                return;
            }
            if (event2.type == SDL_KEYDOWN) {
                if (event2.key.keysym.sym == SDLK_SPACE) {
                    graph_paused = 0;
                    break;
                }
                if (event2.key.keysym.sym == SDLK_q || event2.key.keysym.sym == SDLK_ESCAPE) {
                    graph_running = 0;
                    return;
                }
            }
        }
    }

    render_array(graph_renderer, tab, nbValue, a, b);
    SDL_Delay(GetVisualDelay());
}

/**
 * @brief Fonction principale de visualisation d'un algorithme de tri.
 * 
 * @param tab Le tableau à trier.
 * @param nbValue Le nombre d'éléments dans le tableau.
 * @param sortWithCb Pointeur vers la fonction de tri instrumentée à utiliser.
 */
void VisualizeSort(int tab[], int nbValue, void (*sortWithCb)(int[], int, VizCallback)) {
    if (nbValue <= 0) return;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    int win_w = GetVisualWidth();
    int win_h = GetVisualHeight();

    SDL_Window *win = SDL_CreateWindow("Sort Visualizer",
                                       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       win_w, win_h,
                                       SDL_WINDOW_RESIZABLE);
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    g_renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g_renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        g_renderer = NULL;
        return;
    }

    g_running = 1;
    g_paused = 0;

    // Initial render
    render_array(g_renderer, tab, nbValue, -1, -1);

    // Run the provided instrumented sort which will call viz_callback
    if (sortWithCb) {
        sortWithCb(tab, nbValue, viz_callback);
    }

    // final render
    render_array(g_renderer, tab, nbValue, -1, -1);

    // wait until user closes or presses q/escape
    while (g_running) {
        SDL_Event e;
        while (SDL_WaitEvent(&e)) {
            if (e.type == SDL_QUIT) { g_running = 0; break; }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE) { g_running = 0; break; }
            }
            if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                render_array(g_renderer, tab, nbValue, -1, -1);
            }
        }
    }

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    g_renderer = NULL;
}

/**
 * @brief Fonctions de visualisation spécifiques pour chaque algorithme de tri, plus précisément pour le trie à bulle.
 * 
 * @param tab Le tableau à trier.
 * @param nbValue Le nombre d'éléments dans le tableau.
 */
void VisualizeBubbleSort(int tab[], int nbValue) {
    VisualizeSort(tab, nbValue, BubbleSort_viz);
}

/**
 * @brief Fonctions de visualisation spécifiques pour chaque algorithme de tri, plus précisément pour le trie par sélection.
 * 
 * @param tab Le tableau à trier.
 * @param nbValue Le nombre d'éléments dans le tableau.
 */
void VisualizeSelectSort(int tab[], int nbValue) {
    VisualizeSort(tab, nbValue, SelectSort_viz);
}

/**
 * @brief Fonctions de visualisation spécifiques pour chaque algorithme de tri, plus précisément pour le trie par insertion.
 * 
 * @param tab Le tableau à trier.
 * @param nbValue Le nombre d'éléments dans le tableau.
 */
void VisualizeInsertionSort(int tab[], int nbValue) {
    VisualizeSort(tab, nbValue, InsertionSort_viz);
}

/**
 * @brief Fonctions de visualisation spécifiques pour chaque algorithme de tri, plus précisément pour le trie rapide.
 * 
 * @param tab Le tableau à trier.
 * @param nbValue Le nombre d'éléments dans le tableau.
 */
void VisualizeQuickSort(int tab[], int nbValue) {
    VisualizeSort(tab, nbValue, QuickSort_viz_wrapper);
}

/**
 * @brief Fonctions de visualisation spécifiques pour chaque algorithme de tri, plus précisément pour le trie fusion.
 * 
 * @param tab Le tableau à trier.
 * @param nbValue Le nombre d'éléments dans le tableau.
 */
void VisualizeMergeSort(int tab[], int nbValue) {
    VisualizeSort(tab, nbValue, MergeSort_viz_wrapper);
}

