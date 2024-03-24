#include <stdio.h>

void shell(int v[], int n) {
    int gap = 1;
    int comp = 0;
    int trocas = 0;

    while (gap <= n) {
        gap *= 2;
    }

    gap = gap / 2 - 1;

    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int x = v[i];
            int j = i - gap;
            comp++;

            while (j >= 0 && v[j] > x) {
                v[j + gap] = v[j];
                j -= gap;
                comp++;
            }

            v[j + gap] = x;
            trocas++;
        }
        gap /= 2;
    }

    // Imprime o número total de comparações ao final
    printf("Número total de comparações: %d\n", comp);
    printf("Número total de trocas: %d\n", trocas);

}

int main() {
    int arr[] = {3, 8, 5, 7, 6, 4, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    shell(arr, n);

    // Imprime o array ordenado
    printf("Array ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
