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
	int no;
} CreDefault = {"Test Account", "U53RN4M3", "P455W0RD", "http://website.com", -1};


void Help(int paragraph);
void UserInput(struct Credential *cred);
void Show(struct Credential *cred);
int FileHandling(int flag, struct Credential *cred);
int Search(struct Credential *cred);
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

int FileHandling(int flag, struct Credential *cred) {
	FILE *file;
	time_t timestamp;
	char buffer[300] = {0};
	int total = 0, counter = 0;

	file = fopen("src/creds", "a+");

	switch(flag) {
		case 0:
			if(fgets(buffer, 300, file) == NULL) {
				printf("!! THERE IS NO CREDENTIAL BE MANAGED !!\n");
				fclose(file);
				return -1;
			}
			break;
		case 1:
			fprintf(file, "\"id\":\"%s\", ", cred->id);
			fprintf(file, "\"account\":\"%s\", ", cred->account);
			fprintf(file, "\"password\":\"%s\", ", cred->password);
			fprintf(file, "\"url\":\"%s\", ", cred->url);
			fprintf(file, "\"timestamp\":%ld\n", timestamp);
			break;
		case 2:
			memset(buffer, 0, sizeof(buffer));
			while(fgets(buffer, 300, file) != NULL) {
				char id[20] = {0};
				int i, j;

				for(i = 6, j = 0; i < 300; i++, j++) {
					if(buffer[i] == '"')
						break;
					else
						id[j] = buffer[i];
				}
				fprintf(stdout, "(%2d) %s\n", total, id);
				total += 1;
			}
			cred->no = total;
			break;
		  case 3:
			memset(buffer, 0, sizeof(buffer));
			while(fgets(buffer, 300, file) != NULL) {
				char *key_value;

				if(counter == cred->no){
					key_value = strtok(buffer, ", \":");
					while(key_value != NULL) {
						if (strcmp(key_value, "id") == 0){
							key_value = strtok(NULL, ", \":");	//Next Token
							strcpy(cred->id, key_value);
						} else if (strcmp(key_value, "account") == 0){
							key_value = strtok(NULL, ", \":");	//Next Token
							strcpy(cred->account, key_value);
						} else if (strcmp(key_value, "password") == 0){
							key_value = strtok(NULL, ", \":");	//Next Token
							strcpy(cred->password, key_value);
						} else if (strcmp(key_value, "url") == 0){
							key_value = strtok(NULL, ", \"");	//Next Token
							key_value = strtok(NULL, ", \"");	//Next Token
							strcpy(cred->url, key_value);
						}
						key_value = strtok(NULL, ", \":");	//Next Token
					}
					break;
				} else {
					counter += 1;
				}
			}
		  	break;
		default:
			break;
	}

	fclose(file);
	return 0;
}

int Search(struct Credential *cred){
	int selection = -1;

	printf("\nSelect the following credential card.\n");
	if(FileHandling(0, cred) == -1){
		return 0;
	} else {
		FileHandling(2, cred); 
		printf("> ");
		scanf("%d", &selection);
		if(selection < 0 || selection >= cred->no){
			printf("Out of range. Please re-select the credential card.\n");
			printf("> ");
			scanf("%d", &selection);
		} else {
			cred->no = selection;
			FileHandling(3, cred);
			Show(cred);
		}
		return 0;
	}
}
