#ifndef __CREDIO_H__
#define __CREDIO_H__

#define PATH_CRED "./project/src/creds"

void Show(struct Credential *);
void UserInput(struct Credential *, bool);
int Search(struct Credential *);
void Generation(struct Credential *);
int FileHandling(int, struct Credential *);

#endif
