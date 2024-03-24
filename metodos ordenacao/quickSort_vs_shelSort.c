#include <stdio.h>
#include <stdlib.h>

int shellCont;
int quickCont;

void shell(int v[], int n){
    int i, j, k;
    int x;
    int gap = 1;

    while (gap <= n){
        gap = gap * 2;
    }
    gap = (gap / 2) - 1;

    while (gap > 0){
        for (k = 0; k < gap; k++){
            for (i = k + gap; i < n; i += gap){
                shellCont++;
                x = v[i];

                j = i - gap;

                shellCont++;
                while (j >= 0 && v[j] > x){
                    shellCont++;
                    v[j + gap] = v[j];

                    j -= gap;
                    if (j >= 0){
                        shellCont++;
                    }
                }
                shellCont++;
                v[j + gap] = x;
            }
        }
        gap = gap / 2;

    }
}

void quick(int v[], int c, int f){
    if (c >= f){
        return;
    }

    int m = (c + f) / 2;
    int pivo;
    int i = c;
    int j = f;
    int tmp;

    pivo = v[m];
    quickCont++;


    while (1){
        
        quickCont++;
        while (v[i] < pivo){
            i++;
            quickCont++;
        }

        quickCont++;
        while (v[j] > pivo){
            j--;
            quickCont++;
        }


        if (j <= i){
            break;
        }

        // Copia dos vetores
        
        quickCont += 3;
        tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
        i++;
        j--;

    }
    quick(v, c, j);
    quick(v, j + 1, f);
}

int main(){
    int i, j;
    int n, num;
    int *vetor;
    int *vq, *vs;
    int ops = 0, opq = 0;

    scanf("%d", &n);

    vetor = (int *)calloc(n, sizeof(int));

    for (i = 0; i < n; i++){
        scanf("%d", &num);
        vetor[i] = num;
    }

    for (i = 1; i <= n; i++){
        vs = (int *)calloc(i, sizeof(int));
        vq = (int *)calloc(i, sizeof(int));

        for (j = 0; j < i; j++){
            vs[j] = vetor[j];
            vq[j] = vetor[j];
        }

        shell(vs, i);
        quick(vq, 0, i - 1);


        if (quickCont == shellCont){
            printf("-");
        }
        else if (quickCont < shellCont){
            printf("Q");
        }
        
        else if (shellCont < quickCont){
            printf("S");
        }
        
   
        
        shellCont = 0;
        quickCont = 0;
        free(vs);
        free(vq);
    }


    printf("\n");
    free(vetor);
    return 0;
}
