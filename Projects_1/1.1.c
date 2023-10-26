#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h> 

#define TAM 100

//Struct 
struct Jogador{
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

//Metodo set 

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

//Metodo para trocar numeros de base char para base int 
int charInt(char aux[]){
    int auxT = 0;
    int auxInt = 0;

    for(int i = strlen(aux)-1, j = 0; i >=0; i--, j++){
    	auxInt = ((int)aux[i] - '0');
	auxT += auxInt * pow(10,j);
    }
    return auxT;
}

//Metodo ler ate a virgula 
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

		
			
//Metodo Ler
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


//Metodo Imprimir 
void imprimir(Jogador* jogador) {
	printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", jogador->id, jogador->nome, jogador->altura, jogador->peso, jogador->anoNascimento, jogador->universidade,jogador->cidadeNascimento, jogador->estadoNascimento);
}	

//Metodo Swapvoid swap(Jogador *jogador[], int i, int menor){
void swap(Jogador jogador[], int i, int menor){
	Jogador jogadorAUX = jogador[menor];
    jogador [menor] = jogador[i];
	jogador [i] = jogadorAUX;

}	

//Metodo Seleção
int selecao(Jogador *jogador, int n){
	int cont = 0;
	for(int i=0; i < (n - 1); i++){
		int menor = i;
		for(int j = (i + 1); j < n; j++){
			int pos = 0;
			char menorA[TAM]; 
            strcpy(menorA, jogador[menor].nome);
			char jA[TAM];
            strcpy(jA, jogador[j].nome);
			while(pos < TAM){
				cont++;
				if((menorA[pos]) > (jA)[pos] ){
					menor = j;
					pos = TAM;
					cont++;
				}else if((menorA[pos]) < ((jA)[pos])){
						pos = TAM;
						cont++;
					}
				pos++;
				cont++;
			}
		}
		swap(jogador, i, menor);
	}
	return cont;
}

int main(void) {
    clock_t begin = clock();

	FILE *arq = fopen("tmp/players.csv", "r");
	Jogador jogador[5000];
	char id[TAM];
	char nome[TAM];
	scanf("%s", id);
	int tamJ = 0;
	int quantidadeComp = 0;
    

	while(strcmp(id,"FIM")){
		ler(charInt(id), arq, &jogador[tamJ]);
		tamJ++;
		scanf("%s", id);
	}

	quantidadeComp = selecao(jogador, tamJ);

	//Buscar o nime listado pelo programa
    scanf(" %[^\n]s", nome);	
    while(strcmp(nome,"FIM")){
		bool tem = false;
        //buscando nome informado
		//pesquisaBinaria (jogador, nome, tamJ);
        int inf = 0;
        int sup = tamJ;
        int meio;
    
        while (inf <= sup){
            meio = (inf + sup)/2;
            quantidadeComp++;
            char auxNome[TAM];
            strcpy(auxNome, jogador[meio].nome);
            if (strcmp(nome, auxNome) == 0){
                tem = true;
                inf = sup + 1;
            }else if (strcmp(nome, auxNome) < 0){
                sup = meio-1;
            }else {
                inf = meio+1;
            }
            quantidadeComp++;
            //printf("\n%s\t%d\t%d\n", auxNome, inf, sup );
        }
		//printando se tem ou não
		if(tem == true){
			puts("SIM");
		}else{
			puts("NAO");
		}
		scanf(" %[^\n]s", nome);
	}
	
	clock_t end = clock();
	fclose(arq);
	return 0;
}
