#ifndef __INIT_H__
#define __INIT_H__

struct Credential {
	char id[20];
	char account[50];
	char password[50];
	char url[100];
	int no;
};
typedef struct Credential CredCard;
#define CREDEFAULT {"Test Account", "U53RN4M3", "P455W0RD", "http://website.com", -1}

void Help(int);

#endif
