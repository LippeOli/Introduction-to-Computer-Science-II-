#include <stdio.h>
#include <stdlib.h>

#define numElem(x)  (sizeof(x) / sizeof((x)[0]))


void insertionSort(int a[], int tamVetores){
    long comps = 0;
    long trocas = 0;
    for(int p = 1; p < tamVetores; p++){
        int x = a[p];
        trocas++;
        int i = p-1;
        while(i >= 0 && x < a[i]){
            comps++;
            a[i+1] = a[i];
            trocas++;
            i--;
        }
        if(i>=0){
        comps++;
        }
        a[i+1] = x;
        trocas++;
    }
    printf ("I %d %ld %ld\n", tamVetores, trocas,comps);
}

void merge(int vetor[], int comeco, int meio, int fim, long* comps, long* trocas) {

    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] <= vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
        (*comps)++;
        (*trocas)++;
    }

    while(com1 <= meio){  //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        (*trocas)++;
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        (*trocas)++;
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){    //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux-comeco];
        (*trocas)++;
    }

    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim, long* comps, long* trocas){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(vetor, comeco, meio, comps, trocas);
        mergeSort(vetor, meio+1, fim, comps, trocas);
        merge(vetor, comeco, meio, fim, comps, trocas);
    }
}

int main() {
    int numVetores;
    long trocas,comps;
    scanf("%d", &numVetores);
    int tamVetor[numVetores];
    for (int i = 0; i<numVetores; i++){
        scanf("%d",&tamVetor[i]); 
    }
    for (int i = 0; i<numVetores; i++){
        int vetor[tamVetor[i]];
        int vetorAux[tamVetor[i]];

        for (int j = 0; j<tamVetor[i]; j++){
            
            scanf("%d", &vetor[j]);
            vetorAux[j] = vetor[j];
        }
        int tam = numElem(vetor);
        insertionSort(vetor,tam);

        int tamAux = numElem(vetorAux);
        comps = 0;
        trocas = 0;
        mergeSort(vetorAux,0,tamAux-1, &comps, &trocas);

        printf("M %d %ld %ld\n", tamAux, trocas, comps);
        
    }
}