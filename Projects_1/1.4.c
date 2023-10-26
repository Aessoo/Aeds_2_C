#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define TAM 100
int quantidadeMov = 0;
int quantidadeComp = 0;

struct Jogador {
    int id;
    char nome[TAM];
    int altura;
    int peso;
    char universidade[TAM];
    int anoNascimento;
    char cidadeNascimento[TAM];
    char estadoNascimento[TAM];
};
typedef struct Jogador Jogador;

void setId(int id, Jogador* jogadorLido){
    jogadorLido->id = id;
}

void setNome(char nome[], Jogador* jogadorLido){
    strcpy(jogadorLido->nome, nome);
}

void setAltura(int altura, Jogador* jogadorLido){
    jogadorLido->altura = altura;
}

void setPeso(int peso, Jogador* jogadorLido){
    jogadorLido->peso = peso;
}

void setUniversidade(char universidade[], Jogador* jogadorLido){
    if(universidade[0] == '\0'){
        strcpy(jogadorLido->universidade, "nao informado");
    }else{
        strcpy(jogadorLido->universidade, universidade);
    }
}

void setAnoNascimento(int anoNascimento, Jogador* jogadorLido){
    jogadorLido->anoNascimento = anoNascimento;
}

void setCidadeNascimento(char cidadeNascimento[], Jogador* jogadorLido){
    if(cidadeNascimento[0] == '\0'){
        strcpy(jogadorLido->cidadeNascimento, "nao informado");
    }else{
        strcpy(jogadorLido->cidadeNascimento, cidadeNascimento);
    }
}

void setEstadoNascimento(char estadoNascimento[], Jogador* jogadorLido){
    if(estadoNascimento[0] == '\0'){
        strcpy(jogadorLido->estadoNascimento, "nao informado");
    }else{
        strcpy(jogadorLido->estadoNascimento, estadoNascimento);
    }
}

int charInt(char aux[]){
    int auxT = 0;
    int auxInt = 0;

    for(int i = strlen(aux)-1, j = 0; i >=0; i--, j++){
        auxInt = ((int)aux[i] - '0');
        auxT += auxInt * pow(10,j);
    }
    return auxT;
}

void lerAteVirgula(char valLido[], char valFinal[], int virgulasPuladas) {
    char aux;
    int posL = 0, posF = 0;
    while(virgulasPuladas>0){
        if(valLido[posL++]==',')
        virgulasPuladas--;
    }
    aux = valLido[posL++];
    while( aux != ',' && aux != '\n' ) {
        valFinal[posF++] = aux;
        aux = valLido[posL++];
    }
    valFinal[posF] = '\0';
}

void ler(int id, FILE *arq, Jogador* jogador) {
    char auxC;
    char aux[TAM];
    char auxA[8*TAM];
    int tam = 0;

    fseek(arq, 0, SEEK_SET);

    do{
        tam= 0 ;
        do{
            fscanf(arq, "%c", &auxC);
            auxA[tam++] = auxC;
        }while(auxC != '\n' && auxC != EOF);
        auxA[tam] = '\0';
        lerAteVirgula(auxA, aux, 0);
    }while(charInt(aux) != id);

    setId(charInt(aux), jogador);

    lerAteVirgula(auxA, aux, 1);
    setNome(aux, jogador);

    lerAteVirgula(auxA, aux, 2);
    setAltura(charInt(aux), jogador);

    lerAteVirgula(auxA, aux, 3);
    setPeso(charInt(aux), jogador);

    lerAteVirgula(auxA, aux, 4);
    setUniversidade(aux, jogador);

    lerAteVirgula(auxA, aux, 5);
    setAnoNascimento(charInt(aux), jogador);

    lerAteVirgula(auxA, aux, 6);
    setCidadeNascimento(aux, jogador);

    lerAteVirgula(auxA, aux, 7);
    setEstadoNascimento(aux, jogador);
}

void imprimir(Jogador* jogador) {
    printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", jogador->id, jogador->nome, jogador->altura, jogador->peso, jogador->anoNascimento, jogador->universidade,jogador->cidadeNascimento, jogador->estadoNascimento);
}

int compareJogador(const void *a, const void *b) {
    Jogador *jogadorA = (Jogador *)a;
    Jogador *jogadorB = (Jogador *)b;

    int resultado;
    resultado = strcmp(jogadorA->estadoNascimento, jogadorB->estadoNascimento);

    if (resultado == 0) {
        resultado = strcmp(jogadorA->nome, jogadorB->nome);
    }
    quantidadeComp++;

    return resultado;
}


void quicksort(Jogador *jogadores, int esquerda, int direita) {
    int i = esquerda, j = direita;
    Jogador temp;
    Jogador pivo = jogadores[(esquerda + direita) / 2]; 
    while (i <= j) {
      
        while (compareJogador(&jogadores[i], &pivo) < 0) {
            i++;
        }
        while (compareJogador(&jogadores[j], &pivo) > 0) {
            j--;
        }
        
        if (i <= j) {
            temp = jogadores[i];
            jogadores[i] = jogadores[j];
            jogadores[j] = temp;
            i++;
            j--;
            quantidadeMov += 3; 
        }
    };
    
    if (esquerda < j) {
        quicksort(jogadores, esquerda, j);
    }
    
    if (i < direita) {
        quicksort(jogadores, i, direita);
    }
}

int main(void) {
    FILE *arq = fopen("tmp/players.csv", "r");
    Jogador jogador[5000];
    char id[TAM];
    scanf("%s", id);
    int tamJ = 0;

    while (strcmp(id, "FIM")) {
        ler(charInt(id), arq, &jogador[tamJ]);
        tamJ++;
        scanf("%s", id);
    }

    clock_t begin = clock();
    quicksort(jogador, 0, tamJ - 1);
    clock_t end = clock();

    for (int i = 0; i < tamJ; i++) {
        imprimir(&jogador[i]);
    }
    fclose(arq);
    return 0;
}

