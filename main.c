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


struct Credential {
	char id[20];
	char account[50];
	char password[50];
	char url[100];
} CreDefault = {"Test Account", "U53RN4M3", "P455W0RD", "http://website.com"};


void Help(int paragraph);
void UserInput(struct Credential *cred);
void Show(struct Credential *cred);
void FileHandling(int flag, struct Credential *cred);
void Search(struct Credential *cred);
void Encrypt();
void Decrypt();


int main(void) {
	int action = -2;
	struct Credential Cred = CreDefault;
	struct Credential *CredPTR;

	CredPTR = &Cred;

	do {
		switch(action){
			case 1:
				Show(CredPTR);
				action = -1;
				break;
			case 2:
				UserInput(CredPTR);
				FileHandling(1, CredPTR);
				action = -1;
				break;
			case 3:
				Search(CredPTR);
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

void Help(int paragraph) {
	/*
	The function aim to show some message that remind user of actions.
	*/
	switch(paragraph){
		case -2:
			printf("Initial Message\n");
			break;
		default:
			printf("┌ (1) Show Current Credential Card\n");
			printf("├ (2) Input Credential\n");
			printf("├ (3) Search Credential\n");
			printf("└ (0) Quit\n");
			break;
	}
}

void UserInput(struct Credential *cred) {
	printf("\nPlease input your credential information.\n");
	printf("ID - The name of this credential card\n=> ");
	scanf("%s", cred->id);
	printf("Account - The account of the credential\n=> ");
	scanf("%s", cred->account);
	printf("Password - The password of the credential\n=> ");
	scanf("%s", cred->password);
	printf("URL - The entry point where the credential will be used\n=> ");
	scanf("%s", cred->url);
}

void Show(struct Credential *cred) {
	printf("\n(Current Card)\n");
	printf("ID:       %s\n", cred->id);
	printf("Account:  %s\n", cred->account);
	printf("Password: %s\n", cred->password);
	printf("URL:      %s\n", cred->url);
}

void FileHandling(int flag, struct Credential *cred) {
	FILE *file;
	time_t timestamp;

	file = fopen("src/creds", "a+");

	switch(flag){
		case 0:
			break;
		case 1:
			fprintf(file, "\"id\":\"%s\", ", cred->id);
			fprintf(file, "\"account\":\"%s\", ", cred->account);
			fprintf(file, "\"password\":\"%s\", ", cred->password);
			fprintf(file, "\"url\":\"%s\", ", cred->url);
			fprintf(file, "\"timestamp\":%ld\n", timestamp);
			break;
		default:
			break;
	}

	fclose(file);
}

void Search(struct Credential *cred){
	Show(cred);
}
