#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "auxiliar.h"

int  menu(Person**);
void add(Person**);
void remov(Person**);
void show(Person**);

int main(){
	
	Person* hash = NULL;
	int cond = 1;
	
	while(cond){
		switch(menu(&hash)){
			case 0: cond = 0;		break;
			case 1: add(&hash);		break;
			case 2: remov(&hash);	break;
			case 3: show(&hash);	break;
		}
	}
}

int menu(Person** list){
	system("cls");
	printf("=========   MENU   =========\n (1)  Adicionar\n (2)  Remover\n (3)  Exibir\n (0)  Fim");
	
	if(*list == NULL) printf("\n\n\n* A lista esta vazia");
	
	char ch = 0;
	while(ch < 48 || ch > 51)
		ch = getch();
	
	return ch - 48;
}

void add(Person** list){
	
	Person* aux = *list;
	Person*	novo = (Person*) malloc(sizeof(Person));
	*novo = createPerson();
	novo->next = NULL;

	if(*list == NULL)
		*list = novo;
	else{
		while(aux->next != NULL)
			aux = aux->next;	
		aux->next = novo;
	}
}

void remov(Person** list){
	
	Person* aux = *list;
	Person* ant = NULL;
	
	char ch = 0;
	int valid, i;
	short int cpf[11];
	
	system("cls");
	if(*list == NULL)
		printf(" ** A lista esta vazia");
	
	else{
		printf("============= Remover pessoa =============\nCPF:  ");
		do{
			getCPF(cpf);
			valid = valCPF(cpf);
			if(!valid){
				for(i = 0; i < 14; i++) putchar(8);
				printf("                 * CPF invalido");
				for(i = 0; i < 31; i++) putchar(8);
			}
		}while( !valid );
		
		system("cls");
		printf("============= Remover pessoa =============.\n");

		while( !compCPF(cpf, aux->cpf) && aux->next != NULL){
			ant = aux;
			aux = aux->next;
		}
			
		if(!compCPF(cpf, aux->cpf)){
			printf(" ** CPF nao cadastrado");
			getch();
		}
		else{
			printf("\nNome: %s \nCPF:  ", aux->name);
			
			for(i = 0; i < 11; i++)
				putchar(aux->cpf[i] + 48);
				
			printf("\nNasc: %02d/%02d/%04d", aux->birth.day, aux->birth.month, aux->birth.year);
			
			printf("\n\n=====  Confirmar remocao  =====\n  (1) Confirmar | (0) Cancelar");
			
			while(ch != '1' && ch != '0') ch = getch();

			if(ch == '1'){
				if(ant != NULL)
					ant->next = aux->next;
				else	
					*list = (*list)->next;

				free(aux);
				printf("\n\n** Removido com sucesso");
			}
		}
	}
}

void show(Person** list){

	Person* aux = *list;
	int i;
	
	system("cls");
	if(aux == NULL)
		printf("** A lista esta vazia");
	
	else{
		printf(" _______________________________________________________________\n");
		printf("|________________Nome________________|_____CPF_____|_Nascimento_|");
		
		while(aux != NULL){
			printf("\n| %-34s | ", aux->name);
			
			for(i = 0; i < 11; i++)
				putchar(aux->cpf[i]+48);
				
			printf(" | %02d/%02d/%04d |", aux->birth.day, aux->birth.month, aux->birth.year);

			aux = aux->next;
		}
		printf("\n|____________________________________|_____________|____________|\n");
	}
	
	while(getch() != 13);
}

