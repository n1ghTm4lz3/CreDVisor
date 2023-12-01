#include <stdio.h>

#include "init.h"

void Help(int paragraph) {
/*
The function aim to show some message that remind user of actions.
*/
	switch(paragraph) {
		case -2:
			printf("+===============================================================+\n");
			printf("|                                                               |\n");
			printf("|                          CreDVisor                            |\n");
			printf("|                           ver 2.0                             |\n");
			printf("|                        (by n1ghTm4lz3)                        |\n");
			printf("|                                                               |\n");
			printf("| CreDVisor is a tool that manages our own credentials. There   |\n");
			printf("| are functions such as saving credentials, generating password |\n");
			printf("| , credential encryption, etc.                                 |\n");
			printf("|                                                               |\n");
			printf("+===============================================================+\n");
			break;
		default:
			printf("+~~ MENU ~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
			printf("| (1) Show Current Credential Card   |\n");
			printf("| (2) Input Credential               |\n");
			printf("| (3) Search Credential              |\n");
			printf("| (4) Generate Random Password       |\n");
			printf("+~~~~~~~~~~~~~~~~~ Press 0 to Quit ~~+\n");
			break;
	}
}
