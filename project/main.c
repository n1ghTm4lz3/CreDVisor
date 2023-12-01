/*
Title: main.c
Author: n1ghTm4lz3
Description:
	The main program of CreDVisor which aim to manage credentials of our own.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "lib/init.h"
#include "lib/credio.h"


int main(void) {
	int action = -2;
	struct Credential Cred = CREDEFAULT;
	struct Credential *CredPTR;

	CredPTR = &Cred;

	do {
		switch(action){
			case 1:
				Show(CredPTR);
				action = -1;
				break;
			case 2:
				UserInput(CredPTR, 1);
				action = -1;
				break;
			case 3:
				Search(CredPTR);
				action = -1;
				break;
			case 4:
				Generation(CredPTR);
				action = -1;
				break;
			case -1:
				printf("\n\n");
				Help(action);
				printf("> ");
				scanf("%u", &action);
				break;
			case -2:
				Help(action);
				action = -1;
				break;
			default:
				printf("Please choose appropriate action!\n");
				Help(action);
				printf("> ");
				scanf("%u", &action);
				break;
		}
	} while(action != 0);

	return 0;
}
