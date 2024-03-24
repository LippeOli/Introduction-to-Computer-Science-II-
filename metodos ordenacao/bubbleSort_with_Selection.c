#include <stdio.h>
#include <string.h>


void Bolha(int lista[], int n){

    int i, passar, aux, s;

    for(passar = n-1; passar >= 1; passar = s){
        s = -1;
        for(i = 0; i < passar; i++){
            printf("C %d %d\n", i, i+1);
            if(lista[i] > lista[i+1]){
                printf("T %d %d\n", i, i+1);
                s = i;
                aux = lista[i];
                lista[i] = lista[i+1];
                lista[i+1] = aux;
            }
        }
    }
    return 0;
}

void Selecao(int lista[], int n){

    int i, aux, k;

    for(i = 0; i < n - 1; i++){
        k = i;
        for(int j = i+1; j < n; j++){
            printf("C %d %d\n", k, j);
            if(lista[j] < lista[k]){
                k = j;
            }
        }
        if (k != i){
            printf("T %d %d\n", i, k);
            aux = lista[i];
            lista[i] = lista[k];
            lista[k] = aux;
        }
    }

}

int main(){
    int n, i;
    char escolha[10];

    scanf("%s", escolha);

    scanf("%d", &n);

    int listaOriginal[n];

    for (i = 0; i < n; i++) scanf("%d", &listaOriginal[i]);

    if (strcmp(escolha, "selecao") == 0) {
        Selecao(listaOriginal, n);
    } else if (strcmp(escolha, "bolha") == 0) {
        Bolha(listaOriginal, n);
    }

    for (i = 0; i<n; i++) printf("%d ", listaOriginal[i]);
}