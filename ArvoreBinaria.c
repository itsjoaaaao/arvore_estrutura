//Aluno: João Paulo
#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

int main(){
    
    ArvBin *raiz;
    int op, valor, cons, tot, alt;
    
    raiz = cria_ArvBin();
    
    do{
    	printf("1-inserir\n");
    	printf("2-remover\n");
    	printf("3-consultar\n");
    	printf("4-altura da arvore\n");
    	printf("5-total de nos\n");
    	printf("6-imprimir pre-ordem\n");
    	printf("7-imprimir pos-ordem\n");
    	printf("8-imprimir em-ordem\n");
	printf("9-total de nos impares\n");
    	scanf("%d", &op);
    	
    	switch(op){
    		case 1:
    			printf("Digite um valor:\n");
    			scanf("%d", &valor);
    			insere_ArvBin(raiz,valor);
    		break;
    		case 2:
    			if(estaVazia_ArvBin(raiz)==1){
    				printf("arvore vazia!!\n");
				}else{
					remove_ArvBin(raiz,valor);
				}
			break;
			case 3:
				printf("Digite o valor que deseja consultar:\n");
				scanf("%d", &valor);
				
				cons = consulta_ArvBin(raiz,valor);
				if(cons == 1){
					printf("%d\n", (*raiz)->info);
				}
			break;
			case 4:
				alt = altura_ArvBin(raiz);
				if(alt){
					printf("a altura da arvore eh: %d\n", alt);
				}
			break;
			case 5:
				tot = totalNO_ArvBin(raiz);
				if(tot){
					printf("o total de nos eh: %d\n", tot);
				}
			break;
			case 6:
				preOrdem_ArvBin(raiz);
			break;
			case 7:
				posOrdem_ArvBin(raiz);
			break;
			case 8:
				emOrdem_ArvBin(raiz);
			break;
		        case 9:
				printf("Digite um numero impar ja inserido:\n");
        			scanf("%d", &valor);
        
				imp = total_no_impar(raiz,valor);
        			if(imp){
          				printf("total de nos impares: %d\n", imp);
        			}
			break;
		}
    	
	}while(op);

    return 0;
}

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0;//elemento já existe
            }

            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    // no2 é o nó anterior a r na ordem e-r-d
    // no1 é o pai de no2
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

//função nova criada por mim
int total_no_impar(ArvBin *raiz, int valor){
	if(raiz == NULL){
		return 0;
	}
	if(*raiz == NULL){
		return 0;
	}
	int cont = 0;
	struct NO* atual = *raiz;
	while(atual != NULL){
		if(valor%2==1){
			cont++;
		}
    if(valor > atual->info){
		atual = atual->dir;
    }
    else{
		atual = atual->esq;
    }
}
  return cont;
}

int consulta_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n",(*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}
