/**
 * @file utils.h
 * @brief Déclarations des fonctions utilitaires pour le projet de visualisation des algorithmes de tri.
 * @author MUZARD Thomas
 * @date 27/10/2025
 */

#ifndef UTILS_H
#define UTILS_H

// Fonction pour l'échantillon de test
void FreeTabSample();
void LoadSample();

// Fonction pour les paramètres de la visualisation
void SetVisualSize(int width, int height);
void SetVisualDelay(int delay_ms);

int GetVisualWidth();
int GetVisualHeight();
int GetVisualDelay();

// Fonction utilitaires
void ChooseAlgorithm(int idxAlgo);
void ShowSettingsMenu();
void ShowShuffleMenu();
void PrintTab(int tab[], int n);
void ShuffleSample(int type);

#endif // UTILS_H
