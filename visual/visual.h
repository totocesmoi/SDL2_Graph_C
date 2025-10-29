/**
 * @file visual.h
 * @brief Déclarations des fonctions de visualisation des algorithmes de tri.
 * @author MUZARD Thomas
 * @date 27/10/2025
 */

#ifndef VISUAL_H
#define VISUAL_H
// Include sorting types for VizCallback
#include "../sorting/sorting.h"

// Generic visualizer: takes a sorting function which accepts an array, its
// length and a VizCallback to report steps. The visualizer will create an
// SDL window and drive the callback to render each step.
void VisualizeSort(int tab[], int nbValue, void (*sortWithCb)(int[], int, VizCallback));

// Backward-compatible wrapper for bubble sort (uses instrumented bubble)
void VisualizeBubbleSort(int tab[], int nbValue);

// Settings: window size and delay between steps (milliseconds)
void SetVisualSize(int width, int height);
void SetVisualDelay(int delay_ms);

// Show a console settings page to let user choose preset window sizes
// and change the delay. This function returns after settings are applied.
void ShowSettingsMenu(void);
#endif // VISUAL_H