//
//  readData.c
//  Assignment2
//
//  Created by JIHUI LIANG on 31/1/19.
//  Copyright © 2019 JIHUI LIANG. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readData.h"


int converturl(char *buffer){
    int i = 0;
    int j = 0;
    int num;
    while(buffer[i] != '\0'){
        if(buffer[i] !='u' && buffer[i] != 'r' && buffer[i]!= 'l')
            buffer[j++] = buffer[i];
        i++;
    }
    buffer[j] = '\0';
    num = atoi(buffer);
    return num;
}

List getCollection(){
    FILE *fp = fopen("collection.txt", "r");
    List L = newList();
    char strurl[100];
    if (fp == NULL) {
        printf("collection.txt open error\n");
        exit(1);
        
    }

    while(fscanf(fp, "%s",strurl) == 1){

        int num = converturl(strurl);
        insert(L, num);
    }
    fclose(fp);
    return L;
}

Graph getGraph(List L){
    Graph urlG = newGraph(nElement(L));
    Node temp = head(L);

    while (temp) {

        char filename[100];
        sprintf(filename, "url%d.txt",data(temp));
        FILE *f = fopen(filename, "r");
        char addr[100];
        int outd = 0;
        while (fscanf(f,"%s",addr) == 1){   //read data from urlxx.txt
            if (strcmp(addr,"#start")==0 || strcmp(addr,"Section-1")==0){
                continue;
            }
            if (strcmp(addr,"#end")==0){
                break;
            }
            int newedge = converturl(addr);
            int newID = getIndex(L,newedge); //get the index of the word
            Edge e;
            e.v = id(temp);
            e.w = newID;
            insertEdge(urlG,e);
            outd++;  //record the number of outgoing links
        }
        setoutd(temp,outd);    //get the outdegree for every url
        fclose(f);
        temp = next(temp);
    }
    return urlG;
}


List get2Collection(){
    FILE *fp = fopen("collection.txt", "r");
    List L = new2List();
    char word[100];
    while (fscanf(fp, "%s",word) == 1) {
        insertSetOrd(L, word);
    }
    fclose(fp);
    return L;
}
//normalize the word
void adjust(char *str){
    
    int start = 0;
    int end = (int)strlen(str) - 1;
    while (isspace(str[start]))
           start++;
    while (isspace(str[end])) //make sure no pinc
           end--;
    if(str[end] == ',')
        end--;
    if(str[end] == ';')
        end--;
    if(str[end] == '.')
        end--;
    if(str[end] == '?')
        end--;
    int i;
    for(i = start; i <= end; i++)
        str[i] = tolower(str[i]);
    str[i] = '\0';
        
}
