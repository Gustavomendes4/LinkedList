#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "auxiliar.h"

void getString(char *str, int len){
	char c = 0;
	int i = 0;
	int upper = 0;
	
	do{
		c = getch();
		if(c > 96 && c < 123) c -= 32;
		
		if(str[i-1] == ' ' || i == 0) upper = 0;
		else upper = 32;
		
		if((c > 64 && c < 91) && i < len - 1){
			str[i] = c;
			putchar(c + upper);
			str[++i] = '\0';
		}
		else if(c == ' ' && str[i-1] != ' ' && i > 2 && i < len - 1){
			str[i] = c;
			putchar(c);
			str[++i] = '\0';
			upper = 0;
		}
		else if(c == 8 && i > 0){
			printf("%c %c", c, c);
			str[i--] = '\0';
		}
	}while(c != 13);	
	if(str[i-1] == ' ') str[i-1] = '\0';
}

int valName(char* name){
	return 0;
}

void getCPF(short int cpf[11]){
	char c, alt[11];
	int i = 0, aux1 = 0, aux2 = 0;
	
	do{
		c = getch();
		if(c > 47 && c < 58 && i < 11){
			alt[i] = c;
			i++;
			putchar(c);
					
			if(i == 3 || i == 6) printf(".");
			else if(i == 9) printf("-");
		}
		
		else if(c == 8 && i > 0){
			printf("%c %c", c,c);
			i--;
				
			if(i == 2 || i == 5 || i == 8)
				printf("%c %c", c, c);
		}
	}while(!(c == 13 && i == 11));
		
	//validar cpf
	for(i = 0; i < 9; i++)
		aux1 += (alt[i] - 48) * (10 - i);
	aux1 *= 10;
	aux1 %= 11;
	if(aux1 == 10) aux1 = 0;
		
	for(i = 0; i < 10; i++)
		aux2 += (alt[i] - 48) * (11 - i);
	aux2 *= 10;
	aux2 %= 11;
	if(aux2 == 10) aux2 = 0;
		
	if( aux1 != (alt[9] - 48) || aux2 != (alt[10] - 48)){ //CPF inválido
		aux1 = -1;
		aux2 = -1;
	}
		
	for(i = 0; i < 11; i++) cpf[i] = alt[i] - 48;
	cpf[9] = aux1;
	cpf[10] = aux2;
}

int valCPF(short int* cpf){
	
	int digit1=0, digit2=0;
	int i, mult = 10;
	
	for(i = 0; i < 9; i++)
		digit1 += cpf[i] * mult--;
	
	digit1 = digit1 * 10 % 11;
	if(digit1 == 10) digit1 = 0;
	
	
	mult = 11;
	for(i = 0; i < 10; i++)
		digit2 += cpf[i] * mult--;
	
	digit2 = digit2 * 10 % 11;
	if(digit2 == 10) digit2 = 0;
	
	if(cpf[9] == digit1 && cpf[10] == digit2)
		 i = 1;
	else i = 0;
	
	return i;	
}

int compCPF(short int* cpf1, short int* cpf2){
	
	int ret = 1, i;
	for(i = 0; i < 11; i++){
		if(cpf1[i] != cpf2[i])
			ret = 0;
	}
	return ret;
}

int searchCPF(Person** list,short int* cpf){
	
	return 1;
	// Retorna falso caso o CPF existar na lista
}

void getDate(Date* dat){
	char c, alt[8];
	int i = 0;
			
	do{
		c = getch();
		if(c > 47 && c < 58 && i < 8){
			alt[i] = c;
			i++;
			printf("%c", c);
				
			if(i == 2 || i == 4) printf("/");
		}
			
		else if(c == 8 && i > 0){
			printf("%c", c);
			printf(" ");
			printf("%c", c);
			i--;
				
			if(i == 1 || i == 3){
				printf("%c", c);
				printf(" ");
				printf("%c", c);
			}
		}
	}while(!(c == 13 && i == 8));
		

	for(i = 0; i < 8; i++) alt[i] -= 48;
		
	dat->day = alt[0] * 10;
	dat->day += alt[1];
	dat->month = alt[2] * 10;
	dat->month += alt[3];
	dat->year = alt[4] * 1000;
	dat->year += alt[5] * 100; 
	dat->year += alt[6] * 10;
	dat->year += alt[7];
}

int valDate(Date dat){
	
	int aprovado = 0;
	
	switch(dat.month){
		case 1:	case 3: case 5: case 7: case 8: case 10: case 12:
			if(dat.day > 31) aprovado = 1;
		break;
		
		case 4: case 6: case 9: case 11:
			if(dat.day > 30) aprovado = 1;
		break;
		
		case 2:
			if(dat.year % 4 == 0){ if(dat.day > 29) aprovado = 1;}
			else if(dat.day > 28) aprovado = 1;
			break;
			
		default: aprovado = 1;
	}
	
	if(dat.day < 1) aprovado = 1;
	return aprovado;
}

Person createPerson(){
	
	Person P;
	int valid, i;
	P.next = NULL;
	
	
	system("cls");
	printf("===== Nova pessoa =====");

	printf("\nNome: ");
	do{
		getString(P.name, 35);
	}while(valName(P.name));
	
	printf("\nCPF:  ");
	do{
		getCPF(P.cpf);
		valid = valCPF(P.cpf);
		if(!valid){
			for(i = 0; i < 14; i++) putchar(8);
			printf("                 * CPF invalido");
			for(i = 0; i < 31; i++) putchar(8);
		}else{
//			valid = searchCPF(P.cpf);
			
			if(!valid){
				for(i = 0; i < 14; i++) putchar(8);
				printf("                 * CPF ja cadastrado");
				for(i = 0; i < 36; i++) putchar(8);
			}
		}
		
	}while( !valid );
	
	printf("                      \nNascimento: ");
	do{
		getDate(&P.birth);
		valid = valDate(P.birth);
		
		if(valid){
			for(i = 0; i < 10; i++) putchar(8);
			printf("             * Data invalida");
			for(i = 0; i < 28; i++) putchar(8);
		}
		
	}while(valid);
	
	return P;
}

