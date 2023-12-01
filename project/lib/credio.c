#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "init.h"
#include "credio.h"

void Show(struct Credential *cred) {
	printf("\n(Current Card)\n");
	printf("ID:       %s\n", cred->id);
	printf("Account:  %s\n", cred->account);
	printf("Password: %s\n", cred->password);
	printf("URL:      %s\n", cred->url);
}

void UserInput(struct Credential *cred, bool flag) {
	printf("\nPlease input your credential information.\n");
	printf("ID - The name of this credential card\n=> ");
	scanf("%s", cred->id);
	printf("Account - The account of the credential\n=> ");
	scanf("%s", cred->account);
	
	if(flag){
		printf("Password - The password of the credential\n=> ");
		scanf("%s", cred->password);
	}

	printf("URL - The entry point where the credential will be used\n=> ");
	scanf("%s", cred->url);
	
	FileHandling(1, cred);
}

int Search (struct Credential *cred) {
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

void Generation(struct Credential *cred) {
	int size = 0, options, i, temp;
	char newCard[2];
	char number[10] = "0123456789";
	char lowercase[26] = "abcdefghijklmnopqrstuvwxyz";
	char uppercase[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char symbol[21] = "!@#$%^&*_+-=;:,./<>?~";
	bool elements[4] = {0, 0, 0, 0};

	printf("\nInput the size of random password: ");
	scanf("%d", &size);
	char rand_pass[size];

	printf("Select elements which contains within the password:\n");
	printf("+-- Options ----------------------------+\n");
	printf("| (1) Number                            |\n");
	printf("| (2) Lowercase Alphabet                |\n");
	printf("| (3) Uppercase Alphabet                |\n");
	printf("| (4) Symbol                            |\n");
	printf("+---------------------------------------+\n");
	printf("(If contains all elements, input 1234)\n");
	printf("> ");
	scanf("%d", &options);
	
	for(i = 0; i < 4; i++) {
		temp = (options % 10) - 1;
		if(temp == -1) {
			break;
		} else {
			elements[temp] = 1;
			options /= 10;
		}
	}
	
	srand(time(NULL));
	for(i = 0; i < size; i++) {
		do {
			options = (rand() % 4);
		} while (elements[options] == 0);

		switch(options){
			case 0:
				temp = rand() % 10;
				rand_pass[i] = number[temp];
				break;
			case 1:
				temp = rand() % 26;
				rand_pass[i] = lowercase[temp];
				break;
			case 2:
				temp = rand() % 26;
				rand_pass[i] = uppercase[temp];
				break;
			case 3:
				temp = rand() % 21;
				rand_pass[i] = symbol[temp];
				break;
		}
	}
	
	printf("\n[!] Random Password: %s\n", rand_pass);

	printf("\n[?] Do you want to new a credential card? (y/n)\n> ");
	scanf("%s", newCard);
	if (newCard[0] == 'Y' | newCard[0] == 'y') {
		strcpy(cred->password, rand_pass);
		UserInput(cred, 0);
	}
}

int FileHandling(int flag, struct Credential *cred) {
	FILE *file;
	time_t timestamp;
	char buffer[300] = {0};
	int total = 0, counter = 0;

	file = fopen(PATH_CRED, "a+");

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

