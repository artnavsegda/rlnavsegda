#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char *strmbtok ( char *input, char *delimit, char *openblock, char *closeblock) {
    static char *token = NULL;
    char *lead = NULL;
    char *block = NULL;
    int iBlock = 0;
    int iBlockIndex = 0;

    if ( input != NULL) {
        token = input;
        lead = input;
    }
    else {
        lead = token;
        if ( *token == '\0') {
            lead = NULL;
        }
    }

    while ( *token != '\0') {
        if ( iBlock) {
            if ( closeblock[iBlockIndex] == *token) {
                iBlock = 0;
            }
            token++;
            continue;
        }
        if ( ( block = strchr ( openblock, *token)) != NULL) {
            iBlock = 1;
            iBlockIndex = block - openblock;
            token++;
            continue;
        }
        if ( strchr ( delimit, *token) != NULL) {
            *token = '\0';
            token++;
            break;
        }
        token++;
    }
    return lead;
}

int main (int argc , char *argv[]) {
    char *tok;
    char acOpen[]  = {"\"[<{"};
    char acClose[] = {"\"]>}"};
    char acStr[] = {"this contains blocks \"a [quoted block\" and a [bracketed \"block] and <other ]\" blocks>"};

    tok = strmbtok ( acStr, " ", acOpen, acClose);
    printf ( "%s\n", tok);
    while ( ( tok = strmbtok ( NULL, " ", acOpen, acClose)) != NULL) {
        printf ( "%s\n", tok);
    }

    return 0;
}
