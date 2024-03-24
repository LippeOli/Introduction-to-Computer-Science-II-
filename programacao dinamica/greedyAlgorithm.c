//Bruno Garcia de Oliveira Breda - 11212702
//Felipe Oliveira Carvalho - 14613879
//Vitor Antônio de Almeida Lacerda - 12544761

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcularSobreposicao(char *r1, char *r2); // Retorna o número de sobreposições entre as reads
void combinarSequencias(char *r1, char *r2, int sobreposicao, char *novaSequencia); // Concatena as sequências
void removerSequencias(char **sequencias, int max1, int max2, char *novaSequencia, int numSequencias); // Remove as sequencias[max1] e [max2] que foram concatenadas

int calcularSobreposicao(char *r1, char *r2) {
    int tamR1, tamR2;
    int sobreposicao = 0;
    tamR1 = strlen(r1);
    tamR2 = strlen(r2);

    if (r1[tamR1 - 1] == r2[0] && tamR2 == 1) { // Tratando o caso de (ABC,C) -> (ABC)
        sobreposicao = 1;
        return sobreposicao;
    }

    if (strstr(r1, r2) != NULL) { // Verifica se a r2 está contida na r1
        sobreposicao = tamR2;
        return sobreposicao; // Retorna o próprio tamanho da r2
    }

    // Se a sobreposicao estiver na última letra da r1
    if (r1[tamR1 - 1] == r2[0] && r1[tamR1 - 2] != r2[1]) {
        sobreposicao = 1;
        return sobreposicao;
    }

    int j = 0; // O índice da r2 só é incrementado quando há sobreposição
    for (int i = 0; i < tamR1 && j < tamR2; i++) {
        if (r1[i] == r2[j]) {
            sobreposicao++;
            j++;
        } else { // A sobreposição é interrompida quando há uma letra diferente
            i = i - sobreposicao; // Compara todas as letras da r1 com a primeira da r2
            sobreposicao = 0;      // i = o que percorreu - as sobreposições encontradas
            j = 0;                // j volta a ser 0 na tentativa de achar uma sobreposição maior
        }
    }
    return sobreposicao;
}

void combinarSequencias(char *r1, char *r2, int sobreposicao, char *novaSequencia) {
    if (sobreposicao == 0) { // Significa que tem sobreposição, é só juntar as duas sequências
        strcpy(novaSequencia, r1);      // Copia a r1 para a novaSequencia
        strcat(novaSequencia, r2);      // Coloca a r2 ao final da novaSequencia, concatenando
    } else if (sobreposicao == strlen(r2)) { // Significa que a r2 é substring da r1 ou elas são iguais
        strcpy(novaSequencia, r1);
    } else { // Combina cada char da r2 que não está sobreposto com a r1
        strcpy(novaSequencia, r1);
        for (int i = sobreposicao; i < strlen(r2); i++) {
            int t = strlen(novaSequencia);
            novaSequencia[t] = r2[i];
            novaSequencia[t + 1] = '\0';
        }
    }
}

void removerSequencias(char **sequencias, int max1, int max2, char *novaSequencia, int numSequencias) {
    for (int i = max1; i < numSequencias - 1; i++) {
        strcpy(sequencias[i], sequencias[i + 1]); // Remove a sequencia[max1]
    }

    int k;
    // Verifica se a posição do max1 permanece a mesma após a remoção
    if (max1 < max2)
        k = 1;
    else
        k = 0;

    for (int i = max2 - k; i < numSequencias - 2; i++) { // Remove a sequencia[max2]
        strcpy(sequencias[i], sequencias[i + 1]);
    }

    // Desloca a sequencia que sobrou uma posição para a direita para colocar a novaSequencia na sequencia[0]
    for (int i = numSequencias - 2; i >= 1; i--) {
        strcpy(sequencias[i], sequencias[i - 1]);
    }
    strcpy(sequencias[0], novaSequencia); // Põe a novaSequencia na primeira posição (sequencia[0])
}

int main() {
    char **sequencias;
    char *novaSequencia;
    int numSequencias;
    int max1, max2, sobreposicaoMax = -1;
    int sobreposicaoCalculada;

    novaSequencia = (char *)malloc(200 * sizeof(char));
    scanf("%d", &numSequencias);
    sequencias = (char **)malloc(numSequencias * sizeof(char *));
    for (int i = 0; i < numSequencias; i++) {
        sequencias[i] = malloc(200 * sizeof(char));
        scanf("%s", sequencias[i]);
    }

    while (numSequencias >= 2) {
        for (int i = 0; i < numSequencias; i++) {
            for (int j = 0; j < numSequencias; j++) {
                if (i != j) {
                    sobreposicaoCalculada = calcularSobreposicao(sequencias[i], sequencias[j]);
                    if (sobreposicaoCalculada > sobreposicaoMax) {
                        sobreposicaoMax = sobreposicaoCalculada;
                        max1 = i;
                        max2 = j;
                    }
                }
            }
        }

        combinarSequencias(sequencias[max1], sequencias[max2], sobreposicaoMax, novaSequencia);

        if (numSequencias > 2) {
            removerSequencias(sequencias, max1, max2, novaSequencia, numSequencias);
        }
        numSequencias--;
        sobreposicaoMax = -1;
    }

    printf("%s", novaSequencia);

    for (int i = 0; i < numSequencias; i++) {
        free(sequencias[i]);
    }
    free(sequencias);
    return 0;
}
