/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Vitor
 *
 * Created on 25 de Maio de 2019, 19:26
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    char pid;
}palavra;

typedef struct{
    int id;
}indice;

typedef struct nopilha* ponteiroP; //P de pilha

typedef struct nopilha{
    indice indice; //indice pra saber se a arv esta no texto
    ponteiroP top; //primeiro char
    ponteiroP prox; //prox no de pilha
    int tam; /*tamanho do char, eh possivel achar se a palavra eh igual vendo
    primeiro pelo tamanho, corta o tempo da computacao se tamanh nao for igual*/
}nopilha;

typedef struct noarv* ponteiroA; //A de arvore

typedef struct noarv{
    palavra palavra; //palavra pra organizacao
    nopilha pilha; //pilha dentro do no
    ponteiroA cima; //no de arvore de cima
    ponteiroA direita; //subarv direita
    ponteiroA esquerda; //subarv esquerda
}noarv;





void iniciaarvore(ponteiroA *arv){
    *arv = NULL;
}

int pilhavazia(ponteiroP *pilha){
    return (pilha->tam == 0);
}

void iniciapilha(ponteiroP *pilha){
    pilha->top = NULL;
    pilha->tam = 0;
}

bool estavazia(ponteiroA *arv){
    return (*arv = NULL);
}

bool enarvoreia(ponteiroA *arv, palavra palavr){
    char y = palavr.pid;
    char x = (*arv)->palavra.pid;
    
    if (estavazia(&(*arv))){
        (*arv) = malloc(sizeof(noarv));
        (*arv)->direita = (*arv)->esquerda = NULL;
        (*arv)->palavra = palavr;
        return true;
    }
    else if (strcmp(y, x) == 0){ //igual
        printf("texto repetido!\n");
        return false;
    }
    else if (strcmp(y, x) > 0){ //para esquerda
        return (enarvoreia(&(*arv)->esquerda, palavr));
    }
    else {//(strcmp < 0) para direita
        return (enarvoreia(&(*arv)->direita, palavr));
    }
}

void empilha(ponteiroP *pilha, int pag){
    ponteiroP aux;
    aux = (ponteiroP) malloc(sizeof(nopilha));
    aux->indice.id = pag;
    
    if(pilhavazia(&pilha)){
        iniciapilha(&pilha);
        pilha->top = aux;
        aux->prox = NULL;
    }
    else{
        aux->prox = pilha->top;
        pilha->top = aux;
    }
}


bool pesquisaeindiceia(ponteiroA *arv, palavra palavr, int pagina){
    if (*arv == NULL)
        return false;
    
    if (strcmp ((*arv)->palavra.pid, palavr->pid) == 0){
        empilha(&(*arv)->pilha, pagina);
        return true;
    }
    
    if (strcmp (palavr.pid, (*arv)->palavra.pid) < 0)
        return (pesquisaeindiceia(&(*arv)->esquerda, palavr, pagina));
    
    else
        return (pesquisaeindiceia(&(*arv)->direita, palavr, pagina));
}






/*
 * 
 */
int main(int argc, char** argv) {
    ponteiroA raiz;
    iniciaarvore(&raiz);
    
    
    FILE * arqivo;
    arqivo = fopen("textao.txt", "r");
    
    if (arqivo == NULL){
        printf("\tabrir arquivo... que arquivo????\n");
        fclose(arqivo);
        exit(-1);
    }
    
    char str[123];
    char * strstart;
    
    fgets(str, 123, arqivo);
    printf("%s\n", strstart);
    
    strstart = strtok(str, ":");
    printf("%s\n", strstart);
    
    char strcomp[123] = "<termos";
    if (strcmp(strstart, strcomp)){
        printf("o arquivo NAO comeca com '<termos', e sim '%s'", strstart);
        exit(-1);
    }
    
    strstart = strtok(NULL, ",");
    printf("%s\n", strstart);
    
    while (strstart != EOF){
        palavra palavrain;
        palavrain.pid = strstart;
        enarvoreia(&(*raiz), palavrain);


        char naodeve[123] = "\n";
        while (strcmp(strstart, naodeve) != 0){
            strstart = strtok(NULL, ",>");
            printf("%s\n", strstart);
            palavrain.pid = strstart;
            enarvoreia(&(*raiz), palavrain);
        }

        naodeve = "<page:";
        int pagina;
        while (strcmp(strstart, naodeve) != 0){
            if (strcmp(strstart, naodeve) == 0)
                sscanf(strstart, "<page:%i", pagina);

            palavrain.pid = strstart;
            pesquisaeindiceia(&(*raiz), palavrain, pagina);

            strstart = strtok(NULL, " ,>\n123456789");
        }
    }
    
    return (EXIT_SUCCESS);
}

//
//                          arvore
//                         /      \
//                     acolher     nopilha
//                                /       \
//                         eloquente      tamarindo
//                         /       \
//                     cabeça    hiperativo
//                      /                 \
//                 bombado               janela
//
//arv modelo pra entender melhor a programacao q to fazendo