#include <stdio.h>
#include "cpu.h"
#include <stdlib.h>
#include <string.h>

struct _command {
    char * commandMsg;
    byte hh;
    byte ll;
};

typedef struct _LNode Node;

struct _LNode {
    char msg[255];
    Node * next;
};

Node * readFile(FILE * fp){

    int c = 0;
    c = fgetc(fp);

    Node * headNode = malloc(sizeof(Node));
    headNode->next = NULL;
    Node * currentNode = headNode;

    char * buf = currentNode->msg;
    unsigned int idx = 0;

    while (c != EOF){
        
        if (c == ' ' || c == '\n' || c == ','){
            
            buf[idx] = '\0';
            idx = 0;
            
            Node * newNode = malloc(sizeof(Node));
            newNode->next = NULL;
            currentNode->next = newNode;
            currentNode = newNode;
            buf = currentNode->msg;
        }else{
           
            buf[idx] = c;
            idx++;
        }
        c = fgetc(fp);
    }
    return headNode;
}

void displayCommands(Node * headPtr){
    for (Node * p = headPtr; p != NULL; p = p->next){
        printf("%s\n", p->msg);
    }
}


int decodeHex(char hexCharacter){
    switch (hexCharacter){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        default:
            return 0;
    }
}

twobytes processAddress(char * msg){
    twobytes data = (twobytes){};

    int hex = 0;


    char hexdigits[4];
    int hexidx = 0;

    for (char * p = msg; *p != '\0' && hexidx < 4; p++){
        if (*p == '$' && !hex){
            hex = 1;
        }else if (hex == 1){
            hexdigits[hexidx] = *p;
            hexidx++;
        }else{
            data.hh = 0;
            data.ll = 0;
            break;
        }
    }

    char highhex[2];
    char lowhex[2];
    highhex[0] = hexdigits[0];
    highhex[1] = hexdigits[1];
    lowhex[0] = hexdigits[2];
    lowhex[1] = hexdigits[3];

    byte highbyte = decodeHex(highhex[0]) * 16 + decodeHex(highhex[1]);
    byte lowbyte = decodeHex(lowhex[0]) * 16 + decodeHex(lowhex[1]);

    data.hh = highbyte;
    data.ll = lowbyte;

    return data;
}


void processCommands(Node * commandPtr){
    for (Node * p = commandPtr; p != NULL; p = p->next){
        if (strcmp("LDAA", p->msg) == 0){
            printf("LDAA command\n");
            twobytes data = processAddress(p->next->msg);
            printf("hh: %x\n", data.hh);
            printf("ll: %x\n", data.ll);
            printf("\n");
        }
        if (strcmp("MOV", p->msg) == 0){
            printf("MOV command\n");
            twobytes from = processAddress(p->next->msg);
            twobytes to = processAddress(p->next->next->msg);
            printf("\n");
        }
    }
}



void freeNodes(Node * headPtr){
    if (headPtr){
        return;
    }

    Node * nextNode = headPtr->next;
    free(headPtr);
    freeNodes(nextNode);
}

int main(void){

    FILE * fp = fopen("./program.txt", "r");
    Node * commands = readFile(fp);
    processCommands(commands);
    freeNodes(commands);
    return 0;
}