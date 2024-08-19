#ifndef AUXILIAR_H_INCLUDED
#define AUXILIAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct D{
	short int	day;
	short int	month;
	short int	year;
}Date;

typedef struct P{
	
	char 		name[35];
	short int	cpf[11];	
	Date		birth;
	
	struct P* 	next;
}Person;

void getCPF(short int*);
int valCPF(short int* cpf);
int searchCPF(Person**, short int*);
int compCPF(short int*, short int*);

void getString(char*, int);
int valName(char*);

int valDate(Date);
void getDate(Date*);

Person createPerson();

#endif
