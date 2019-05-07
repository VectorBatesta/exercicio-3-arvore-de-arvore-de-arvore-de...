/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: a2104679
 *
 * Created on 7 de Maio de 2019, 14:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nolista *ponteiroL;

typedef struct{
    int id;
    ponteiroL prox;
}nolista;

typedef struct{
    ponteiroL first;
}lista;

typedef struct noarvore *ponteiroA;

typedef struct{
    char *palavra;
    ponteiroA direita;
    ponteiroA esquerda;
    lista paginas;
}noarvore;
 

/*
 * 
 */
int main(int argc, char** argv) {
    FILE *entrada;  
    entrada = fopen("texto.txt", "r");
    
    char palavra[100];
    fscanf(entrada, "%s", palavra);
    if (palavra == "<termos:"){
        printf("a");
    }
    else{
        printf("erro: primeira linha");
        return(3);
    }
    
    //fprintf(saida, "%s", palavra);
    fclose(entrada);
    //fclose(saida);
    
    
    return (EXIT_SUCCESS);
}

/*
noarvore *ponteiroarv;

noarvore[
	string palavra;
	ponteiroarv direita;
	ponteiroarv esquerda;
	lista paginas;
]

nolista *ponteirolis;

nolista[
	int id;
	ponteirolis prox;
]

lista[
	ponteirolis primeiro;
]
 */