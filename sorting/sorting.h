/**
 * @file sorting/sorting.h
 * @brief Déclarations des algorithmes de tri et des versions instrumentées pour la visualisation.
 * @author MUZARD Thomas
 * @date 27/10/2025
 */

#ifndef SORTING_H

#define SORTING_H

// Simple (silent) algorithms
void SelectSort(int arr[], int n);
void BubbleSort(int arr[], int n);
void InsertionSort(int arr[], int n);
void QuickSort(int arr[], int low, int high);
void MergeSort(int arr[], int left, int right);

// Instrumentation callback used for visualization: highlight indices a and b.
typedef void (*VizCallback)(int arr[], int n, int a, int b);

// Instrumented algorithms that call the VizCallback at comparisons / swaps.
void SelectSort_viz(int arr[], int n, VizCallback cb);
void BubbleSort_viz(int arr[], int n, VizCallback cb);
void InsertionSort_viz(int arr[], int n, VizCallback cb);
void QuickSort_viz(int arr[], int low, int high, VizCallback cb); // low/high version keeps compatibility
void QuickSort_viz_wrapper(int arr[], int n, VizCallback cb); // wrapper matching (arr,n,cb)
void MergeSort_viz(int arr[], int left, int right, VizCallback cb);
void MergeSort_viz_wrapper(int arr[], int n, VizCallback cb); // wrapper matching (arr,n,cb)

#endif // SORTING_H