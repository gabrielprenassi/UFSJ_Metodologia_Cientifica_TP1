#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "codigo/algoritmos.h"
#include "codigo/monitor_memoria.h"

// ============================
// Geração de vetores
// ============================
void generate_vector(int arr[], int n, int digits, const char* scenario) {
    int low = (digits > 1) ? 1 : 0;
    int high = 1;
    for (int i = 0; i < digits; i++) high *= 10;
    high -= 1;

    if (strcmp(scenario, "sorted") == 0) {
        for (int i = 0; i < n; i++) arr[i] = low + i;
    } else if (strcmp(scenario, "reverse") == 0) {
        for (int i = 0; i < n; i++) arr[i] = low + n - i;
    } else {
        for (int i = 0; i < n; i++) arr[i] = low + rand() % (high - low + 1);
    }
}

// ============================
// Medição de tempo simples
// ============================
double measure_time(void (*sort_func)(int*, int), int* arr, int n, size_t* mem_used) {
    current_mem = 0;
    peak_mem = 0;

    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();

    *mem_used = peak_mem > 0 ? peak_mem : n * sizeof(int);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// ============================
// Limites por algoritmo e cenário
// ============================
int max_size_for_algo_scenario(const char* algo, const char* scenario) {
    // Bubble Sort
    if (strcmp(algo, "bubble_sort") == 0) {
        return 100000;
    }

    // Insertion e Selection Sort
    if (strcmp(algo, "insertion_sort") == 0 ||
        strcmp(algo, "selection_sort") == 0) {
        return 250000;
    }

    // Radix Sort
    if (strcmp(algo, "radix_sort") == 0) {
        return 1000000;
    }

    return 0;
}

// ============================
// Main
// ============================
int main() {
    srand(2025);

    int min_size = 1000;
    int step = 1000;
    int digits_list[] = {1, 3, 5};
    int repetitions = 3;

    const char* scenarios[] = {"sorted", "reverse", "random"};
    const char* algos_names[] = {"bubble_sort", "insertion_sort", "selection_sort", "radix_sort"};
    void (*algos[])(int*, int) = {bubble_sort, insertion_sort, selection_sort, radix_sort};

    for (int s = 0; s < 3; s++) {
        char filename[50];
        snprintf(filename, sizeof(filename), "%s.csv", scenarios[s]);
        FILE* f = fopen(filename, "w");
        if (!f) { perror("Erro ao criar arquivo"); return 1; }

        fprintf(f, "algorithm,scenario,size,digits,repetition,execution_time,memory_used_bytes\n");

        for (int d = 0; d < 3; d++) {
            for (int a = 0; a < 4; a++) {
                int max_size_algo = max_size_for_algo_scenario(algos_names[a], scenarios[s]);
                for (int n = min_size; n <= max_size_algo; n += step) {
                    int reps_vector = (strcmp(scenarios[s], "random") == 0) ? repetitions : 1;
                    int reps_run    = (strcmp(scenarios[s], "random") == 0) ? 1 : repetitions;

                    for (int v = 0; v < reps_vector; v++) {
                        int* vector = (int*) my_malloc(n * sizeof(int));
                        generate_vector(vector, n, digits_list[d], scenarios[s]);

                        for (int r = 0; r < reps_run; r++) {
                            int* copy = (int*) my_malloc(n * sizeof(int));
                            memcpy(copy, vector, n * sizeof(int));

                            size_t mem_used;
                            double exec_time = measure_time(algos[a], copy, n, &mem_used);

                            fprintf(f, "%s,%s,%d,%d,%d,%.6f,%zu\n",
                                    algos_names[a], scenarios[s], n, digits_list[d], r+1, exec_time, mem_used);

                            printf("%s | %s | n=%d | d=%d | rep=%d | time=%.6f s\n",
                                   algos_names[a], scenarios[s], n, digits_list[d], r+1, exec_time);

                            my_free(copy, n * sizeof(int));
                        }

                        my_free(vector, n * sizeof(int));
                    }
                }
            }
        }

        fclose(f);
        printf("Results saved to %s\n", filename);
    }

    return 0;
}