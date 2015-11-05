#include <stdio.h>
#include <stdlib.h>

struct no{                                                  //cria��o da struct
	int chave;												//chave sera o numero armazenado
	struct no *esq;											//ponteiro para elemento menor
	struct no *dir;											//ponteiro para elemento maior
};
typedef struct no no;

no *raiz = NULL;											//inicia a arvore com a raiz aterrada em NULL

int busca(no *raiz, int elemento); 							//fun��o de busca
void inserir(no **raiz, int elemento);						//fun��o de inser��o
void emordem(no *raiz);										//fun��o de impress�o em ordem
void preordem(no *raiz);									//fun��o de impress�o pr�-ordem
void posordem(no *raiz);									//fun��o de impress�o p�s-ordem
void lb(no *raiz);											//fun��o de impress�o em Labelled Bracketing
void remover(no **raiz, int elemento);						//fun��o de remo��o
no *menormaior(no *raiz);									//fun��o que retorna o menor n� a partir de um n� dado										

main() {
	int i, a, b, c, d, e;									//variaveis auxiliares
	printf("Numero de Insercoes: ");						
	scanf("%d", &a);										//recolhe o numero de elementos
	printf("Elementos: ");
	
	for(i=0;i<a;i++) {										
		fflush;
		scanf("%d", &b);									//recolhe os elementos
		inserir(&raiz, b);								 	//faz a inser��o na arvore
	}
	printf("\n--->  MENU  <---\n-> 1 para imprimir a arvore.");			//print do MENU
	printf("\n-> 2 para inserir elementos.");
	printf("\n-> 3 para remover elementos.");
	printf("\n-> 4 para buscar elementos.");
	printf("\n-> 0 para sair\n");
	fflush;
	scanf("%d", &c);
	
	while(c!=0) {														//codigo do MENU
		fflush;
		switch(c) {													
			case 1:
				system("cls");
				printf("Pre Ordem:\n");
					preordem(raiz);
				printf("\nPos Ordem:\n");
					posordem(raiz);
				printf("\nEm Ordem:\n");
					emordem(raiz);
				printf("\nLabelled Bracketing:\n");
					lb(raiz);
				printf("\n");
				break;
			case 2:
				system("cls");
				printf("Novo elemento: ");
				scanf("%d", &d);
				inserir(&raiz, d);
				break;
			case 3:
				system("cls");
				printf("Elemento para remocao: ");
				scanf("%d", &d);
				remover(&raiz, d);
				break;
			case 4:
				system("cls");
				printf("Elemento para busca: ");
				scanf("%d", &d);
				e = busca(raiz, d);
				if(e==1) printf("\nO elemento %d nao existe na arvore.\n", d);
				if(e==2) printf("\nO elemento %d existe na arvore.\n", d);
				break;
		}
		printf("\n--->  MENU  <---\n-> 1 para imprimir a arvore.");
		printf("\n-> 2 para inserir elementos.");
		printf("\n-> 3 para remover elementos.");
		printf("\n-> 4 para buscar elementos.");
		printf("\n-> 0 para sair\n");
		fflush;
		scanf("%d", &c);
	}	
}

int busca(no *raiz, int elemento){
	if(raiz == NULL) {									//faz a verifica��o se o elemento existe
		return 1;										
	}
	if(elemento < (raiz)->chave) {						
		return busca((raiz)->esq, elemento);			//continua busca com elemento da esquerda
	}
	if(elemento > (raiz)->chave) {						
		return busca((raiz)->dir, elemento);			//continua busca com elemento da direita
	}
	return 2;											//se o elemento nao for nulo nem maior nem menor ele ser� igual e retornar� o valor 2
}

void inserir(no **raiz, int elemento) {
	if(*raiz == NULL) {									//faz a verifica��o se o espa�o nao contem elementos da arvore
		*raiz = (no *)malloc(sizeof(no));				//aloca espa�o para uma nova struct
		(*raiz)-> chave = elemento;						//define a chave dessa struct igual ao elemento de entrada
		(*raiz)-> dir = NULL;							//aterra o lado direito da nova folha
		(*raiz)-> esq = NULL;							//aterra o lado esquerdo da nova folha
	}
	if(elemento < (*raiz)->chave) {						//verifica se o elemento de entrada � menor que o numero chave atual
		inserir(&(*raiz)->esq, elemento);				//executa novamente a fun��o com o endere�o esquerdo como raiz
	}
	if(elemento > (*raiz)->chave) {						//verifica se o elemento de entrada � maior que o numero chave atual
		inserir(&(*raiz)->dir, elemento);				//executa novamente a fun��o com o endere�o direito como raiz
	}
}

void emordem(no *raiz) {								//faz a impress�o do menor para o maior, logo ela ira diminuir ao maximo os valores, imprimir, aumentar o minimo possivel e reimprimir 
	if(raiz != NULL) {									//verifica se o elemento existe
		emordem(raiz->esq);								//re-executa a fun��o com o elemento da esquerda para chegar no menor possivel
		printf("%d ", raiz->chave);						//faz a impress�o
		emordem(raiz->dir);								//re-executa a fun��o aumentando os valores chave
	}													//ou seja imprime em ordem crescente de valores chave
}

void preordem(no *raiz) {								//faz a impress�o e depois percorre a arvore primeiramente pelo lado esquerdo, ou seja a impress�o comessar� pela raiz
	if(raiz != NULL) {									//verifica se o elemento existe
		printf("%d ", raiz->chave);						//faz a impress�o
		preordem(raiz->esq);							//re-executa a fun��o diminuindo os valores chave
		preordem(raiz->dir);							//re-executa a fun��o aumentando os valores chave
	}													//ou seja, imprimir� de cima para baixo da esquerda para a direita
}

void posordem(no *raiz) {								//faz a impressao depois de percorrer a arvore
	if(raiz != NULL) {									//verifica se o elemento existe
		posordem(raiz->esq);							//re-executa a fun��o diminuindo os valores chave
		posordem(raiz->dir);							//re-executa a fun��o aumentando os valores chave
		printf("%d ", raiz->chave);						//ou seja, imprimir� de baixo para cima, da esquerda para a direita
	}
}

void lb(no *raiz) {										//faz impress�o organizada em colchetes
	if(raiz != NULL) {									//mesmo c�digo base da imrpess�o pr� ordem, j� q os primeiros termos representados s�o os de cima e os da esquerda
		printf("[");									//adiciona um colhete antes de imprimir o numero
		printf("%d", raiz->chave);
		lb(raiz->esq);
		lb(raiz->dir);
		printf("] ");									//fecha o que foi imprimido na execu��o
	}
	else printf("[] ");									//se verificado que h� um espa�o vazio, imprime um colchete vazio
}

void remover(no **raiz, int elemento){
	if(busca(*raiz, elemento)== 1) {
		printf("\nO elemento %d nao existe na arvore.\n", elemento);	//verifica se o elemento existe na �rvore
	}																	//se nao existir nao precisa executar a fun��o
	
	else if(elemento < (*raiz)->chave) {						
		remover(&(*raiz)->esq, elemento);				
	}
		else if(elemento > (*raiz)->chave) {			
	  		remover(&(*raiz)->dir, elemento);							//procura a posi��o do elemento
		}
			else if((*raiz)->esq != NULL && (*raiz)->dir != NULL) {		//se o elemento tiver galho para os dois lados
		  	 	no *aux = NULL;											//define a aux primeiramente como NULL
		  		aux = menormaior((*raiz)->dir);							//como � passado o maior valor, � retornado o menor valor maior que o elemento para remo��o
		  		(*raiz)->chave = aux->chave;							//copia o valor da aux encontrada para a chave que ser� removida
		  		remover(&(*raiz)->dir, (*raiz)->chave);					//remove o elemento menor maior que teve a chave copiada para o elemento q era para remover
			}
				else {
					no *aux = (*raiz);									//salva o valor da raiz para remo��o na variavel aux
					if((*raiz)->esq == NULL) {							//verifica se a raiz da esq � nula
	  					(*raiz) = (*raiz)-> dir;						//reajusta para trocar de chave com o elemento da direita
					}
						else {											//se o valor da esquerda nao for nulo, basta trocar os valores das chaves			
							(*raiz) = (*raiz)-> esq;					//muda a raiz para a raiz da esquerda
						}
						free(aux);										//libera a raiz entrada na fun��o
				}
}

no *menormaior(no *raiz) {												
	if(raiz==NULL)  return NULL;										//se a raiz ja for nula nao altera o valor auxiliar
	else if(raiz->esq==NULL) return raiz;								//se a raiz da esquerda for nula, retorna a raiz atual, ou seja o menor valor nao nulo
		else return menormaior(raiz->esq);								//se nao for, re-executa a fun��o com o valor da esquerda para chegar no valor desejado					
}
